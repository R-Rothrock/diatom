// env.c
// https://github.com/R-Rothrock/diatom
// running programs in what looks like another computers environment.

#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <unistd.h>

#include "data.h"
#include "deps.h"
#include "fds.c"
#include "handler.c"

pid_t start_process(char **argv, char **envp) {
  pid_t pid = fork();

  switch (pid) {
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

enum arg_regs {
  REGS_RDI,
  REGS_RSI,
  REGS_RDX,
  REGS_R8,
  REGS_R9,
}

int handle_process_syscalls(pid_t pid, pid_t diatom_pid) {
  struct user_regs_struct regs;

  const char *tmp_path = get_tmp_path();

  char *get_str_arg(enum ARG_REGS arg_register); // TODO
  int *get_int_arg(enum ARG_REGS arg_register);  // TODO
  // TODO more of these

  for (;;) {
    // utilizing PTRACE_SYSEMU increases performance by
    // lowering the amount of mode switches.
    ptrace(PTRACE_SYSEMU, pid, 0, 0);
    waitpid(pid, 0, 0);
    ptrace(PTRACE_GETREGS, pid, 0, &regs);

    /*
     * Some syscalls automatically return with error without sending
     * a request. They are:
     *
     * networking:
     *   accept, connect, bind, recvfrom, accept, recvmsg, etc.
     *
     * system:
     *   reboot, shutdown, swapoff, swapon
     *
     * kernel:
     *   create_module, init_module, delete_module
     *
     * debugging:
     *   ptrace, process_vm_readv, process_vm_writev
     */

#define DENIED                                                                 \
  {                                                                            \
    regs.rax = -1;                                                             \
    goto skip;                                                                 \
  }
#define NOT_IMPLEMENTED                                                        \
  {                                                                            \
    regs.rax = -1;                                                             \
    goto skip;                                                                 \
  }
#define ERROR                                                                  \
  {                                                                            \
    regs.rax = -1;                                                             \
    goto skip;                                                                 \
  }

    switch (regs.orig_rax) {
    case SYS_READ:

      int fd = &get_int_arg(RDI);
      void *proto_buf =
          dicp(DICP_REQUEST_INFO, diatom_pid, INFO_FILE, getfd(fd));

      sendto_central(proto_buf);

      free(proto_buf);

      // TODO

    case SYS_WRITE:
      // TODO
    case SYS_OPEN:
      // this is my half-baked idea for how this goes.

      // setting the new file descriptor
      struct fd newfd;
      newfd.type = FD_TYPE_FILE;
      newfd.loc = get_str_arg(RDI);
      newfd.realloc = tmp_path;

      {
        void *proto_buf =
            dicp(DICP_REQUEST_INFO, diatom_pid, INFO_FILE, newfd.loc);
        sendto_central(proto_buf);
        free(proto_buf);
      }

      {
        void *proto_buf = recvfrom_central();

        // expecting DSCP_RESPONSE with matching diatom PID and INFO_FILE,
        // along with a path matching the one given, and, of course, data.

        if (ident_dscp(proto_buf) != DSCP_RESPONSE) {
          ERROR;
        }

        struct dscp_response unpacked = unpack_dscp_response(proto_buf);

        if (unpacked.diatom_pid != diatom_pid) {
          ERROR;
        } else if (unpacked.info != INFO_FILE) {
          ERROR;
        } else if (unpacked.loc != newfd.loc) {
          ERROR;
        }

        // writing received data to file `newfd.realloc + newfd.loc`
        // TODO
      }

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
      DENIED
    case SYS_CONNECT:
      DENIED
    case SYS_ACCEPT:
      DENIED
    case SYS_SENDTO:
      DENIED
    case SYS_RECVFROM:
      DENIED
    case SYS_SENDMSG:
      DENIED
    case SYS_RECVMSG:
      DENIED
    case SYS_SHUTDOWN:
      DENIED
    case SYS_BIND:
      DENIED
    case SYS_LISTEN:
      DENIED
    case SYS_GETSOCKNAME:
      DENIED
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
      // TODO
    case SYS_GETRLIMIT:
      // TODO
    case SYS_GETRUSAGE:
      // TODO
    case SYS_SYSINFO:
      // TODO
    case SYS_TIMES:
      // TODO
    case SYS_PTRACE:
      DENIED
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
      DENIED
    case SYS_SWAPOFF:
      DENIED
    case SYS_REBOOT:
      DENIED
    case SYS_SETHOSTNAME:
      // TODO
    case SYS_SETDOMAINNAME:
      // TODO
    case SYS_IOPL:
      // TODO
    case SYS_IOPERM:
      // TODO
    case SYS_CREATE_MODULE:
      DENIED
    case SYS_INIT_MODULE:
      DENIED
    case SYS_DELETE_MODULE:
      DENIED
    case SYS_QUOTACTL:
      // TODO
    case SYS_GETTID:
      // TODO
    case SYS_READAHEAD:
      // TODO
    case SYS_SETXADDR:
      // TODO
    case SYS_LSETXATTR:
      // TODO
    case SYS_FSETXATTR:
      // TODO
    case SYS_GETXATTR:
      // TODO
    case SYS_LGETXATTR:
      // TODO
    case SYS_FGETXATTR:
      // TODO
    case SYS_LISTXATTR:
      // TODO
    case SYS_FLISTXATTR:
      // TODO
    case SYS_REMOVEXATTR:
      // TODO
    case SYS_FREMOVEXATTR:
      // TODO
    case SYS_TKILL:
      // TODO
    case SYS_TIME:
      // TODO
    case SYS_FUTEX:
      // TODO
    case SYS_SCHED_SETAFFINITY:
      // TODO
    case SYS_SCHED_GETAFFINITY:
      // TODO
    case SYS_SET_THREAD_AREA:
      // TODO
    case SYS_IO_SETUP:
      // TODO
    case SYS_IO_DESTROY:
      // TODO
    case SYS_IO_GETEVENTS:
      // TODO
    case SYS_IO_SUBMIT:
      // TODO
    case SYS_IO_CANCEL:
      // TODO
    case SYS_GET_THREAD_AERA:
      // TODO
    case SYS_LOOKUP_DCOOKIE:
      // TODO
    case SYS_EPOLL_CREATE:
      // TODO
    case SYS_EPOLL_CTL_OLD:
      // TODO
    case SYS_EPOLL_WAIT_OLD:
      // TODO
    case SYS_REMAP_FILE_PAGES:
      // TODO
    case SYS_GETDENTS64:
      // TODO
    case SYS_SET_TID_ADDRESS:
      // TODO
    case SYS_RESTART_SYSCALL:
      // TODO
    case SYS_SEMTIMEDOP:
      // TODO
    case SYS_FADVISE64:
      // TODO
    case SYS_TIMER_CREATE:
      // TODO
    case SYS_TIMER_SETTIME:
      // TODO
    case SYS_TIMER_GETTIME:
      // TODO
    case SYS_TIMER_GETOVERRUN:
      // TODO
    case SYS_TIMER_DELETE:
      // TODO
    case SYS_CLOCK_SETTIME:
      // TODO
    case SYS_CLOCK_GETTIME:
      // TODO
    case SYS_GETRES:
      // TODO
    case SYS_CLOCK_NANOSLEEP:
      // TODO
    case SYS_EXIT_GROUP:
      // TODO
    case SYS_EPOLL_WAIT:
      // TODO
    case SYS_EPOLL_CTL:
      // TODO
    case SYS_TGKILL:
      // TODO
    case SYS_UTIMES:
      // TODO
    case SYS_MBIND:
      // TODO
    case SYS_SET_MEMPOLICY:
      // TODO
    case SYS_GET_MEMPOLICY:
      // TODO
    case SYS_MQ_OPEN:
      // TODO
    case SYS_MQ_UNLINK:
      // TODO
    case SYS_MQ_TIMEDSEND:
      // TODO
    case SYS_MQ_TIMEDRECEIVE:
      // TODO
    case SYS_MQ_NOTIFY:
      // TODO
    case SYS_GETSETATTR:
      // TODO
    case SYS_KEXEC_LOAD:
      // TODO
    case SYS_WAITID:
      // TODO
    case SYS_ADD_KEY:
      // TODO
    case SYS_REQUEST_KEY:
      // TODO
    case SYS_KEYCTL:
      // TODO
    case SYS_IOPRIO_SET:
      // TODO
    case SYS_IOPRIO_GET:
      // TODO
    case SYS_INOTIFY_INIT:
      // TODO
    case SYS_INOTIFY_ADD_WATCH:
      // TODO
    case SYS_INOTIFY_RM_WATCH:
      // TODO
    case SYS_MIGRATE_PAGES:
      // TODO
    case SYS_OPENAT:
      // TODO
    case SYS_MKDIRAT:
      // TODO
    case SYS_MKNODAT:
      // TODO
    case SYS_FCHWONAT:
      // TODO
    case SYS_FUTIMESAT:
      // TODO
    case SYS_NEWFSTATAT:
      // TODO
    case SYS_UNLINKAT:
      // TODO
    case SYS_RENAMEAT:
      // TODO
    case SYS_LINKAT:
      // TODO
    case SYS_SYMLINKAT:
      // TODO
    case SYS_READLINKAT:
      // TODO
    case SYS_FCHMODAT:
      // TODO
    case SYS_FACCESSAT:
      // TODO
    case SYS_PSELECT6:
      // TODO
    case SYS_PPOLL:
      // TODO
    case SYS_UNSHARE:
      // TODO
    case SYS_SET_ROBUST_LIST:
      // TODO
    case SYS_GET_ROBUST_LIST:
      // TODO
    case SYS_SPLICE:
      // TODO
    case SYS_TEE:
      // TODO
    case SYS_SYNC_FILE_RANGE:
      // TODO
    case SYS_VMSPLICE:
      // TODO
    case SYS_MOVE_PAGES:
      // TODO
    case SYS_UTIMENSAT:
      // TODO
    case SYS_EPOLL_PWAIT:
      // TODO
    case SYS_SIGNALFD:
      // TODO
    case SYS_TIMERFD_CREATE:
      // TODO
    case SYS_EVENTFD:
      // TODO
    case SYS_FALLOCATE:
      // TODO
    case SYS_TIMERFD_SETTIME:
      // TODO
    case SYS_TIMERFD_GETTIME:
      // TODO
    case SYS_ACCEPT4:
      // TODO
    case SYS_SIGNALFD4:
      // TODO
    case SYS_EVENTFD2:
      // TODO
    case SYS_EPOLL_CREATE1:
      // TODO
    case SYS_DUP3:
      // TODO
    case SYS_PIPE2:
      // TODO
    case SYS_INOTIFY_INIT1:
      // TODO
    case SYS_PREADV:
      // TODO
    case SYS_PWRITEV:
      // TODO
    case SYS_RT_TGSIGQUEUEINFO:
      // TODO
    case SYS_PERF_EVENT_OPEN:
      // TODO
    case SYS_RECVMSG:
      // TODO
    case SYS_FANOTIFY_INIT:
      // TODO
    case SYS_FANOTIFY_MARK:
      // TODO
    case SYS_PRLIMIT64:
      // TODO
    case SYS_NAME_TO_HANDLE_AT:
      // TODO
    case SYS_OPEN_TO_HANDLE_AT:
      // TODO
    case SYS_CLOCK_ADJTIME:
      // TODO
    case SYS_SYNCFS:
      // TODO
    case SYS_SENDMMSG:
      DENIED
    case SYS_SETNS:
      // TODO
    case SYS_GETCPU:
      // TODO
    case SYS_PROCESS_VM_READY:
      DENIED
    case SYS_PROCESS_VM_WRITEV:
      DENIED
    case SYS_KCMP:
      // TODO
    case SYS_FINIT_MODULE:
      DENIED
    default:
      // TODO
    }
  skip:
    ptrace(PTRACE_SETREGS, pid, 0, &regs);
  }
  return 0;
}
