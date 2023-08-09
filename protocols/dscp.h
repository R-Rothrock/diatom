// dscp.h
// https://github.com/R-Rothrock/diatom

#ifndef DSCP_H_
#define DSCP_H_

#define DSCP_PORT 12036

enum dscp_requests;

int dscp(enum dscp_requests __request, int sockfd, char *key, int iv, ...);

#define IV 123

#endif /* DSCP_H_ */
