// unpack.h
// https://github.com/R-Rothrock/diatom
// a library for packing and unpacking DICP and DSCP requests.

#ifndef UNPACK_H_
#define UNPACK_H_

enum dicp_req;
enum dscp_req;

enum dicp_res;
enum dscp_res;

struct dicp_killed;
struct dicp_request_info;
struct dicp_fork;   // NOT IMPLEMENTED
struct dicp_thread; // NOT IMPLEMENTED

struct dscp_start_process;
struct dscp_start_fork;   // NOT IMPLEMENTED
struct dscp_start_thread; // NOT IMPLEMENTED
struct dscp_kill;
struct dscp_response;

enum dicp_req ident_dicp(void *buf);
enum dscp_req ident_dscp(void *buf);

struct dicp_killed unpack_dicp_killed(void *buf);
struct dicp_request_info unpack_dicp_request_info(void *buf);
struct dscp_start_process unpack_dscp_start_process(void *buf);
struct dscp_kill unpack_dscp_kill(void *buf);
struct dscp_response unpack_dscp_response(void *buf);

#endif /* UNPACK_H_ */
