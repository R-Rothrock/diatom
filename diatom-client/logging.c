// logging.c
// https://github.com/R-Rothrock/diatom
// logging system

// A primer on how this logging system ought to operate.
// Logs will be loaded into a heap buffer to speed. A separate thread
// (we will call it the logging thread) will work to move these logs
// from memory to the hard disk. Additional to this, we will have yet
// another thread (we will call it the monitoring thread) that will be
// tasked with making sure we always have an idea of how much space is
// used/free within the logging buffer, in the event this data is ever
// wanted.
// When the buffer gets near overflowing, the index pointer will be
// moved back to the beginning. By keeping track of where the log
// index pointer is in contrast to where the logging thread's index
// pointer, (not to be confused) we will always know what meeds to be
// written to disk by the logging thread. Additionally, we can keep
// track of the usage of the logging buffer as so:
// 
// part = abs(logging_index - logging_thread_index)
// whole = log_buffer_size
// percentage = (part / whole) * 100
//
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
#define LOG_BUFFER_SIZE 1024 * 1024 * 2 // 2MB
// the location of the log buffer and the location of where we are in
// the log buffer
static void* LOG_BUFFER;
static void* LOG_BUFFER_INDEX;

// these variables are used only by the logging thread

// firstly, the logging thread needs to always know where it is in the
// logging buffer
static int LOGGING_THREAD_INDEX;

// since the logging thread doesn't need to be working continuously,
// I'll make it pause just a bit after each iteration of its loop
#define LOGGING_THREAD_PAUSE_SEC 1 // in seconds

// TODO more variables?
void logging_thread(void)
{
	/* Everything the logging thread does is here */

	for(;;)
	{
		// TODO
		sleep(LOGGING_THREAD_PAUSE_SEC);
	}
}

void monitoring_thread(void)
{
	/* Everything the logging threasd does is here */
	// TODO
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

