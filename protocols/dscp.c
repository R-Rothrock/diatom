// dscp.c
// https://github.com/R-Rothrock/diatom

#include<stdarg.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>

#include<openssl/aes.h>

#include "dscp.h"

enum dscp_requests
{
  DSCP_START_PROCESS, // used to start processes
  DSCP_START_FORK,    // NOT IMPLEMENTED
  DSCP_START_THREAD,  // NOT IMPLEMENTED
  DSCP_KILL,          // used to stop proccess (or start, depending)
  DSCP_RESPONSE,      // used to respond to info requests (files,
  // sockets, environment variables, etc.)
}

int dscp(int sockfd, char *key, int iv, enum dscp_requests dscp_req, ...)
{
  va_list ptr;
  va_start(alp, dscp_req);

void *buf;

  match(dscp_req)
  {
    case DSCP_START_PROCESS:
      char *name = va_arg(ptr, void*);

      buf = malloc(2 + sizeof(*name));

      *buf[0] = DSCP_START_PROCESS;
      buf++;
      memcpy(*buf, *name, sizeof(*name));

      int id = va_arg(ptr, uint8_t);
      *buf[sizeof(*buf)] = id;

      break;

    case DSCP_START_FORK:
      break;
    case DSCP_START_THREAD:
      break;
    case DSCP_KILL:
      break;
    case DSCP_RESPONSE:
      break;
  }

  va_end(ptr);

  // TODO encrypt

  write(sockfd, buf, sizeof(*buf));

  return 0;
}
