CC = gcc
CFLAGS = -g -o

cgenmake: cgenmake.c
	$(CC) $(CFLAGS) cgenmake cgenmake.c
	@echo 'Done.'

clean:
	rm -rf *.o cgenmake.c
