// env.c
// https://github.com/R-Rothrock/diatom
// running programs in what looks like another computers environment.

#include<stdlib.h>
#include<sys/ptrace.h>
#include<sys/syscall.h>
#include<sys/wait.h>
#include<unistd.h>

#include "deps.h"

pid_t start_process(char **argv, char **envp)
{
  pid_t pid = fork();

  switch(pid)
  {
    case -1:
      return -1; // errno is set
    case 0:
      ptrace(PTRACE_TRACEME, 0, 0, 0);
      execve(argv[1], argv, envp);
  }

  waitpid(pid, 0, 0);

  ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_EXITKILL);

  return pid;
}

int handle_process_syscall(pid_t pid, int sockfd)
{
  // utilizing PTRACE_SYSEMU saves us a context switch
  ptrace(PTRACE_SYSEMU, pid, 0, 0);
  waitpid(pid, 0, 0);

  struct user_regs_struct regs;
  ptrace(PTRACE_GETREGS, pid, 0, &regs);

  // some syscalls will automatically return with EPERM
  // socket, connect, accept
  switch(regs.orig_rax)
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
    case SYS_SHMAT:
      // TODO
    case SYS_SHMCTL:
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
    // TODO add the remaining syscalls.
  }

 // TODO finish PTRACE_SYSEMU implementation 

  return 0;
}

