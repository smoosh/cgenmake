/* * * * * * *
 * Use this as a template 
 * - cemetery
 * * * */

#include <stdio.h>
#include <argp.h>

#include "config.h" /* parse real config file in future */
#include "err.h"

#define BUFSIZE 80

/* structure which holds arguments variables and makefile data */
struct arguments {
  char *args[1];
  int force;
  char *cfile; /* source file var */
  char *hfile; /* header file var */
  char *mfile; /* makefile var */
  char binfile[BUFSIZE];
};

static struct argp_option options[] =
{
  { "cfile", 'c', "example.c", 0,
    "Insert a source file into the makefile" },
  { "hfile", 'h', "example.h", 0,
    "Insert a header file into the makefile" },
  { "force", 'f', 0, 0,
    "Overwrite an existing makefile"},
 {0}
};

static error_t parse_opt(int key, char *arg,
                         struct argp_state *state)
{
  struct arguments *arguments = state->input;

  switch (key) {
    case 'c':
      arguments->cfile = arg;
      break;
    case 'h':
      arguments->hfile = arg;
      break;
    case 'f':
      arguments->force = 1;
      break;
    case ARGP_KEY_ARG:
      if (state->arg_num >= 1)
        argp_usage(state);
      arguments->args[state->arg_num] = arg;
      break;
    case ARGP_KEY_END:
      if (state->arg_num < 1)
        argp_usage(state);
      break;
    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static char args_doc[] = "makefile || Makefile";

/* declare argp struct */
static struct argp argp = {options, parse_opt, args_doc};

/* generate the makefile */
void genmake(int argc, char **argv)
{
  struct arguments a/*rguments*/;
  FILE *outstream;
  char binfile[BUFSIZE];

  a.force = 0;
  a.cfile = "";
  a.hfile = NULL;

  argp_parse(&argp, argc, argv, 0, 0, &a);

  outstream = fopen(a.args[0], "w");

  /* cut off the last two chars in cfile and copy to binfile array */
  strncpy(binfile, a.cfile, strlen(a.cfile)-2);
  
  if (a.hfile == NULL) {
    fprintf(outstream, "%s = gcc\n", compiler);
    fprintf(outstream, "%s = %s\n\n", flags, gcc_args);
    fprintf(outstream, "%s: %s\n", binfile, a.cfile);
    fprintf(outstream, "\t$(%s) $(%s) %s %s\n", 
        compiler, flags, binfile, a.cfile);
    fprintf(outstream, "\t@echo \'Done.\'\n\n");
    fprintf(outstream, "clean:\n\trm -rf *.o %s\n", a.cfile);
  }
  else {
    fprintf(outstream, "%s = gcc\n", compiler);
    fprintf(outstream, "%s = %s\n\n", flags, gcc_args);
    fprintf(outstream, "%s: %s %s\n", binfile, a.cfile,
        a.hfile); /* header file is added here */
    fprintf(outstream, "\t$(%s) $(%s) %s %s\n", 
        compiler, flags, binfile, a.cfile);
    fprintf(outstream, "\t@echo \'Done.\'\n\n");
    fprintf(outstream, "clean:\n\trm -rf *.o %s\n", binfile);
  }
  fclose(outstream);
}

/* main */
int main(int argc, char **argv)
{
  struct arguments a;
  argp_parse(&argp, argc, argv, 0, 0, &a);

  if (!fexists(a.args[0]) || a.force == 1)
    genmake(argc, argv);
  else
    fprintf(stderr, "%s already exists. "
                    "Use -f to overwrite.\n", a.args[0]);
  return 0;
}
