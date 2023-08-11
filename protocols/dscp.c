// dscp.c
// https://github.com/R-Rothrock/diatom

#include<stdarg.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>

#include<openssl/aes.h>

#include "dscp.h"

enum dscp_req
{
  DSCP_START_PROCESS, // used to start processes
  DSCP_START_FORK,    // NOT IMPLEMENTED
  DSCP_START_THREAD,  // NOT IMPLEMENTED
  DSCP_KILL,          // used to stop proccess (or start, depending)
  DSCP_RESPONSE,      // used to respond to info requests (files,
                      // sockets, environment variables, etc.)
}
// might only be supported by GCC
__attribute__ ((__packed__));
STATIC_ASSERT(sizeof(enum dscp_req) == 1)

int dscp(int sockfd, char *key, int iv, enum dscp_req req,
         ...)
{
  va_list ptr;
  va_start(alp, dscp_req);

void *buf;

  match(dscp_req)
  {
    case DSCP_START_PROCESS:
      char *name = va_arg(ptr, void*);
      int id     = va_arg(ptr, int);

      buf = malloc(1 + sizeof(*name) + sizeof(id));

      *buf[0] = DSCP_START_PROCESS;
      memcpy(*(buf + 1), *name, sizeof(*name));
      memcpy(*(buf + 1 + sizeof(*name), id, sizeof(id)));

      break;

    case DSCP_START_FORK:
      return -1; // NOT IMPLEMENTED
      break;
    case DSCP_START_THREAD:
      return -1; // NOT IMPLEMENTED
      break;
    case DSCP_KILL:
      int id   = va_arg(ptr, int);
      int code = va_arg(ptr, int);

      *buf = malloc(1 + sizeof(int) * 2);

      *buf[0] = DSCP_KILL;
      memcpy(*(buf + 1), id, sizeof(id));
      memcpy(*(buf + 1 + sizeof(id)), code, sizeof(code));

      break;
    case DSCP_RESPONSE:
      break;
  }

  va_end(ptr);

  // TODO encrypt

  write(sockfd, buf, sizeof(*buf));

  return 0;
}
