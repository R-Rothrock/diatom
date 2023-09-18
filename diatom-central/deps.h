// deps.h
// https://github.com/R-Rothrock/diatom
// externs to required object files.

#include<stdint.h>

// protocols/dscp.h
extern enum dscp_req;
extern enum dscp_res;
extern int dscp(int sockfd, enum dscp_req req, uint16_t diatom_pid, ...);


// protocols/unpack.h
extern enum dicp_req;
extern enum dicp_req

extern struct dicp_killed;
extern struct dicp_request_info;
extern struct dicp_fork; // NOT IMPLEMENTED
extern struct dicp_thread; // NOT IMPLEMENTED

extern enum dicp_req ident_dicp(void *buf);
extern struct dicp_killed unpack_dicp_killed(void *buf);
extern struct dicp_request_info unpack_dicp_request_info(void *buf);

// TODO logging/logging.h
