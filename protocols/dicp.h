// dicp.h
// https://github.com/R-Rothrock/diatom

#ifndef DICP_H_
#define DICP_H_

#define DICP_PORT 12036

enum dicp_req;

int dicp(int sockfd, char *key, int iv, enum dicp_req req, uint8_t diatom_pid, ...);

#endif /* DICP_H_ */
