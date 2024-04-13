// deps.h
// https://github.com/R-Rothrock/diatom
// externs to required object files.

#ifndef DEPS_H_
#define DEPS_H_

#include <stdint.h>

// protocols/dicp.h
#define DSCP_PORT 12036
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

// logging/logging.h
extern char *get_formatted_time(void);

extern void debug(char *msg);
extern void info(char *msg);
extern void warning(char *msg);
extern void critical(char *msg);
extern void error(char *msg);

extern void debugf(char *msg);
extern void infof(char *msg);
extern void warningf(char *msg);
extern void criticalf(char *msg);
extern void errorf(char *msg);

#endif /* DEPS_H_ */
