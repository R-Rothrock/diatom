// dicp.c
// https://github.com/R-Rothrock/diatom

#include<stdarg.h>
#include<sys/socket.h>

#include "dicp.h"

enum dicp_req
{
  DICP_KILLED,       // process died (SIGABRT, SIGSEGV, SIGCONT, etc.)
  DICP_REQUEST_INFO, // requests files, sockets, etc.
  DICP_FORK,         // NOT IMPLEMENTED
  DICP_THREAD,       // NOT IMPLEMENTED
}
// might only be supported by GCC
__attribute__ ((__packed__));
STATIC_ASSERT(sizeof(enum dscp_req) == 1)

enum dicp_info_req
{
  INFO_REQUEST_FILE,        // requests file
  INFO_REQUEST_SOCKET,      // requests socket
  INFO_REQUEST_ENVIRON,     // request environment variables
  INFO_REQUEST_ENVIRON_VAR, // requests specific environment variable
}
// might only be supported by GCC
__attribute__ ((__packed__));
STATIC_ASSERT(sizeof(enum dscp_req) == 1)

int dicp(int sockfd, char *key, int iv, enum dicp_req req, ...)
{
  /* docs */
}
