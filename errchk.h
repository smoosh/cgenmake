#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define BUFSIZE 80

/* check if makefile's name is valid */

int chk_make(char *mkf)
{
	int auth_flag = 0;
	char mk_buf[BUFSIZE];
  strcpy(mk_buf, mkf);

  if (strcmp(mk_buf, "Makefile") == 0)
    auth_flag = 1;
  if (strcmp(mk_buf, "makefile") == 0)
    auth_flag = 1;

  return auth_flag;
}

/* boolean enum for error checking */
typedef enum { true, false } Bool;
struct stat sts;

Bool fexists(char *file)
{
  Bool found = false; /* init found to false */
  if ((stat(file, &sts)) == -1 || errno == ENONET)
    found = true;
  else
    found = false;

  return found;
}

/* error handling */
void die(const char *errstr, ...)
{
  va_list ap;

  va_start(ap, errstr);
  vfprintf(stderr, errstr, ap);
  va_end(ap);
  exit(EXIT_FAILURE);
}
