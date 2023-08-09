// dscp.c
// https://github.com/R-Rothrock/diatom

#include<stdarg.h>
#include<stdlib.h>
#include<sys/socket.h>

#include<openssl/aes.h>

#include "dscp.h"

enum dscp_requests
{
  DSCP_START_PROCESS, // used to start processes
  DSCP_START_FORK,    // used to start forks
  DSCP_START_THREAD,  // used to start threads
  DSCP_KILL           // used to stop proccess (or start, depending)
  DSCP_RESPONSE       // used to respond to info requests (files, sockets, etc.)
}

int dscp(enum dicp_requests __request, int sockfd, char *key, int iv, ...)
{
  
}
