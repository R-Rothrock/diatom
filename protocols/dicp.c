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
} __attribute__((packed)); // all values are uint8_t

enum dicp_res
{
  DICP_RES_FILE,    // request a file (sokets, too)
  DICP_RES_ENVIRON, // request environment variables
  DICP_RES_PROCESS, // ptrace stuff NOT IMPLEMENTED
  DICP_RES_MEMORY,  // request memory and/or registers NOT IMPLEMENTED
} __attribute__((packed));

int dicp(int sockfd, enum dicp_req req, uint16_t diatom_pid, ...)
{
  /* DICP_KILLED:
   *       16              8          8
   * [ diatom PID ][ DICP_KILLED ][ code ]
   *
   * DICP_REQUEST_INFO:
   *        16               4                     4             *
   * [ diatom PID ][ DICP_REQUEST_INFO ][ enum dicp_res res ][ data ]
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

      size = 4;
      buf = malloc(size);

      *buf = diatom_pid;

      buf += 2;
      *buf = DICP_KILLED;

      buf++;
      *buf = code;

      buf -= 3;

      break;
    case DICP_REQUEST_INFO:
      uint8_t res = (uint8_t)va_arg(ptr, unsigned int);
      char *data  = va_arg(ptr, char*);

      size = 3 + strlen(data) + 1; // +1 is null byte
      buf = malloc(size);

      *buf = diatom_pid;

      buf += 2;
      *buf = DICP_REQUEST_INFO & (res >> 4);

      buf++;
      memcpy(buf, data, strlen(data));

      buf -= 3;

      break;
    default:
      return -1;
      break;
  }

  va_end(ptr);

  write(sockfd, buf, size);
}
