// dicp.c
// https://github.com/R-Rothrock/diatom

#include<stdarg.h>

#include "dicp.h"

enum dicp_req
{
  DICP_KILLED,       // process signal (SIGABRT, SIGSEGV, SIGCONT, etc.)
  DICP_REQUEST_INFO, // requests files, sockets, etc.
  DICP_FORK,         // NOT IMPLEMENTED
  DICP_THREAD,       // NOT IMPLEMENTED
} __attribute__((packed));

enum dicp_res
{
  DICP_RES_FILE,    // request a file (sokets, too)
  DICP_RES_ENVIRON, // request environment variables
  DICP_RES_PROCESS, // ptrace stuff NOT IMPLEMENTED
  DICP_RES_MEMORY,  // request memory and/or registers NOT IMPLEMENTED
} __attribute__((packed));

int dicp(int sockfd, char *key, int iv, enum dicp_req req, ...)
{
  /**/
}
