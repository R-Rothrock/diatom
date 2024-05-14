// deps.h
// https://github.com/R-Rothrock/diatom
// externs to required object files.

#ifndef DEPS_H_
#define DEPS_H_

#include <stdint.h>

// protocols/dicp.h
extern enum dicp_req;
extern int dicp(int sockfd, enum dicp_req req, uint16_t diatom_pid, ...);

// protocols/unpacking.h
extern enum dscp_req;
extern enum dscp_res;

extern struct dscp_start_process;
extern struct dscp_start_fork;
extern struct dscp_start_thread;
extern struct dscp_kill;
extern struct dscp_response;

extern struct dscp_kill unpack_dscp_kill(void *buf);
extern struct dscp_response unpack_dscp_response(void *buf);

#endif /* DEPS_H_ */
