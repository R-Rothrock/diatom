// info.h
// https://github.com/R-Rothrock/diatom

#ifndef INFO_H_
#define INFO_H_

// utilized for DICP_REQUEST_INFO and DSCP_RESPONSE
enum info
{
  INFO_FILE,    // files contents, socket contents, etc.
  INFO_STAT,    // stat(2) data
  INFO_INFO_PROCESS, // other process state NOT IMPLEMENTED
  INFO_MEMORY,  // other process memory or registers NOT IMPLEMENTED
} __attribute__((__packed__));
