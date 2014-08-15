This program was intended as a simple way to generate a basic makefile template. In the future I will make it more useful for more complex makefiles. However, for now its only purpose is served as a starting template that the user can obviously edit to his or her own needs. You can modify and redistribute this source in any way you see fit. If you need to contact me for more information or would wish to submit your additions send them to pnl.ognc@gmail.com

This program is used to generate a simple makefile template.
Usage: -[n:w:h]
	-n [filename] [source file(s)]: Create new makefile.
	-w [filename] [source file(s)]: Overwrite existing makefile.
	-h: Display help.

Example:
	./genmake -n makefile sourcefile
