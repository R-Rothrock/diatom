// logging.c

#include<stdio.h>
#include<time.h>

#include "logging.h"

char *get_formatted_time(void)
{
  // TODO
}

void debug(char *msg)
{
  printf(DEBUG, get_formatted_time(), msg);
}

void info(char *msg)
{
  printf(INFO, get_formatted_time(), msg);
}

void warning(char *msg)
{
  printf(WARNING, get_formatted_time(), msg);
}

void critical(char *msg)
{
  printf(CRITICAL, get_formatted_time(), msg);
}

void error(char *msg)
{
  printf(ERROR, get_formatted_time(), msg);
}

void debugf(char *msg, FILE *stream)
{
  fprintf(stream, DEBUG, get_formatted_time(), msg);
}

void infof(char *msg, FILE *stream)
{
  fprintf(stream, INFO, get_formatted_time(), msg);
}

void warningf(char *msg, FILE *stream)
{
  fprintf(stream, WARNING, get_formatted_time(), msg);
}

void criticalf(char *msg, FILE *stream)
{
  fprintf(stream, CRITICAL, get_formatted_time(), msg);
}

void errorf(char *msg, FILE *stream)
{
  fprintf(stream, ERROR, get_formatted_time(), msg);
}

/*
int main()
{
  debug("This is a debug message.");
  info("This is an info message.");
  warning("This is a warning message.");
  critical("This is a critical message.");
  error("Whatever happened, we're blaming it on you.");
  return 0;
}
*/
