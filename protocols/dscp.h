// dscp.h
// https://github.com/R-Rothrock/diatom

#ifndef DSCP_H_
#define DSCP_H_

#define DSCP_PORT 12036

enum dscp_req;

int dscp(int sockfd, char *key, int iv, enum dscp_req dscp_req,
         ...)

#endif /* DSCP_H_ */
