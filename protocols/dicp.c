// dicp.c
// https://github.com/R-Rothrock/diatom

#include<stdarg.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include "dicp.h"

enum dicp_req
{
  DICP_KILLED,       // process signal (SIGABRT, SIGSEGV, SIGCONT, etc.)
  DICP_REQUEST_INFO, // requests files, permissions, etc.
  DICP_ALTER         // alter files, permissions, etc.
} __attribute__((packed)); // all values are uint8_t

int dicp(int sockfd, enum dicp_req req, uint16_t diatom_pid, ...)
{
  /* DICP_KILLED:
   *       16             8          8
   * [ diatom PID ][ DICP_KILLED ][ code ]
   *
   * DICP_REQUEST_INFO:
   *       16                8                8         *
   * [ diatom PID ][ DICP_REQUEST_INFO ][ enum info ][ data ]
   *
   * DICP_ALTER:
   *       16            8             8         *      *
   * [ diatom PID ][ DICP_ALTER ][ enum info ][ loc ][ data ]
   */

  va_list ptr;
  va_start(ptr, diatom_pid);

  uint8_t *buf;
  uint8_t size;

  switch(req)
  {
    case DICP_KILLED:
      uint8_t code = (uint8_t)va_arg(ptr, int);

      size = 4;
      buf = malloc(size);

      *buf = diatom_pid;

      buf += 2;
      *buf = DICP_KILLED;

      buf++;
      *buf = code;

      buf -= 3;

    case DICP_REQUEST_INFO:
      uint8_t info = (uint8_t)va_arg(ptr, int);
      char *loc  = va_arg(ptr, char*);

      size = 3 + strlen(data) + 1;
      buf = malloc(size);

      *buf = diatom_pid;

      buf += 2;
      *buf = DICP_REQUEST_INFO;

      buf++;
      *buf = info;

      buf++;
      memcpy(buf, loc, strlen(loc) +1);

      buf -= 3;

    case DICP_ALTER:
      uint8_t info = (uint8_t)va_arg(ptr, int);
      char *loc    = va_arg(ptr, char*);
      char *data   = va_arg(ptr, char*);

      size = 4 + strlen(loc) + 1 + strlen(data) + 1;
      buf = malloc(size);

      *buf = diatom_pid;

      buf += 2;
      *buf = DICP_ALTER;

      buf++;
      *buf = info;

      buf++;
      memcpy(buf, loc, strlen(loc) + 1);

      buf += strlen(loc) + 1;
      memcpy(buf, data, strlen(data) + 1);

      buf -= (6 + strlen(loc) + strlen(data));

    default:
      return -1;
    }

  va_end(ptr);

  write(sockfd, buf, size);

  free(buf);

  return 0;
}
