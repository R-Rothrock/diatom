// dscp.c
// https://github.com/R-Rothrock/diatom

#include<stdarg.h>
#include<sys/socket.h>

#include "dscp.h"

enum dscp_requests
{
  DSCP_START_PROCESS, // used to start processes
  DSCP_START_FORK,    // used to start forks
  DSCP_START_THREAD,  // used to start threads
  DSCP_RESPONSE       // used to response to info requests (files, sockets, etc.)
}

int dscp(enum dicp_requests __request, char *key, ...)
{
  /* docs */
}
