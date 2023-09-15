// unpack.c
// https://github.com/R-Rothrock/diatom

#include "pack.h"

enum dicp_req
{
  DICP_KILLED,       // process signal (SIGABRT, SIGSEGV, SIGCONT, etc.)
  DICP_REQUEST_INFO, // requests files, sockets, etc.
  DICP_FORK,         // NOT IMPLEMENTED
  DICP_THREAD,       // NOT IMPLEMENTED
} __attribute__((packed));

enum dscp_req
{
  DSCP_START_PROCESS, // used to start processes
  DSCP_START_FORK,    // NOT IMPLEMENTED
  DSCP_START_THREAD,  // NOT IMPLEMENTED
  DSCP_KILL,          // used to stop proccess (or start, depending)
  DSCP_RESPONSE,      // used to respond to info requests (files,
                      // sockets, environment variables, etc.)
} __attribute__((packed));

enum dicp_res
{
  DICP_RES_FILE,    // request a file (sokets, too)
  DICP_RES_ENVIRON, // request environment variables
  DICP_RES_PROCESS, // ptrace stuff NOT IMPLEMENTED
  DICP_RES_MEMORY,  // request memory and/or registers NOT IMPLEMENTED
} __attribute__((packed));

enum dscp_res
{
  DSCP_RES_FILE,    // responding to a request for a file (sockets, too)
  DSCP_RES_ENVIRON, // responding to a request for environment variables
  DSCP_RES_PROCESS, // other process state NOT IMPLEMENTED
  DSCP_RES_MEMORY,  // other process memory or registers NOT IMPLEMENTED
} __attribute__((__packed__));

struct dicp_killed
{
  uint16_t diatom_pid;
  uint8_t code;
};

struct dicp_request_info
{
  uint16_t diatom_pid;
  enum dicp_res res;
  char *data;
};

struct dicp_fork
{
  // NOT IMPLEMENTED
};

struct dicp_thread
{
  // NOT IMPLEMENTED
};

struct dscp_start_process
{
  uint16_t diatom_pid;
  char *pathname;
};

struct dscp_start_fork
{
  // NOT IMPLEMENTED
};

struct dscp_start_thread
{
  // NOT IMPLEMENTED
};

struct dscp_kill
{
  uint16_t diatom_pid;
  uint8_t code;
};

struct dscp_response
{
  uint16_t diatom_pid;
  enum dscp_res res;
  char *data;
};

enum dicp_req ident_dicp(void *buf)
{
  return *(buf + 2); // +2 to skip Diatom PID
}

enum dscp_req ident_dscp(void *buf)
{
  return *(buf + 2); // +2 to skip Diatom PID
}

struct dicp_killed unpack_dicp_killed(void *buf)
{
  struct dicp_killed ret;

  ret.diatom_pid = *buf;

  buf += 2;

  ret.code = *buf;

  return ret
}

struct dicp_request_info unpack_dicp_request_info(void *buf)
{
  struct dicp_request_info ret;

  ret.diatom_pid = *buf

  buf += 2;

  ret.res = *buf;

  buf++;

  char str[strlen(buf) + 1];
  strcpy(&str, buf);

  ret.data = &str;

  return ret;
}

struct dscp_start_process unpack_dscp_start_process(void *buf)
{
  struct dscp_start_process ret;

  ret.diatom_pid = *buf;

  buf += 2;

  char str[strlen(buf) + 1];
  strcpy(&str, buf);

  ret.pathname = &str;

  return ret;
}

struct dscp_kill unpack_dscp_kill(void *buf)
{
  struct dscp_kill ret;

  ret.diatom_pid = *buf;

  buf += 2;

  ret.code = *buf;

  return ret;
}

struct dscp_response unpack_dscp_response(void *buf)
{
  struct dscp_response ret;

  ret.diatom_pid = *buf;

  buf += 2;

  ret.ret = *buf;

  buf ++;

  char str[strlen(buf) + 1];
  strcpy(&str, buf);

  ret.pathname = &str;

  return ret;
}

// TODO functions to pack the structs
