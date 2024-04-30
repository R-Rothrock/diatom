// env.c
// https://github.com/R-Rothrock/diatom
// running programs in what looks like another computers environment.

#include <asm/unistd_64.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/syscall.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>

#include "data.h"
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
};

int handle_process_syscalls(pid_t pid, pid_t diatom_pid) {
  struct user_regs_struct regs;

  const char *tmp_path = get_tmp_path();

  char *get_str_arg(enum ARG_REGS arg_register); // TODO
  int *get_int_arg(enum ARG_REGS arg_register);  // TODO
  // TODO more of these

  for (;;) {
    // utilizing PTRACE __NREMU increases performance by
    // lowering the amount of mode switches.
    ptrace(PTRACE_SYSEMU, pid, 0, 0);
    waitpid(pid, 0, 0);
    ptrace(PTRACE_GETREGS, pid, 0, &regs);

    /*
     * Some __NRcalls automatically return with error without sending
     * a request. They are:
     *
     * networking:
     *   accept, connect, bind, recvfrom, accept, recvmsg, etc.
     *
     * __NRtem:
     *   reboot, shutdown, swapoff, swapon
     *
     * kernel:
     *   create_module, init_module, delete_module
     *
     * debugging:
     *   ptrace, process_vm_readv, process_vm_writev
     */

#define SYSCALL_RETURN(x)                                                      \
  {                                                                            \
    regs.rax = x;                                                              \
    goto skip;                                                                 \
  }

#define ERROR SYSCALL_RETURN(-1)
#define NOT_IMPLEMENTED ERROR
#define DENIED ERROR

    switch (regs.orig_rax) {
    case __NR_read:
      // TODO
    case __NR_write:
      // TODO
    case __NR_open: {
      // this is my half-baked idea for how this goes.

      // setting the new file descriptor
      struct fd newfd;
      newfd.type = FD_TYPE_FILE;
      newfd.loc = get_str_arg(REGS_RDI);
      newfd.real_loc = tmp_path;

      {
        void *proto_buf =
            dicp(DICP_REQUEST_INFO, diatom_pid, INFO_FILE, newfd.loc);
        sendto_central(proto_buf);
        free(proto_buf);
      }

      struct dscp_response unpacked;

      void *proto_buf = recvfrom_central();

      // expecting DSCP_RESPONSE with matching diatom PID and INFO_FILE,
      // along with a path matching the one given, and, of course, data.

      if (ident_dscp(proto_buf) != DSCP_RESPONSE)
        ERROR;

      struct dscp_response unpacked = unpack_dscp_response(proto_buf);

      if (unpacked.diatom_pid != diatom_pid)
        ERROR;

      else if (unpacked.info != INFO_FILE)
        ERROR;

      else if (strcmp(unpacked.loc, newfd.loc) != 0)
        ERROR;

      // So
      // We are going to add the data of this file descriptor to a
      // file at `newfd.real_loc + newfd.loc`, then we're going to
      // add the file descriptor to the SQLite database in RAM.
      // Finally, we'll free everything used in the process and give
      // the good news of success.

      int ret = setfd(get_nextfd(), newfd);
      if (!ret)
        ERROR;

      char *path = malloc(strlen(newfd.real_loc) + newfd.loc + 1);
      strcat(path, newfd.real_loc);
      strcat(path, newfd.loc);

      FILE *stream = open(path, "wb");
      write(); // TODO

      free(&path) free(&proto_buf);
    }
    case __NR_close: {
      SYSCALL_RETURN(clsfd(get_int_arg(RDI)));
    }
    case __NR_stat:
      // TODO
    case __NR_fstat:
      // TODO
    case __NR_lstat:
      // TODO
    case __NR_poll:
      // TODO
    case __NR_lseek:
      // TODO
    case __NR_mmap:
      // TODO
    case __NR_mprotect:
      // TODO
    case __NR_munmap:
      // TODO
    case __NR_brk:
      // TODO
    case __NR_rt_sigaction:
      // TODO
    case __NR_rt_sigprocmask:
      // TODO
    case __NR_rt_sigreturn:
      // TODO
    case __NR_ioctl:
      // TODO
    case __NR_pread64:
      // TODO
    case __NR_pwrite64:
      // TODO
    case __NR_readv:
      // TODO
    case __NR_writev:
      // TODO
    case __NR_access:
      // TODO
    case __NR_pipe:
      // TODO
    case __NR_select:
      // TODO
    case __NR_sched_yield:
      // TODO
    case __NR_mremap:
      // TODO
    case __NR_mincore:
      // TODO
    case __NR_madvise:
      // TODO
    case __NR_shmget:
      // TODO
    case __NR_shmat:
      // TODO
    case __NR_shmctl:
      // TODO
    case __NR_dup:
      // TODO
    case __NR_dup2:
      // TODO
    case __NR_pause:
      // TODO
    case __NR_nanosleep:
      // TODO
    case __NR_gettimeofday:
      // TODO
    case __NR_alarm:
      // TODO
    case __NR_setitimer:
      // TODO
    case __NR_getpid:
      // TODO
    case __NR_sendfile:
      DENIED
    case __NR_connect:
      DENIED
    case __NR_accept:
      DENIED
    case __NR_sendto:
      DENIED
    case __NR_recvfrom:
      DENIED
    case __NR_sendmsg:
      DENIED
    case __NR_recvmsg:
      DENIED
    case __NR_shutdown:
      DENIED
    case __NR_bind:
      DENIED
    case __NR_listen:
      DENIED
    case __NR_getsockname:
      DENIED
    case __NR_getpeername:
      // TODO
    case __NR_socketpair:
      // TODO
    case __NR_setsockopt:
      // TODO
    case __NR_getsockopt:
      // TODO
    case __NR_clone:
      // TODO
    case __NR_fork:
      // TODO
    case __NR_vfork:
      // TODO
    case __NR_execve:
      // TODO
    case __NR_exit:
      // TODO
    case __NR_wait4:
      // TODO
    case __NR_kill:
      // TODO
    case __NR_uname:
      // TODO
    case __NR_semget:
      // TODO
    case __NR_semop:
      // TODO
    case __NR_semctl:
      // TODO
    case __NR_shmdt:
      // TODO
    case __NR_msgget:
      // TODO
    case __NR_msgctl:
      // TODO
    case __NR_fcntl:
      // TODO
    case __NR_flock:
      // TODO
    case __NR_fsync:
      // TODO
    case __NR_fdatasync:
      // TODO
    case __NR_truncate:
      // TODO
    case __NR_ftruncate:
      // TODO
    case __NR_getdents:
      // TODO
    case __NR_getcwd:
      // TODO
    case __NR_chdir:
      // TODO
    case __NR_fchdir:
      // TODO
    case __NR_rename:
      // TODO
    case __NR_mkdir:
      // TODO
    case __NR_rmdir:
      // TODO
    case __NR_creat:
      // TODO
    case __NR_link:
      // TODO
    case __NR_unlink:
      // TODO
    case __NR_symlink:
      // TODO
    case __NR_readlink:
      // TODO
    case __NR_chmod:
      // TODO
    case __NR_chown:
      // TODO
    case __NR_fchown:
      // TODO
    case __NR_lchown:
      // TODO
    case __NR_umask:
      // TODO
    case __NR_gettimeofday:
      // TODO
    case __NR_getrlimit:
      // TODO
    case __NR_getrusage:
      // TODO
    case __NR: // TODO I don't know which goes here
               // TODO
    case __NR_times:
      // TODO
    case __NR_ptrace:
      DENIED
    case __NR_getuid:
      // TODO
    case __NR: // TODO I don't know which goes here
               // TODO
    case __NR_getgid:
      // TODO
    case __NR_setuid:
      // TODO
    case __NR_setgid:
      // TODO
    case __NR_geteuid:
      // TODO
    case __NR_getegid:
      // TODO
    case __NR_getpgid:
      // TODO
    case __NR_getppid:
      // TODO
    case __NR_getpgrp:
      // TODO
    case __NR_setsid:
      // TODO
    case __NR_setreuid:
      // TODO
    case __NR_setregid:
      // TODO
    case __NR_getgroups:
      // TODO
    case __NR_getgroups:
      // TODO
    case __NR_setresuid:
      // TODO
    case __NR_setresuid:
      // TODO
    case __NR_setresgid:
      // TODO
    case __NR_getresgid:
      // TODO
    case __NR_getpgid:
      // TODO
    case __NR_setfsuid:
      // TODO
    case __NR_getsid:
      // TODO
    case __NR_capget:
      // TODO
    case __NR_capset:
      // TODO
    case __NR_rt_sigpending:
      // TODO
    case __NR_rt_sigtimedwait:
      // TODO
    case __NR_rt_sigqueueinfo:
      // TODO
    case __NR_rt_sigsuspend:
      // TODO
    case __NR_: // TODO fix
                // TODO
    case __NR_utime:
      // TODO
    case __NR_mknod:
      // TODO
    case __NR_uselib:
      // TODO
    case __NR_personality:
      // TODO
    case __NR_ustat:
      // TODO
    case __NR_statfs:
      // TODO
    case __NR_fstatfs:
      // TODO
    case __NR: // TODO fix
               // TODO
    case __NR_getpriority:
      // TODO
    case __NR_setpriority:
      // TODO
    case __NR_sched_setparam:
      // TODO
    case __NR_sched_getparam:
      // TODO
    case __NR_sched_setscheduler:
      // TODO
    case __NR_sched_getscheduler:
      // TODO
    case __NR_sched_get_priority_max:
      // TODO
    case __NR_sched_get_priority_min:
      // TODO
    case __NR_SCHED_RR_GET_INTERVAL: // TODO make all this stuff lowercase
                                     // TODO
    case __NR_MLOCK:
      // TODO
    case __NR_MUNLOCK:
      // TODO
    case __NR_MLOCKALL:
      // TODO
    case __NR_MUNLOCKALL:
      // TODO
    case __NR_VHANGUP:
      // TODO
    case __NR_MODIFY_LDT:
      // TODO
    case __NR_PIVOT_ROOT:
      // TODO
    case __NRCTL:
      // TODO
    case __NR_PRCTL:
      // TODO
    case __NR_ARCH_PRCTL:
      // TODO
    case __NR_ADJTIMEX:
      // TODO
    case __NR_SETRLIMIT:
      // TODO
    case __NR_CHROOT:
      // TODO
    case __NR_SYNC:
      // TODO
    case __NR_ACCT:
      // TODO
    case __NR_SETTIMEOFDAY:
      // TODO
    case __NR_MOUNT:
      // TODO
    case __NR_UMOUNT2:
      // TODO
    case __NR_SWAPON:
      DENIED
    case __NR_SWAPOFF:
      DENIED
    case __NR_REBOOT:
      DENIED
    case __NR_SETHOSTNAME:
      // TODO
    case __NR_SETDOMAINNAME:
      // TODO
    case __NR_IOPL:
      // TODO
    case __NR_IOPERM:
      // TODO
    case __NR_CREATE_MODULE:
      DENIED
    case __NR_INIT_MODULE:
      DENIED
    case __NR_DELETE_MODULE:
      DENIED
    case __NR_QUOTACTL:
      // TODO
    case __NR_GETTID:
      // TODO
    case __NR_READAHEAD:
      // TODO
    case __NR_SETXADDR:
      // TODO
    case __NR_LSETXATTR:
      // TODO
    case __NR_FSETXATTR:
      // TODO
    case __NR_GETXATTR:
      // TODO
    case __NR_LGETXATTR:
      // TODO
    case __NR_FGETXATTR:
      // TODO
    case __NR_LISTXATTR:
      // TODO
    case __NR_FLISTXATTR:
      // TODO
    case __NR_REMOVEXATTR:
      // TODO
    case __NR_FREMOVEXATTR:
      // TODO
    case __NR_TKILL:
      // TODO
    case __NR_TIME:
      // TODO
    case __NR_FUTEX:
      // TODO
    case __NR_SCHED_SETAFFINITY:
      // TODO
    case __NR_SCHED_GETAFFINITY:
      // TODO
    case __NR_SET_THREAD_AREA:
      // TODO
    case __NR_IO_SETUP:
      // TODO
    case __NR_IO_DESTROY:
      // TODO
    case __NR_IO_GETEVENTS:
      // TODO
    case __NR_IO_SUBMIT:
      // TODO
    case __NR_IO_CANCEL:
      // TODO
    case __NR_GET_THREAD_AERA:
      // TODO
    case __NR_LOOKUP_DCOOKIE:
      // TODO
    case __NR_EPOLL_CREATE:
      // TODO
    case __NR_EPOLL_CTL_OLD:
      // TODO
    case __NR_EPOLL_WAIT_OLD:
      // TODO
    case __NR_REMAP_FILE_PAGES:
      // TODO
    case __NR_GETDENTS64:
      // TODO
    case __NR_SET_TID_ADDRESS:
      // TODO
    case __NR_RESTART __NRCALL:
      // TODO
    case __NR_SEMTIMEDOP:
      // TODO
    case __NR_FADVISE64:
      // TODO
    case __NR_TIMER_CREATE:
      // TODO
    case __NR_TIMER_SETTIME:
      // TODO
    case __NR_TIMER_GETTIME:
      // TODO
    case __NR_TIMER_GETOVERRUN:
      // TODO
    case __NR_TIMER_DELETE:
      // TODO
    case __NR_CLOCK_SETTIME:
      // TODO
    case __NR_CLOCK_GETTIME:
      // TODO
    case __NR_GETRES:
      // TODO
    case __NR_CLOCK_NANOSLEEP:
      // TODO
    case __NR_EXIT_GROUP:
      // TODO
    case __NR_EPOLL_WAIT:
      // TODO
    case __NR_EPOLL_CTL:
      // TODO
    case __NR_TGKILL:
      // TODO
    case __NR_UTIMES:
      // TODO
    case __NR_MBIND:
      // TODO
    case __NR_SET_MEMPOLICY:
      // TODO
    case __NR_GET_MEMPOLICY:
      // TODO
    case __NR_MQ_OPEN:
      // TODO
    case __NR_MQ_UNLINK:
      // TODO
    case __NR_MQ_TIMEDSEND:
      // TODO
    case __NR_MQ_TIMEDRECEIVE:
      // TODO
    case __NR_MQ_NOTIFY:
      // TODO
    case __NR_GETSETATTR:
      // TODO
    case __NR_KEXEC_LOAD:
      // TODO
    case __NR_WAITID:
      // TODO
    case __NR_ADD_KEY:
      // TODO
    case __NR_REQUEST_KEY:
      // TODO
    case __NR_KEYCTL:
      // TODO
    case __NR_IOPRIO_SET:
      // TODO
    case __NR_IOPRIO_GET:
      // TODO
    case __NR_INOTIFY_INIT:
      // TODO
    case __NR_INOTIFY_ADD_WATCH:
      // TODO
    case __NR_INOTIFY_RM_WATCH:
      // TODO
    case __NR_MIGRATE_PAGES:
      // TODO
    case __NR_OPENAT:
      // TODO
    case __NR_MKDIRAT:
      // TODO
    case __NR_MKNODAT:
      // TODO
    case __NR_FCHWONAT:
      // TODO
    case __NR_FUTIMESAT:
      // TODO
    case __NR_NEWFSTATAT:
      // TODO
    case __NR_UNLINKAT:
      // TODO
    case __NR_RENAMEAT:
      // TODO
    case __NR_LINKAT:
      // TODO
    case __NR_SYMLINKAT:
      // TODO
    case __NR_READLINKAT:
      // TODO
    case __NR_FCHMODAT:
      // TODO
    case __NR_FACCESSAT:
      // TODO
    case __NR_PSELECT6:
      // TODO
    case __NR_PPOLL:
      // TODO
    case __NR_UNSHARE:
      // TODO
    case __NR_SET_ROBUST_LIST:
      // TODO
    case __NR_GET_ROBUST_LIST:
      // TODO
    case __NR_SPLICE:
      // TODO
    case __NR_TEE:
      // TODO
    case __NR_SYNC_FILE_RANGE:
      // TODO
    case __NR_VMSPLICE:
      // TODO
    case __NR_MOVE_PAGES:
      // TODO
    case __NR_UTIMENSAT:
      // TODO
    case __NR_EPOLL_PWAIT:
      // TODO
    case __NR_SIGNALFD:
      // TODO
    case __NR_TIMERFD_CREATE:
      // TODO
    case __NR_EVENTFD:
      // TODO
    case __NR_FALLOCATE:
      // TODO
    case __NR_TIMERFD_SETTIME:
      // TODO
    case __NR_TIMERFD_GETTIME:
      // TODO
    case __NR_ACCEPT4:
      // TODO
    case __NR_SIGNALFD4:
      // TODO
    case __NR_EVENTFD2:
      // TODO
    case __NR_EPOLL_CREATE1:
      // TODO
    case __NR_DUP3:
      // TODO
    case __NR_PIPE2:
      // TODO
    case __NR_INOTIFY_INIT1:
      // TODO
    case __NR_PREADV:
      // TODO
    case __NR_PWRITEV:
      // TODO
    case __NR_RT_TGSIGQUEUEINFO:
      // TODO
    case __NR_PERF_EVENT_OPEN:
      // TODO
    case __NR_RECVMSG:
      // TODO
    case __NR_FANOTIFY_INIT:
      // TODO
    case __NR_FANOTIFY_MARK:
      // TODO
    case __NR_PRLIMIT64:
      // TODO
    case __NR_NAME_TO_HANDLE_AT:
      // TODO
    case __NR_OPEN_TO_HANDLE_AT:
      // TODO
    case __NR_CLOCK_ADJTIME:
      // TODO
    case __NR_SYNCFS:
      // TODO
    case __NR_SENDMMSG:
      DENIED
    case __NR_SETNS:
      // TODO
    case __NR_GETCPU:
      // TODO
    case __NR_PROCESS_VM_READY:
      DENIED
    case __NR_PROCESS_VM_WRITEV:
      DENIED
    case __NR_KCMP:
      // TODO
    case __NR_FINIT_MODULE:
      DENIED
    default:
      // TODO
    }
  skip:
    ptrace(PTRACE_SETREGS, pid, 0, &regs);
  }
  return 0;
}
