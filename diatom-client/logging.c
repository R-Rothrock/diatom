// logging.c
// https://github.com/R-Rothrock/diatom
// logging system

// These logs are designed to be very in-depth. Very little will be
// omitted. Something like that output of `journalctl` is what I'm
// going for.

#include<fcntl.h>

// the file descriptor for the logging
static FILE *fd;

int log_init(const char* pathname)
{
	/* Initializes logging by opening a file descriptor. Needless to
	 * say, run this before anything else here. */
	
	fd = fopen(pathname, "a");
	if(fd <= 0)
		return fd;

	// TODO log that log_init is initing the log
}

// different log levels that can be used
// DEBUG for monotonous, repetative calls (i.e. syscall handling)
// INFO for less common but unimportant things (i.e. communicating
// with the central machine.
// WARNING for simple misuses insued by the user (i.e. bad config)
// CRITICAL for things that are likely not good (i.e. tracee crashes)
// ERROR for things that are internal (i.e. function had the balls to
// return -1)
enum log_levels
{
	DEBUG,
	INFO,
	WARNING,
	CRITICAL,
	ERROR
} __attribute__((packed));

// time information used in logging (all in string form)
struct time_data
{
	char[3] month_abbrev;
	char[2] date_abbrev;
	char[2] hour_abbrev;
	char[2] min_abbrev;
	char[2] sec_abbrev;
	char[2] msec_abbrev;
}

struct time_data get_time_date(void)
{
	// fills in a `struct time_data` with currect data and returns it.
	// TODO
}

int log(enum log_levels level, const char *msg, const char *origin)
{
	/* Examples:
	 *
	 * May 9 00:01:41:25 handle_process_syscalls [DEBUG] tracee SYS_read -> 0
	 * May 9 00:01:41:37 handle_process_syscalls [INFO] contacting cent-
	 * ral machine requesting file `/etc/bash.bashrc`
	 * etc.
	 *
	 * `origin` is the `handle_process_syscalls` part (the function/part
	 * of the program logging.) Ought to help with debugging.
	 */

	// TODO

}


