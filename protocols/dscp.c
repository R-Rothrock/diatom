// dscp.c
// https://github.com/R-Rothrock/diatom

#include<stdarg.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include<openssl/evp.h>

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

int dscp(int sockfd, char *key, uint8_t iv, enum dscp_req req,
         uint8_t diatom_pid, ...)
{
  /* DSCP_START_PROCESS:
   *   8            4                  4            *
   * [ iv ][ DSCP_START_PROCESS ][ diatom PID ][ pathname ]
   *
   * DSCP_KILL:
   *   8         4            4          8
   * [ iv ][ DSCP_KILL ][ diatom PID ][ code ]
   *
   * DSCP_RESPONSE:
   *   8           4              4               8           *
   * [ iv ][ DSCP_RESPONSE ][ diatom PID ][ enum dscp_res ][ data ]
   */

  va_list ptr;
  va_start(ptr, diatom_pid);

  int *buf;
  uint8_t size;

  switch(req)
  {
    case DSCP_START_PROCESS:
      char *name = va_arg(ptr, char*);

      size = 2 + strlen(name);
      buf = malloc(size);

      *buf = iv;

      buf++;
      *buf = DSCP_RESPONSE & (diatom_pid >> 4);

      buf++;
      memcpy(buf, name, strlen(name));

      buf -= 2;

      break;

    case DSCP_START_FORK:
      return -1; // NOT IMPLEMENTED
      break;
    case DSCP_START_THREAD:
      return -1; // NOT IMPLEMENTED
      break;
    case DSCP_KILL:
      uint8_t code = (uint8_t)va_arg(ptr, unsigned int);

      size = 2;
      buf = malloc(size);

      *buf = iv;

      buf++;
      *buf = DSCP_KILL & (diatom_pid >> 4);

      buf++;
      *buf = code;

      buf -= 2;

      break;
    case DSCP_RESPONSE:
      uint8_t res = (uint8_t)va_arg(ptr, unsigned int);
      char *data  = va_arg(ptr, char*);

      size = 3 + strlen(data);
      buf = malloc(size);

      *buf = iv;

      buf++;
      *buf = DSCP_RESPONSE & (diatom_pid >> 4);

      buf++;
      *buf = res;

      buf++;
      memcpy(buf, data, strlen(data));

      buf -= 3;

      break;
    default:
      return -1;
      break;
  }

  va_end(ptr);

  // TODO encryption
  // not encrypting the first byte, since that's the IV.

  write(sockfd, buf, size);

  return 0;
}
