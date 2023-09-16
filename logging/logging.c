// logging.c

#include<stdio.h>
#include<time.h>

#include "logging.h"


void debug(char *msg)
{
  printf(DEBUG, time(NULL), msg);
}

void info(char *msg)
{
  printf(INFO, time(NULL), msg);
}

void warning(char *msg)
{
  printf(WARNING, time(NULL), msg);
}

void critical(char *msg)
{
  printf(CRITICAL, time(NULL), msg);
}

void error(char *msg)
{
  printf(ERROR, time(NULL), msg);
}

void debugf(char *msg, FILE *stream)
{
  fprintf(stream, DEBUG, time(NULL), msg);
}

void infof(char *msg, FILE *stream)
{
  fprintf(stream, INFO, time(NULL), msg);
}

void warningf(char *msg, FILE *stream)
{
  fprintf(stream, WARNING, time(NULL), msg);
}

void criticalf(char *msg, FILE *stream)
{
  fprintf(stream, CRITICAL, time(NULL), msg);
}

void errorf(char *msg, FILE *stream)
{
  fprintf(stream, ERROR, time(NULL), msg);
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
