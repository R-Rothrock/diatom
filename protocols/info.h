// info.h
// https://github.com/R-Rothrock/diatom

#ifndef INFO_H_
#define INFO_H_

// utilized for DICP_REQUEST_INFO, DICP_ALTER, and DSCP_RESPONSE
enum info {
  INFO_FILE, // file sharing
  INFO_STAT, // file stat sharing
  INFO_POLL, // poll data sharing
  // TODO
} __attribute__((__packed__));

#endif /* INFO_H_ */
