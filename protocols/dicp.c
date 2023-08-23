// dicp.c
// https://github.com/R-Rothrock/diatom

#include<stdarg.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

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

int dicp(int sockfd, char *key, int iv, enum dicp_req req, uint8_t diatom_pid, ...)
{
  /* DICP_KILLED:
   *   8          4             4          8
   * [ iv ][ DICP_KILLED ][ diatom PID ][ code ]
   *
   * DICP_REQUEST_INFO:
   *   8             4                 4               8           *
   * [ iv ][ DICP_REQUEST_INFO ][ diatom PID  ][ enum dicp_res ][ data ]
   *
   */

  va_list ptr;
  va_start(ptr, diatom_pid);

  int *buf;
  uint8_t size;

  switch(req)
  {
    case DICP_KILLED:
      uint8_t code = (uint8_t)va_arg(ptr, unsigned int);

      size = 3;
      buf = malloc(size);

      *buf = iv;

      buf++;
      *buf = DICP_KILLED & (diatom_pid >> 4);

      buf++;
      *buf = code;

      buf -= 2;

      break;
    case DICP_REQUEST_INFO:
      uint8_t res = (uint8_t)va_arg(ptr, unsigned int);
      char *data  = va_arg(ptr, char*);

      size = 3 + strlen(data);
      buf = malloc(size);

      *buf = iv;

      buf++;
      *buf = DICP_REQUEST_INFO & (diatom_pid >> 4);

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
}
