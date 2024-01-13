// handler.h
// https://github.com/R-Rothrock/diatom

#include "deps.h"

void *get_req(int sockfd)
{
  // TODO
}

int send_req(int sockfd)
{
  // TODO
}

int handle_request(int sockfd)
{
  void *buf = get_req();

  enum dicp_req req_type = ident_dicp(buf);
  // note: some syscalls will automatically return with EPERM without
  // a request being sent
  // nevertheless, all syscalls will be acknowledged here
  // info about such syscalls is in
  // `diatom-client/env.c:handle_process_syscall`
  switch(req_type)
  {
    case SYS_READ:
      // TODO
    case SYS_WRITE:
      // TODO
    case SYS_OPEN:
      // TODO
    case SYS_CLOSE:
      // TODO
    case SYS_STAT:
      // TODO
    case SYS_FSTAT:
      // TODO
    case SYS_LSTAT:
      // TODO
    case SYS_POLL:
      // TODO
    case SYS_LSEEK:
      // TODO
    case SYS_MMAP:
      // TODO
    case SYS_MPROTECT:
      // TODO
    case SYS_MUNMAP:
      // TODO
    case SYS_BRK:
      // TODO
    case SYS_RT_SIGACTION:
      // TODO
    case SYS_RT_SIGPROCMASK:
      // TODO
    case SYS_RT_SIGRETURN:
      // TODO
    case SYS_IOCTL:
      // TODO
    case SYS_PREAD64:
      // TODO
    case SYS_WRITE64:
      // TODO
    case SYS_READV:
      // TODO
    case SYS_WRITEV:
      // TODO
    case SYS_ACCESS:
      // TODO
    case SYS_PIPE:
      // TODO
    case SYS_SELECT:
      // TODO
    case SYS_SCHED_YIELD:
      // TODO
    case SYS_MREMAP:
      // TODO
    case SYS_MINCORE:
      // TODO
    case SYS_MADVISE:
      // TODO
    case SYS_SHMGET:
      // TODO
    case SYS_DUP:
      // TODO
    case SYS_DUP2:
      // TODO
    case SYS_PAUSE:
      // TODO
    case SYS_NANOSLEEP:
      // TODO
    case SYS_GETITIMER:
      // TODO
    case SYS_ALARM:
      // TODO
    case SYS_SETITIMER:
      // TODO
    case SYS_GETPID:
      // TODO
    case SYS_SENDFILE:
      // TODO
    case SYS_CONNECT:
      // TODO
    case SYS_ACCEPT:
      // TODO
    case SYS_SENDTO:
      // TODO
    case SYS_RECVFROM:
      // TODO
    case SYS_SENDMSG:
      // TODO
    case SYS_RECVMSG:
      // TODO
    // TODO add remaining syscalls
  }
}
