// dicp.c
// https://github.com/R-Rothrock/diatom

#include<stdarg.h>
#include<sys/socket.h>

#include "dicp.h"

enum dicp_requests
{
  DICP_KILLED,       // process died (SIGABRT, SIGSEGV, SIGCONT, etc.)
  DICP_REQUEST_INFO, // requests files, sockets, etc.
  DICP_FORK,         // NOT IMPLEMENTED
  DICP_THREAD,       // NOT IMPLEMENTED
}

enum dicp_info_requests
{
  INFO_REQUEST_FILE,        // requests file
  INFO_REQUEST_SOCKET,      // requests socket
  INFO_REQUEST_ENVIRON,     // request environment variables
  INFO_REQUEST_ENVIRON_VAR, // requests specific environment variable
}

int dicp(enum dicp_requests __request, int sockfd. char *key, int iv, ...)
{
  /* docs */
}
