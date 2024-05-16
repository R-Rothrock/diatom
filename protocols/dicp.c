// dicp.c
// https://github.com/R-Rothrock/diatom

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dicp.h"

// These are the different DICP packet types.
// DICP_KILLED: The tracee/process being handled by the client machine
//              died/terminated/stopped/started/etc.
// DICP_REQUEST_INFO: The client machine needs data (files, file
//                    permissions, etc.) on behalf of either the
//                    tracee or the Diatom Client itself.
// DICP_ALTER: The client machine alters the central machine's data
//             (files, etc.) usually on behald of the tracee. The
//             Diatom Client wouldn't alter data on it's own behalf (
//             I don't think.)

enum dicp_req {
  DICP_KILLED,
  DICP_REQUEST_INFO DICP_ALTER
} __attribute__((packed));

void *dicp(enum dicp_req req, uint16_t diatom_pid, ...) {
  /* DICP_KILLED:
   *       64             16             8          8
   * [ packet size ][ diatom PID ][ DICP_KILLED ][ code ]
   *
   * DICP_REQUEST_INFO:
   *       64             16                8                8         *
   * [ packet size ][ diatom PID ][ DICP_REQUEST_INFO ][ enum info ][ loc ]
   *
   * DICP_ALTER:
   *       64             16            8             8         *      *
   * [ packet size ][ diatom PID ][ DICP_ALTER ][ enum info ][ loc ][ data ]
   */

  va_list ptr;
  va_start(ptr, diatom_pid);

  void *buf;
  uint64_t size;

  switch (req) {
  case DICP_KILLED: {
    uint8_t code = (uint8_t)va_arg(ptr, int);

    size = 20;
    buf = malloc(size);

    *(uint64_t *)buf = size;

    buf += 8;
    *(uint8_t *)buf = diatom_pid;

    buf += 2;
    *(uint8_t *)buf = DICP_KILLED;

    buf++;
    *(uint8_t *)buf = code;

    buf -= 11;
  }
  case DICP_REQUEST_INFO: {
    uint8_t info = (uint8_t)va_arg(ptr, int);
    char *loc = va_arg(ptr, char *);

    size = 1 + strlen(loc) + 1;
    buf = malloc(size);

    *(uint64_t *)buf = size;

    buf += 8;
    *(uint8_t *)buf = diatom_pid;

    buf += 2;
    *(uint8_t *)buf = DICP_REQUEST_INFO;

    buf++;
    *(uint8_t *)buf = info;

    buf++;
    memcpy(buf, loc, strlen(loc) + 1);

    buf -= 11;
  }
  case DICP_ALTER: {
    uint8_t info = (uint8_t)va_arg(ptr, int);
    char *loc = va_arg(ptr, char *);
    char *data = va_arg(ptr, char *);

    size = 12 + strlen(loc) + 1 + strlen(data) + 1;
    buf = malloc(size);

    *(uint64_t *)buf = size;
    buf += 8;

    *(uint8_t *)buf = diatom_pid;

    buf += 2;
    *(uint8_t *)buf = DICP_ALTER;

    buf++;
    *(uint8_t *)buf = info;

    buf++;
    memcpy(buf, loc, strlen(loc) + 1);

    buf += strlen(loc) + 1;
    memcpy(buf, data, strlen(data) + 1);

    buf -= (14 + strlen(loc) + strlen(data));
  }
  default: {
    return (void *)0;
  }
  }

  va_end(ptr);

  return buf;

  return 0;
}
