// unpack.h
// https://github.com/R-Rothrock/diatom
// a library for unpacking DICP and DSCP requests.

#ifndef UNPACK_H_
#define UNPACK_H_

enum dicp_req;
enum dscp_req;

enum dicp_res;
enum dscp_res;

struct dicp_killed_unpacked;
struct dicp_request_info_unpacked;
struct dicp_fork_unpacked;   // NOT IMPLEMENTED
struct dicp_thread_unpacked; // NOT IMPLEMENTED



int unencrypt(char *ciphertxt, char *key, int iv);

struct diatom_prot_sep;

struct diatom_prot_sep sep_res(char *data);

#endif /* UNPACK_H_ */
