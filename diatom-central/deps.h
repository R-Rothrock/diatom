// deps.h
// https://github.com/R-Rothrock/diatom
// externs to required object files.

#ifndef DEPS_H_
#define DEPS_H_

#include <stdint.h>

// protocols/dscp.h
#define DSCP_PORT 12036
extern enum dscp_req;
extern int dscp(int sockfd, enum dscp_req req, uint16_t diatom_pid, ...);

// protocols/unpack.h
extern enum dicp_req;
extern enum dicp_res;

extern struct dicp_killed;
extern struct dicp_request_info;
extern struct dicp_fork;   // NOT IMPLEMENTED
extern struct dicp_thread; // NOT IMPLEMENTED

extern enum dicp_req ident_dicp(void *buf);
extern struct dicp_killed unpack_dicp_killed(void *buf);
extern struct dicp_request_info unpack_dicp_request_info(void *buf);

// logging/logging.h
extern char *get_formatted_time(void);

extern debug(char *msg);
extern info(char *msg);
extern warning(char *msg);
extern critical(char *msg);
extern error(char *msg);

extern debugf(char *msg);
extern infof(char *msg);
extern warningf(char *msg);
extern criticalf(char *msg);
extern errorf(char *msg);

#endif /* DEPS_H_ */
