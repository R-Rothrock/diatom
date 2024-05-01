// env.c
// https://github.com/R-Rothrock/diatom
// running programs in what looks like another computers environment.

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

  char *get_str_arg(enum arg_regs arg_register); // TODO
  int *get_int_arg(enum arg_regs arg_register);  // TODO
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

#define SYSCALL_RETURN(x)                                                      \
  {                                                                            \
    regs.rax = x;                                                              \
    goto skip;                                                                 \
  }

#define ERROR SYSCALL_RETURN(-1)
#define NOT_IMPLEMENTED ERROR
#define DENIED ERROR

    switch (regs.orig_rax) {
    case SYS_read:
      // TODO
    case SYS_write:
      // TODO
    case SYS_open: {
      // this is my idea for how this goes
      // _seems_ air tight...

      // setting the new file descriptor
      struct fd newfd;

      newfd.type = FD_TYPE_FILE;
      newfd.flags = newfd.flags ^ newfd.flags;
      newfd.index = newfd.index ^ newfd.index;
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
      if (ret != 0)
        ERROR;

      char *path = malloc(strlen(newfd.real_loc) + newfd.loc + 1);
      strcat(path, newfd.real_loc);
      strcat(path, newfd.loc);

      FILE *stream = fopen(path, "wb");
      if (!stream)
        ERROR;

      ret = write(unpacked.data, strlen(unpacked.data) + 1, 1, stream);
      if (ret != 0)
        ERROR;

      // coast clear

      fclose(stream);

      free(&path);
      free(&proto_buf);

      SYSCALL_RETURN(0);
    }
    case SYS_close: {
      SYSCALL_RETURN(clsfd(get_int_arg(RDI)));
    }
    case SYS_stat:
      // TODO
    case SYS_fstat:
      // TODO
    case SYS_lstat:
      // TODO
    case SYS_poll:
      // TODO
    case SYS_lseek:
      // TODO
    case SYS_mmap:
      // TODO
    case SYS_mprotect:
      // TODO
    case SYS_munmap:
      // TODO
    case SYS_brk:
      // TODO
    case SYS_rt_sigaction:
      // TODO
    case SYS_rt_sigprocmask:
      // TODO
    case SYS_rt_sigreturn:
      // TODO
    case SYS_ioctl:
      // TODO
    case SYS_pread64:
      // TODO
    case SYS_pwrite64:
      // TODO
    case SYS_readv:
      // TODO
    case SYS_writev:
      // TODO
    case SYS_access:
      // TODO
    case SYS_pipe:
      // TODO
    case SYS_select:
      // TODO
    case SYS_sched_yield:
      // TODO
    case SYS_mremap:
      // TODO
    case SYS_mincore:
      // TODO
    case SYS_madvise:
      // TODO
    case SYS_shmget:
      // TODO
    case SYS_shmat:
      // TODO
    case SYS_shmctl:
      // TODO
    case SYS_dup:
      // TODO
    case SYS_dup2:
      // TODO
    case SYS_pause:
      // TODO
    case SYS_nanosleep:
      // TODO
    case SYS_gettimeofday:
      // TODO
    case SYS_alarm:
      // TODO
    case SYS_setitimer:
      // TODO
    case SYS_getpid:
      // TODO
    case SYS_sendfile:
      DENIED
    case SYS_connect:
      DENIED
    case SYS_accept:
      DENIED
    case SYS_sendto:
      DENIED
    case SYS_recvfrom:
      DENIED
    case SYS_sendmsg:
      DENIED
    case SYS_recvmsg:
      DENIED
    case SYS_shutdown:
      DENIED
    case SYS_bind:
      DENIED
    case SYS_listen:
      DENIED
    case SYS_getsockname:
      DENIED
    case SYS_getpeername:
      // TODO
    case SYS_socketpair:
      // TODO
    case SYS_setsockopt:
      // TODO
    case SYS_getsockopt:
      // TODO
    case SYS_clone:
      // TODO
    case SYS_fork:
      // TODO
    case SYS_vfork:
      // TODO
    case SYS_execve:
      // TODO
    case SYS_exit:
      // TODO
    case SYS_wait4:
      // TODO
    case SYS_kill:
      // TODO
    case SYS_uname:
      // TODO
    case SYS_semget:
      // TODO
    case SYS_semop:
      // TODO
    case SYS_semctl:
      // TODO
    case SYS_shmdt:
      // TODO
    case SYS_msgget:
      // TODO
    case SYS_msgctl:
      // TODO
    case SYS_fcntl:
      // TODO
    case SYS_flock:
      // TODO
    case SYS_fsync:
      // TODO
    case SYS_fdatasync:
      // TODO
    case SYS_truncate:
      // TODO
    case SYS_ftruncate:
      // TODO
    case SYS_getdents:
      // TODO
    case SYS_getcwd:
      // TODO
    case SYS_chdir:
      // TODO
    case SYS_fchdir:
      // TODO
    case SYS_rename:
      // TODO
    case SYS_mkdir:
      // TODO
    case SYS_rmdir:
      // TODO
    case SYS_creat:
      // TODO
    case SYS_link:
      // TODO
    case SYS_unlink:
      // TODO
    case SYS_symlink:
      // TODO
    case SYS_readlink:
      // TODO
    case SYS_chmod:
      // TODO
    case SYS_chown:
      // TODO
    case SYS_fchown:
      // TODO
    case SYS_lchown:
      // TODO
    case SYS_umask:
      // TODO
    case SYS_gettimeofday:
      // TODO
    case SYS_getrlimit:
      // TODO
    case SYS_getrusage:
      // TODO
    case SYS: // TODO I don't know which goes here
      // TODO
    case SYS_times:
      // TODO
    case SYS_ptrace:
      DENIED
    case SYS_getuid:
      // TODO
    case SYS: // TODO I don't know which goes here
      // TODO
    case SYS_getgid:
      // TODO
    case SYS_setuid:
      // TODO
    case SYS_setgid:
      // TODO
    case SYS_geteuid:
      // TODO
    case SYS_getegid:
      // TODO
    case SYS_getpgid:
      // TODO
    case SYS_getppid:
      // TODO
    case SYS_getpgrp:
      // TODO
    case SYS_setsid:
      // TODO
    case SYS_setreuid:
      // TODO
    case SYS_setregid:
      // TODO
    case SYS_getgroups:
      // TODO
    case SYS_getgroups:
      // TODO
    case SYS_setresuid:
      // TODO
    case SYS_setresuid:
      // TODO
    case SYS_setresgid:
      // TODO
    case SYS_getresgid:
      // TODO
    case SYS_getpgid:
      // TODO
    case SYS_setfsuid:
      // TODO
    case SYS_getsid:
      // TODO
    case SYS_capget:
      // TODO
    case SYS_capset:
      // TODO
    case SYS_rt_sigpending:
      // TODO
    case SYS_rt_sigtimedwait:
      // TODO
    case SYS_rt_sigqueueinfo:
      // TODO
    case SYS_rt_sigsuspend:
      // TODO
    case SYS_: // TODO fix
      // TODO
    case SYS_utime:
      // TODO
    case SYS_mknod:
      // TODO
    case SYS_uselib:
      // TODO
    case SYS_personality:
      // TODO
    case SYS_ustat:
      // TODO
    case SYS_statfs:
      // TODO
    case SYS_fstatfs:
      // TODO
    case SYS: // TODO fix
      // TODO
    case SYS_getpriority:
      // TODO
    case SYS_setpriority:
      // TODO
    case SYS_sched_setparam:
      // TODO
    case SYS_sched_getparam:
      // TODO
    case SYS_sched_setscheduler:
      // TODO
    case SYS_sched_getscheduler:
      // TODO
    case SYS_sched_get_priority_max:
      // TODO
    case SYS_sched_get_priority_min:
      // TODO
    case SYS_sched_rr_get_interval:
      // TODO
    case SYS_mlock:
      // TODO
    case SYS_munlock:
      // TODO
    case SYS_mlockall:
      // TODO
    case SYS_munlockall:
      // TODO
    case SYS_vhangup:
      // TODO
    case SYS_modify_ldt:
      // TODO
    case SYS_pivot_root:
      // TODO
    case SYS_sysctl: // TODO fix
      // TODO
    case SYS_prctl:
      // TODO
    case SYS_arch_prctl:
      // TODO
    case SYS_adjtimex:
      // TODO
    case SYS_setrlimit:
      // TODO
    case SYS_chroot:
      // TODO
    case SYS_sync:
      // TODO
    case SYS_acct:
      // TODO
    case SYS_settimeofday:
      // TODO
    case SYS_mount:
      // TODO
    case SYS_umount2:
      // TODO
    case SYS_swapon:
      DENIED
    case SYS_swapoff:
      DENIED
    case SYS_reboot:
      DENIED
    case SYS_sethostname:
      // TODO
    case SYS_setdomainname:
      // TODO
    case SYS_iopl:
      // TODO
    case SYS_ioperm:
      // TODO
    case SYS_create_module:
      DENIED
    case SYS_init_module:
      DENIED
    case SYS_delete_module:
      DENIED
    case SYS_quotactl:
      // TODO
    case SYS_gettid:
      // TODO
    case SYS_readahead:
      // TODO
    case SYS_setxattr:
      // TODO
    case SYS_lsetxattr:
      // TODO
    case SYS_fsetxattr:
      // TODO
    case SYS_getxattr:
      // TODO
    case SYS_lgetxattr:
      // TODO
    case SYS_fgetxattr:
      // TODO
    case SYS_listxattr:
      // TODO
    case SYS_flistxattr:
      // TODO
    case SYS_removexattr:
      // TODO
    case SYS_fremovexattr:
      // TODO
    case SYS_tkill:
      // TODO
    case SYS_time:
      // TODO
    case SYS_futex:
      // TODO
    case SYS_sched_setaffinity:
      // TODO
    case SYS_sched_getaffinity:
      // TODO
    case SYS_set_thread_area:
      // TODO
    case SYS_io_setup:
      // TODO
    case SYS_io_destroy:
      // TODO
    case SYS_io_getevents:
      // TODO
    case SYS_io_submit:
      // TODO
    case SYS_io_cancel:
      // TODO
    case SYS_get_thread_area:
      // TODO
    case SYS_lookup_dcookie:
      // TODO
    case SYS_epoll_create:
      // TODO
    case SYS_epoll_ctl_old:
      // TODO
    case SYS_epoll_wait_old:
      // TODO
    case SYS_remap_file_pages:
      // TODO
    case SYS_getdents64:
      // TODO
    case SYS_set_tid_address:
      // TODO
    case SYS_restart_syscall:
      // TODO
    case SYS_semtimedup: // TODO fix
      // TODO
    case SYS_fadvise64:
      // TODO
    case SYS_timer_create:
      // TODO
    case SYS_timer_settime:
      // TODO
    case SYS_timer_gettime:
      // TODO
    case SYS_timer_getoverrun:
      // TODO
    case SYS_timer_delete:
      // TODO
    case SYS_clock_settime:
      DENIED
    case SYS_clock_gettime:
      DENIED
    case SYS_getres: // TODO fix
      // TODO
    case SYS_clock_nanosleep:
      // TODO
    case SYS_exit_group:
      // TODO
    case SYS_epoll_wait:
      // TODO
    case SYS_epoll_ctl:
      // TODO
    case SYS_tgkill:
      // TODO
    case SYS_utimes:
      // TODO
    case SYS_mbind:
      // TODO
    case SYS_set_mempolicy:
      // TODO
    case SYS_get_mempolicy:
      // TODO
    case SYS_mq_open:
      // TODO
    case SYS_mq_unlink:
      // TODO
    case SYS_mq_timedsend:
      // TODO
    case SYS_mq_timedreceive:
      // TODO
    case SYS_mq_notify:
      // TODO
    case SYS_getsetattr:
      // TODO
    case SYS_kexec_load:
      // TODO
    case SYS_waitid:
      // TODO
    case SYS_add_key:
      // TODO
    case SYS_request_key:
      // TODO
    case SYS_keyctl:
      // TODO
    case SYS_ioprio_set:
      // TODO
    case SYS_ioprio_get:
      // TODO
    case SYS_inotify_init:
      // TODO
    case SYS_inotify_add_watch:
      // TODO
    case SYS_inotify_rm_watch:
      // TODO
    case SYS_migrate_pages:
      // TODO
    case SYS_openat:
      // TODO
    case SYS_mkdirat:
      // TODO
    case SYS_mknodat:
      // TODO
    case SYS_fchwonat:
      // TODO
    case SYS_futimesat:
      // TODO
    case SYS_newfstatat:
      // TODO
    case SYS_unlinkat:
      // TODO
    case SYS_renameat:
      // TODO
    case SYS_linkat:
      // TODO
    case SYS_symlinkat:
      // TODO
    case SYS_readlinkat:
      // TODO
    case SYS_fchmodat:
      // TODO
    case SYS_faccessat:
      // TODO
    case SYS_pselect6:
      // TODO
    case SYS_ppoll:
      // TODO
    case SYS_unshare:
      // TODO
    case SYS_set_robust_list:
      // TODO
    case SYS_get_robust_list:
      // TODO
    case SYS_splice:
      // TODO
    case SYS_tee:
      // TODO
    case SYS_sync_file_range:
      // TODO
    case SYS_vmsplice:
      // TODO
    case SYS_move_pages:
      // TODO
    case SYS_utimensat:
      // TODO
    case SYS_epoll_pwait:
      // TODO
    case SYS_signalfd:
      // TODO
    case SYS_timerfd_create:
      // TODO
    case SYS_eventfd:
      // TODO
    case SYS_fallocate:
      // TODO
    case SYS_timerfd_settime:
      // TODO
    case SYS_timerfd_gettime:
      // TODO
    case SYS_accept4:
      // TODO
    case SYS_signalfd4:
      // TODO
    case SYS_eventfd2:
      // TODO
    case SYS_epoll_create1:
      // TODO
    case SYS_dup3:
      // TODO
    case SYS_pipe2:
      // TODO
    case SYS_inotify_init1:
      // TODO
    case SYS_preadv:
      // TODO
    case SYS_pwritev:
      // TODO
    case SYS_rt_tgsigqueueinfo:
      // TODO
    case SYS_perf_event_open:
      // TODO
    case SYS_recvmsg:
      // TODO
    case SYS_fanotify_init:
      // TODO
    case SYS_fanotify_mark:
      // TODO
    case SYS_prlimit64:
      // TODO
    case SYS_name_to_handle_at:
      // TODO
    case SYS_open_by_handle_at:
      // TODO
    case SYS_clock_adjtime:
      // TODO
    case SYS_syncfs:
      // TODO
    case SYS_sendmsg:
      DENIED
    case SYS_setns:
      // TODO
    case SYS_getcpu:
      // TODO
    case SYS_process_vm_readv:
      DENIED
    case SYS_process_vm_writev:
      DENIED
    case SYS_kcmp:
      // TODO
    case SYS_finit_module:
      DENIED
    default:
      // TODO
    }
  skip:
    ptrace(PTRACE_SETREGS, pid, 0, &regs);
  }
  return 0;
}
