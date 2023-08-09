// dscp.h
// https://github.com/R-Rothrock/diatom

#ifndef DSCP_H_
#define DSCP_H_

#define DSCP_PORT 

enum dscp_requests;

int dscp(enum dscp_requests __request, char *key, ...);

#endif /* DSCP_H_ */
