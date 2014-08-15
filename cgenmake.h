#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define BUFSIZE 80

/* print basic template to makefile */
char *gen_make(char *src, FILE *fp)
{
	int c, hflag, nflag;

  char *cc = "CC";
  char *cflags = "CFLAGS";
	char *flags = "-g -o"; /* change your flags here */

  fprintf(fp, "%s = gcc\n", cc);
 	fprintf(fp, "%s = %s\n\n", cflags, flags);
  fprintf(fp, "%s: %s.c\n", src, src);
  fprintf(fp, "\t$(%s) $(%s) %s %s.c\n", cc, cflags, src, src);
	fprintf(fp, "\t@echo \'Done.\'\n\n");
 	fprintf(fp, "clean:\n\trm -rf *.o %s\n", src);

  return src;
}

/* check if makefile's name is valid */
/* potential exploit if bufsize > 80, might cause overflow */
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

/* die, error handling */
void die(const char *errstr, ...)
{
  va_list ap;

  va_start(ap, errstr);
  vfprintf(stderr, errstr, ap);
  va_end(ap);
  exit(EXIT_FAILURE);
}
