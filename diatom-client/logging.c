// logging.c
// https://github.com/R-Rothrock/diatom
// logging system

// A primer on how this logging system ought to operate.
// Logs will be loaded into a heap buffer to speed. A separate thread
// will work to move these logs from RAM to an actual file. I'm
// deciding to do it this way so that, for example, I don't have to
// endure another syscall every time the tracee has another syscall
// to be emulated. And so, I'm making it so that the main thread
// doesn't actually have a mode switch. Perhaps there are
// different/better ways to do this, but this makes the most sense
// thus far.

// These logs are designed to be very in-depth. Very little will be
// omitted. Something like that output of `journalctl` is what I'm
// going for.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

// the file descriptor for the logging
static FILE *fd;

// these variables are to be shared between threads

// This one's prone to change. I don't yet know how to analyze the
// cost and benefit of using all that memory.
static int LOG_BUFFER_SIZE 1024 * 1024 * 2 // 2MB
// the location of the log buffer and the location of where we are in
// the log buffer
static void* LOG_BUFFER;
static void* LOG_BUFFER_INDEX;

// these variables are used only by the logging thread

// the percentage of usage of the log buffer that is finally deemed
// unacceptible by the logging thread
static int ACCEPTIBLE_LOG_BUFFER_USAGE_PER = 95;

// where the log thread is in the log buffer when reading through it
static void* LOG_THREAD_LOG_BUFFER_INDEX;

// how frequently the logging thread checks the usage of the buffer
// (measured in seconds)
static int LOG_THREAD_USAGE_CHECK_FREQ = 2;

float get_log_buffer_usage()
{
	/* calculates the percentage usage of the log buffer */
	float ret;
	int part = LOG_BUFFER_INDEX - LOG_BUFFER;
	int whole = LOG_BUFFER_SIZE;

	ret = (part / whole) * 100;
	return ret;
}

void logging_thread()
{
	/* Everything the logging thread does is here */

	// First things first, we need to (almost) always know how much
	// space we have in the logging buffer
}

int log_init(const char* pathname)
{
	/* Allocates space in RAM for logs and starts the logging thread */
	// TODO
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
	 * ral machine DICP_REQUEST_INFO '/usr/bin/bash'
	 * etc.
	 *
	 * `origin` is the `handle_process_syscalls` part (the function/part
	 * of the program logging.) Ought to help with debugging.
	 */

	// TODO

}


