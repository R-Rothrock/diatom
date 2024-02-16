// dscp.c
// https://github.com/R-Rothrock/diatom

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dscp.h"

enum dscp_req {
  DSCP_START_PROCESS, // used to start processes
  DSCP_KILL,          // used to stop proccess
  DSCP_RESPONSE,      // used to respond to info requests (files,
                      // sockets, environment variables, etc.)
} __attribute__((packed));

void *dscp(int sockfd, enum dscp_req req, uint16_t diatom_pid, ...) {
  /* DSCP_START_PROCESS:
   *       64             16                8                *
   * [ packet size ][ diatom PID ][ DSCP_START_PROCESS ][ pathname ]
   *
   * DSCP_KILL:
   *       64             16            8         8
   * [ packet size ][ diatom PID ][ DSCP_KILL ][ code ]
   *
   * DSCP_RESPONSE:
   *       64             16              8              8         *      *
   * [ packet size ][ diatom PID ][ DSCP_RESPONSE ][ enum info ][ loc ][ data ]
   */

  va_list ptr;
  va_start(ptr, diatom_pid);

  void *buf;
  uint64_t size;

  switch (req) {
  case DSCP_START_PROCESS:
    char *pathname = va_arg(ptr, char *);

    size = 11 + strlen(pathname) + 1;
    buf = malloc(size);

    *(uint64_t*)buf = size;

    buf += 8;
    *(uint8_t*)buf = diatom_pid;

    buf += 2;
    *(uint8_t*)buf = DSCP_RESPONSE;

    buf++;
    memcpy(buf, pathname, strlen(pathname) + 1);

    buf -= 11;

  case DSCP_KILL:
    uint8_t code = (uint8_t)va_arg(ptr, int);

    size = 12;
    buf = malloc(size);

    *(uint64_t*)buf = size;

    buf += 8;
    *(uint8_t*)buf = diatom_pid;

    buf += 2;
    *(uint8_t*)buf = DSCP_KILL;

    buf++;
    *(uint8_t*)buf = code;

    buf -= 11;

    break;
  case DSCP_RESPONSE:
    uint8_t info = (uint8_t)va_arg(ptr, int);
    char *loc = va_arg(ptr, char *);
    char *data = va_arg(ptr, char *);

    size = 11 + strlen(loc) + strlen(data) + 2;
    buf = malloc(size);

    *(uint64_t*)buf = size;

    buf += 8;
    *(uint8_t*)buf = diatom_pid;

    buf += 2;
    *(uint8_t*)buf = DSCP_RESPONSE;

    buf++;
    *(uint8_t*)buf = info;

    buf++;
    memcpy(buf, loc, strlen(loc) + 1);

    buf++;
    memcpy(buf, data, strlen(data) + 1);

    buf -= (12 + strlen(loc));

    break;
  default:
    return -1;
    break;
  }

  va_end(ptr);

  return buf;

  return 0;
}
