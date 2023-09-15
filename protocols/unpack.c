// unpack.c
// https://github.com/R-Rothrock/diatom

#include "unpack.h"

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

struct dicp_killed_unpacked
{
  uint16_t diatom_pid;
  uint8_t code;
};

struct dicp_request_info_unpacked
{
  uint16_t diatom_pid;
  enum dicp_res res;
  char *data;
};

struct dicp_fork_unpacked
{
  // NOT IMPLEMENTED
};

struct dicp_thread_unpacked
{
  // NOT IMPLEMENTED
};

struct dscp_start_process_unpacked
{
  uint16_t diatom_pid;
  char *pathname;
};

struct dscp_start_fork_unpacked
{
  // NOT IMPLEMENTED
};

struct dscp_start_thread_unpacked
{
  // NOT IMPLEMENTED
};

struct dscp_kill_unpacked
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
