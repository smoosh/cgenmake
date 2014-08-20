 /* * * * * * * * * * * * * * * * * * * * * * * *
  *
  * For a little bit of convenience I've decided 
	* to make a very simplistic form of a makefile 
	* generator. This will become more complex in 
	* future iterations.
  * 
  * - cemetery
  *
  * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>
#include <unistd.h> /* for getopt */
#include <getopt.h> /* for getopt_long */
#include <sys/stat.h> /* for stat */
#include <errno.h> /* for errno */

#include "errchk.h"
#include "config.h"

/* prototypes */
char *usage();
char *gen_make(char *,FILE *);

int main(int argc, char *argv[])
{
  int c, i;
	
	/* option flags */
	int nflag, wflag, hflag;
	nflag = wflag = hflag = 0;

  char *cc = "CC";
  char *cflags = "CFLAGS";
  FILE *fp;

  struct stat sts;

  while ((c = getopt(argc, argv, "f:s:n:w:h")) != -1)
    switch (c) {
    case 'n':
			nflag = 1;
      break;
    case 'w':
			wflag = 1;
      break;
    case 'h':
			hflag = 1;
      break;
    case '?':
			if (optopt == 'n' || optopt == 'w')
				fprintf(stderr, "Option -%c requires and argument.\n",
            optopt);
      else if (isprint(optopt))
				fprintf(stderr, "Unknown option `-%c'.\n", optopt);
      else
				fprintf(stderr, "Unknown option char `\\x%x'.\n",
            optopt);
      return 1;
    default:
      abort();
      break;
    }

  /* create a new makefile if !exists */
	if (nflag) {
    //if ((stat(argv[2], &sts)) == -1 || errno == ENONET) {
    if (!fexists(argv[2])) {
				/* error handling */
				if (argc > 4)
					fprintf(stderr, "Too many arguments.\n");
				else if (chk_make(argv[2])) {
          fp = fopen(argv[2], "w");
				  gen_make(argv[3], fp);
          fclose(fp);
        } else
          die("This is not a valid makefile: "
            "[Makefile || makefile]\n");
      } else {
					fprintf(stderr, "%s already exists.\n", argv[2]);
					return 1;
      }
  /* overwrite existing makefiles */
	} else if (wflag) {
      if (chk_make(argv[2])) {
        fp = fopen(argv[2], "w");
      	gen_make(argv[3], fp);
        fclose(fp);
      } else
        die("This is not a valid makefile: "
            "[Makefile || makefile]\n");

  /* TODO: insert a header */
	} else if (hflag)
		printf("%s", usage());

  return 0;
}

char *usage(void)
{
  static char *msg =
    {
      "Usage: -[n:w:h]\n"
      "\t-n [filename] [source file(s)]: Create new makefile.\n"
      "\t-w [filename] [source file(s)]: Overwrite existing makefile.\n"
      "\t-h: Display help.\n"
    };

  return msg;
}

/* print basic template to makefile */
char *gen_make(char *src, FILE *fp)
{
  /* these variables do nothing yet */
	int c, hflag, nflag;

  /* 
   * char *cc = "CC";
     char *cflags = "CFLAGS";
	   char *flags = "-g -o"; change your flags here
  */

  fprintf(fp, "%s = gcc\n", compilers);
 	fprintf(fp, "%s = %s\n\n", flags, args);
  fprintf(fp, "%s: %s.c\n", src, src);
  fprintf(fp, "\t$(%s) $(%s) %s %s.c\n", compilers, flags, src, src);
	fprintf(fp, "\t@echo \'Done.\'\n\n");
 	fprintf(fp, "clean:\n\trm -rf *.o %s\n", src);

  return src;
}
