// dscp.c
// https://github.com/R-Rothrock/diatom

#include<stdarg.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include "dscp.h"

enum dscp_req
{
  DSCP_START_PROCESS, // used to start processes
  DSCP_START_FORK,    // NOT IMPLEMENTED
  DSCP_START_THREAD,  // NOT IMPLEMENTED
  DSCP_KILL,          // used to stop proccess (or start, depending)
  DSCP_RESPONSE,      // used to respond to info requests (files,
                      // sockets, environment variables, etc.)
} __attribute__((packed));

int dscp(int sockfd, enum dscp_req req, uint16_t diatom_pid, ...)
{
  /* DSCP_START_PROCESS:
   *       16                8                *
   * [ diatom PID ][ DSCP_START_PROCESS ][ pathname ]
   *
   * DSCP_KILL:
   *       16            8         8
   * [ diatom PID ][ DSCP_KILL ][ code ]
   *
   * DSCP_RESPONSE:
   *       16              4              4         *
   * [ diatom PID ][ DSCP_RESPONSE ][ enum info ][ data ]
   */

  va_list ptr;
  va_start(ptr, diatom_pid);

  uint8_t *buf;
  uint8_t size;

  switch(req)
  {
    case DSCP_START_PROCESS:
      char *pathname = va_arg(ptr, char*);

      size = 3 + strlen(pathname) + 1; // +1 is null byte
      buf = malloc(size);

      *buf = diatom_pid;

      buf += 2;
      *buf = DSCP_RESPONSE;

      buf++;
      memcpy(buf, pathname, strlen(pathname) + 1);

      buf -= 3;

      break;

    case DSCP_START_FORK:
      return -1; // NOT IMPLEMENTED
      break;
    case DSCP_START_THREAD:
      return -1; // NOT IMPLEMENTED
      break;
    case DSCP_KILL:
      uint8_t code = (uint8_t)va_arg(ptr, int);

      size = 4;
      buf = malloc(size);

      *buf = diatom_pid;

      buf += 2;
      *buf = DSCP_KILL;

      buf++;
      *buf = code;

      buf -= 3;

      break;
    case DSCP_RESPONSE:
      uint8_t res = (uint8_t)va_arg(ptr, int);
      char *data  = va_arg(ptr, char*);

      size = 3 + strlen(data) + 1; // +1 is null byte
      buf = malloc(size);

      *buf = diatom_pid;

      buf += 2;
      *buf = DSCP_RESPONSE & (res >> 4);

      buf++;
      memcpy(buf, data, strlen(data) + 1);

      buf -= 3;

      break;
    default:
      return -1;
      break;
  }

  va_end(ptr);

  write(sockfd, buf, size);

  free(buf);

  return 0;
}
