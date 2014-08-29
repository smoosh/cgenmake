This program was intended as a simple way to generate a basic makefile template. In the future I will make it more useful for more complex makefiles. However, for now its only purpose is served as a starting template that the user can obviously edit to his or her own needs. You can modify and redistribute this source in any way you see fit. If you need to contact me for more information or would wish to submit your additions send them to pnl.ognc@gmail.com

This program is used to generate a simple makefile template.
Usage: cgenmake [-f?] [-c example.c] [-h example.h] [--cfile=example.c]
            [--force] [--hfile=example.h] [--help] [--usage]
            makefile || Makefile

Example:
$ cgenmake -c source.c -h header.h Makefile
