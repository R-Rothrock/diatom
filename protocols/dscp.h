// dscp.h
// https://github.com/R-Rothrock/diatom

#ifndef DSCP_H_
#define DSCP_H_

#include <stdint.h>

#include "info.h"

#define DSCP_PORT 12036

enum dscp_req;

void *dscp(int sockfd, enum dscp_req req, uint16_t diatom_pid, ...);

#endif /* DSCP_H_ */
