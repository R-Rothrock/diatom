// logging.c
// https://github.com/R-Rothrock/diatom
// logging system

// A primer on how this logging system ought to operate.
// Logs will be loaded into a heap buffer for speed. A separate thread
// (we will call it the logging thread) will work to move these logs
// from memory to the hard disk, along with overwriting the space with
// null bytes. Additional to this, we will have yet another thread (we
// will call it the monitoring thread) that will be tasked with making
// sure we always have an idea of how much space is used/free within
// the logging buffer, in the event this data is ever wanted. When the
// buffer gets near overflowing, the index pointer will be
// moved back to the beginning.
//
// To calculate the logging buffer usage in bytes, we can do this:
//
// if logging_index > logging_thread_index:
//   logging_index - logging_thread_index
//
// if logging_index < logging_thread_index:
//   null_start - logging_thread_index + logging_index - buffer_start
//
// where:
// `null_start` is where the logging_thread stopped and went back to
// the beginning of the buffer (where the null bytes at the end start)
//
// These logs are designed to be very in-depth. Very little will be
// omitted. Something like the output of `journalctl` is what I'm
// going for.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

/******************
 * Variables
 * (lots of them)
 ******************/

// the size of the log buffer. One day this'll be in a config file.
static unsigned int LOG_BUFFER_SIZE = 1024 * 1024 * 2;

static void *LOG_BUFFER;       // the actual buffer
static void *LOG_INDEX;        // where the logging happens
static void *NULL_START;       // where the null bytes start at the
															 // end of the buffer
static void *LOG_THREAD_INDEX; // where the logging thread is in the
															 // buffer
static int TOTAL_USAGE_BYTES;  // the number of bytes used in the
															 // buffer. Managed by the monitoring
															 // thread
// any other variables go here

/******************
 * Macro Variables
 * (not too many)
 ******************/

// since the logging thread doesn't need to be working continuously,
// I'll give it a small pause
#define LOG_THREAD_REFRESH_RATE 1 // in seconds

// same goes to the monitoring thread
#define MONITOR_THREAD_REFRESH_RATE 1 // in seconds

float calc_total_usage_percent(void)
{
	// TODO
}

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
	/* Everything the monitoring thread does is here */
	for(;;)
	{
		// TODO implement kill switch

		if(LOG_INDEX > LOG_THREAD_INDEX)
		{
			 TOTAL_USAGE_BYTES = LOG_INDEX - LOG_THREAD_INDEX;
		} else
		if(LOG_INDX < LOG_THREAD_INDEX)
		{
			TOTAL_USAGE_BYTES
			= NULL_START
			- LOG_THREAD_INDEX
			+ LOG_INDEX
			- LOG_BUFFER;
		} else
		{
			// LOG_INDEX == LOG_THREAD_INDEX
			TOTAL_USAGE_BYTES = 0;
		}
		sleep(MONITOR_THREAD_REFRESH_RATE);
	}
}

int log_init(const char* pathname)
{
	/* Allocates space in RAM for logs and starts the logging thread and
	 * the monitoring thread */
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

