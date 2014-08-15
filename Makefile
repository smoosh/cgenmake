CC = gcc
CFLAGS = -g -o

cgenmake: cgenmake.c errchk.h
	$(CC) $(CFLAGS) cgenmake cgenmake.c
	@echo 'Done.'

clean:
	rm -rf *.o cgenmake
