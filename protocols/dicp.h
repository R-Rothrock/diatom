// dicp.h
// https://github.com/R-Rothrock/diatom

#ifndef DICP_H_
#define DICP_H_

#define DICP_PORT SOMETHING

enum dicp_requests;

int dicp(enum dicp_requests __request, char *key, ...);

#endif /* DICP_H_ */
