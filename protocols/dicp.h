// dicp.h
// https://github.com/R-Rothrock/diatom

#ifndef DICP_H_
#define DICP_H_

#define DICP_PORT 12036

enum dicp_requests;

int dicp(enum dicp_requests __request, int sockfd, char *key, int iv, ...);

#endif /* DICP_H_ */
