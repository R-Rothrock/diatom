// dscp.h
// https://github.com/R-Rothrock/diatom

#ifndef DSCP_H_
#define DSCP_H_

#define DSCP_PORT 12036

enum dscp_req;

int dscp(int sockfd, char *key, uint8_t iv, enum dscp_req req, uint8_t diatom_pid, ...);

#endif /* DSCP_H_ */
