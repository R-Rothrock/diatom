// env.c
// https://github.com/R-Rothrock/diatom
// running programs in what looks like another computers environment.

#include<stdlib.h>
#include<sys/ptrace.h>
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

  switch(regs.orig_rax)
  {
    case OS_READ:
      // TODO
    case OS_WRITE:
      // TODO
    case OS_OPEN:
      // TODO
    case OS_CLOSE:
      // TODO
    case OS_STAT:
      // TODO
    case OS_FSTAT:
      // TODO
    case OS_LSTAT:
      // TODO
    case OS_POLL:
      // TODO
    // and many more...
  }

  return 0;
}

