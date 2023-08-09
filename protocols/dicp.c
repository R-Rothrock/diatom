// dicp.c
// https://github.com/R-Rothrock/diatom

#include<stdarg.h>
#include<sys/socket.h>

#include "dicp.h"

enum dicp_requests
{
  DICP_KILLED       // process was killed
  DICP_REQUEST_INFO // requests files, sockets, etc.
  DICP_FORK         // process forks
  DICP_THREAD       // process tries to start a new thread
}

int dicp(enum dicp_requests __request, char *key, ...)
{
  /* docs */
}
