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
  struct user_regs_struct regs
  for(;;)
  {
    // utilizing PTRACE_SYSEMU increases performance by
    // lowering the amount of context switches.
    ptrace(PTRACE_SYSEMU, pid, 0, 0);
    waitpid(pid, 0, 0);
    ptrace(PTRACE_GETREGS, pid, 0, &regs);

    /*
     * Some syscalls automatically return with EPERM without sending
     * a request. They are:
     *
     * bind, sendto, recvfrom,
     */
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
      case SYS_SHUTDOWN:
        // TODO
      case SYS_BIND:
        // TODO
      case SYS_LISTEN:
        // TODO
      case SYS_GETSOCKNAME:
        // TODO
      case SYS_GETPEERNAME:
        // TODO
      case SYS_SOCKETPAIR:
        // TODO
      case SYS_SETSOCKOPT:
        // TODO
      case SYS_GETSOCKOPT:
        // TODO
      case SYS_CLONE:
        // TODO
      case SYS_FORK:
        // TODO
      case SYS_VFORK:
        // TODO
      case SYS_EXECVE:
        // TODO
      case SYS_EXIT:
        // TODO
      case SYS_WAIT4:
        // TODO
      case SYS_KILL:
        // TODO
      case SYS_UNAME:
        // TODO
      case SYS_SEMGET:
        // TODO
      case SYS_SEMOP:
        // TODO
      case SYS_SEMCTL:
        // TODO
      case SYS_SHMDT:
        // TODO
      case SYS_MSGGET:
        // TODO
      case SYS_MSGCTL:
        // TODO
      case SYS_FCNTL:
        // TODO
      case SYS_FLOCK:
        // TODO
      case SYS_FSYNC:
        // TODO
      case SYS_FDATASYNC:
        // TODO
      case SYS_TRUNCATE:
        // TODO
      case SYS_FTRUNCATE:
        // TODO
      case SYS_GETDENTS:
        // TODO
      case SYS_GETCWD:
        // TODO
      case SYS_CHDIR:
        // TODO
      case SYS_FCHDIR:
        // TODO
      case SYS_RENAME:
        // TODO
      case SYS_MKDIR:
        // TODO
      case SYS_RMDIR:
        // TODO
      case SYS_CREAT:
        // TODO
      case SYS_LINK:
        // TODO
      case SYS_UNLINK:
        // TODO
      case SYS_SYMLINK:
        // TODO
      case SYS_READLINK:
        // TODO
      case SYS_CHMOD:
        // TODO
      case SYS_CHOWN:
        // TODO
      case SYS_FCHOWN:
        // TODO
      case SYS_LCHOWN:
        // TODO
      case SYS_UMASK:
        // TODO
      case SYS_GETTIMEOFDAY:
        // TODO fyi this syscall doesn't context switch
      case SYS_GETRLIMIT:
        // TODO
      case SYS_GETRUSAGE:
        // TODO
      case SYS_SYSINFO:
        // TODO
      case SYS_TIMES:
        // TODO
      case SYS_PTRACE:
        // TODO
      case SYS_GETUID:
        // TODO
      case SYS_SYSLOG:
        // TODO
      case SYS_GETGID:
        // TODO
      case SYS_SETUID:
        // TODO
      case SYS_SETGID:
        // TODO
      case SYS_GETEUID:
        // TODO
      case SYS_GETEGID:
        // TODO
      case SYS_SETPGID:
        // TODO
      case SYS_GETPPID:
        // TODO
      case SYS_GETPGRP:
        // TODO
      case SYS_SETSID:
        // TODO
      case SYS_SETREUID:
        // TODO
      case SYS_SETREGID:
        // TODO
      case SYS_GETGROUPS:
        // TODO
      case SYS_SETGROUPS:
        // TODO
      case SYS_SETRESUID:
        // TODO
      case SYS_GETRESUID:
        // TODO
      case SYS_SETRESGID:
        // TODO
      case SYS_GETRESGID:
        // TODO
      case SYS_GETPGID:
        // TODO
      case SYS_SETFSUID:
        // TODO
      case SYS_GETSID:
        // TODO
      case SYS_CAPGET:
        // TODO
      case SYS_CAPSET:
        // TODO
      case SYS_RT_SIGPENDING:
        // TODO
      case SYS_RT_SIGTIMEDWAIT:
        // TODO
      case SYS_RT_SIGQUEUEINFO:
        // TODO
      case SYS_RT_SIGSUSPEND:
        // TODO
      case SYS_SIGNALSTACK:
        // TODO
      case SYS_UTIME:
        // TODO
      case SYS_MKNOD:
        // TODO
      case SYS_USELIB:
        // TODO
      case SYS_PERSONALITY:
        // TODO
      case SYS_USTAT:
        // TODO
      case SYS_STATFS:
        // TODO
      case SYS_FSTATFS:
        // TODO
      case SYS_SYSFS:
        // TODO
      case SYS_GETPRIORITY:
        // TODO
      case SYS_SETPRIORITY:
        // TODO
      case SYS_SCHED_SETPARAM:
        // TODO
      case SYS_SCHED_GETPARAM:
        // TODO
      case SYS_SCHED_SETSCHEDULER:
        // TODO
      case SYS_SCHED_GETSCHEDULER:
        // TODO
      case SYS_SCHED_GET_PRIORITY_MAX:
        // TODO
      case SYS_SCHED_GET_PRIORITY_MIN:
        // TODO
      case SYS_SCHED_RR_GET_INTERVAL:
        // TODO
      case SYS_MLOCK:
        // TODO
      case SYS_MUNLOCK:
        // TODO
      case SYS_MLOCKALL:
        // TODO
      case SYS_MUNLOCKALL:
        // TODO
      case SYS_VHANGUP:
        // TODO
      case SYS_MODIFY_LDT:
        // TODO
      case SYS_PIVOT_ROOT:
        // TODO
      case SYS_SYSCTL:
        // TODO
      case SYS_PRCTL:
        // TODO
      case SYS_ARCH_PRCTL:
        // TODO
      case SYS_ADJTIMEX:
        // TODO
      case SYS_SETRLIMIT:
        // TODO
      case SYS_CHROOT:
        // TODO
      case SYS_SYNC:
        // TODO
      case SYS_ACCT:
        // TODO
      case SYS_SETTIMEOFDAY:
        // TODO
      case SYS_MOUNT:
        // TODO
      case SYS_UMOUNT2:
        // TODO
      case SYS_SWAPON:
        // TODO EPERM
      case SYS_SWAPOFF:
        // TODO EPERM
      case SYS_REBOOT:
        // TODO EPERM
      case SYS_SETHOSTNAME:
        // TODO
      case SYS_SETDOMAINNAME:
        // TODO
      case SYS_IOPL:
        // TODO
      case SYS_IOPERM:
        // TODO
      case SYS_CREATE_MODULE:
        // TODO EPERM
      case SYS_INIT_MODULE:
        // TODO EPERM
      case DELETE_MODULE:
        // TODO EPERM
      // TODO add remaining syscalls
      
    }
  }

  ptrace(PTRACE_SETREGS, pid, 0, &regs);  

  return 0;
}

