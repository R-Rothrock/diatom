// info.h
// https://github.com/R-Rothrock/diatom

#ifndef INFO_H_
#define INFO_H_

// utilized for DICP_REQUEST_INFO and DSCP_RESPONSE
enum info
{
  INFO_FILE,          // files for I/O
  INFO_STRUCT_STAT,   // `struct stat` for *stat
  INFO_STRUCT_POLLFD, // `struct pollfd` for poll
  INFO_SIGACTION      // sigaction info
  INFO_SIGPROCMASK    // sigprocmask info
  INFO_SIGRETURN      // sigreturn info
  INFO_IOCTL          // ioctl info
  INFO_STRUCT_IOVEC   // `struct iovec` for *(read|write)v*
  INFO_ACCESS         // access info
  INFO_PIPE           // pipe info
  // TODO
} __attribute__((__packed__));
