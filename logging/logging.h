// logging.h

#ifndef LOGGING_H_
#define LOGGING_H_

#define ANSI_BLUE "\033[34m"
#define ANSI_CYAN "\033[36m"
#define ANSI_GREEN "\033[32m"
#define ANSI_RED "\033[31m"
#define ANSI_YELLOW "\033[33m"

#define ANSI_RESET "\033[39m"

#define MESSAGE_BASE "[" ANSI_BLUE "%i" ANSI_RESET "]["

#define DEBUG MESSAGE_BASE ANSI_CYAN "DEBUG" ANSI_RESET "]: %s\n"
#define INFO MESSAGE_BASE ANSI_GREEN "INFO" ANSI_RESET "]: %s\n"
#define WARNING MESSAGE_BASE ANSI_YELLOW "WARNING" ANSI_RESET "]: %s\n"
#define CRITICAL MESSAGE_BASE ANSI_RED "CRITICAL" ANSI_RESET "]: %s\n"
#define ERROR MESSAGE_BASE ANSI_RED "ERROR" ANSI_RESET "]: %s\n"


char *get_formatted_time(void);

void debug(char *msg);
void info(char *msg);
void warning(char *msg);
void critical(char *msg);
void error(char *msg);

void debugf(char *msg, FILE *stream);
void infof(char *msg, FILE *stream);
void warningf(char *msg, FILE *stream);
void criticalf(char *msg, FILE *stream);
void errorf(char *msg, FILE *stream);

#endif /* LOGGING_H_ */
