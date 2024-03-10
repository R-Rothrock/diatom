// logging.h

#ifndef LOGGING_H_
#define LOGGING_H_

#define ANSI_BLUE "\033[34m"
#define ANSI_CYAN "\033[36m"
#define ANSI_GREEN "\033[32m"
#define ANSI_RED "\033[31m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_RESET "\033[39m"

#define MESSAGE_PRE "[" ANSI_BLUE "%s" ANSI_RESET "]["
#define MESSAGE_SUF ANSI_RESET "]: %s\n"

#define DEBUG MESSAGE_PRE ANSI_CYAN "DEBUG" MESSAGE_SUF
#define INFO MESSAGE_PRE ANSI_GREEN "INFO" MESSAGE_SUF
#define WARNING MESSAGE_PRE ANSI_YELLOW "WARNING" MESSAGE_SUF
#define CRITICAL MESSAGE_PRE ANSI_RED "CRITICAL" MESSAGE_SUF
#define ERROR MESSAGE_PRE ANSI_RED "ERROR" MESSAGE_SUF

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
