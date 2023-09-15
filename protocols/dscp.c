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

enum dscp_res
{
  DSCP_RES_FILE,    // responding to a request for a file (sockets, too)
  DSCP_RES_ENVIRON, // responding to a request for environment variables
  DSCP_RES_PROCESS, // other process state NOT IMPLEMENTED
  DSCP_RES_MEMORY,  // other process memory or registers NOT IMPLEMENTED
} __attribute__((__packed__));

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
   *       16              4                4           *
   * [ diatom PID ][ DSCP_RESPONSE ][ enum dscp_res ][ data ]
   */

  va_list ptr;
  va_start(ptr, diatom_pid);

  int *buf;
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
      memcpy(buf, pathname, strlen(pathname));

      buf -= 3;

      break;

    case DSCP_START_FORK:
      return -1; // NOT IMPLEMENTED
      break;
    case DSCP_START_THREAD:
      return -1; // NOT IMPLEMENTED
      break;
    case DSCP_KILL:
      uint8_t code = (uint8_t)va_arg(ptr, unsigned int);

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
      uint8_t res = va_arg(ptr, uint8_t);
      char *data  = va_arg(ptr, char*);

      size = 3 + strlen(data) + 1; // +1 is null byte
      buf = malloc(size);

      *buf = diatom_pid;

      buf += 2;
      *buf = DSCP_RESPONSE & (res >> 4);

      buf++;
      memcpy(buf, data, strlen(data));

      buf -= 3;

      break;
    default:
      return -1;
      break;
  }

  va_end(ptr);

  write(sockfd, buf, size);

  return 0;
}
