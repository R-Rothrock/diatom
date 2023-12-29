// dicp.h
// https://github.com/R-Rothrock/diatom

#ifndef DICP_H_
#define DICP_H_

#include<stdint.h>

#include "info.h"

#define DICP_PORT 12036

enum dicp_req;
enum dicp_res;

int dicp(int sockfd, enum dicp_req req, uint16_t diatom_pid, ...);

#endif /* DICP_H_ */
