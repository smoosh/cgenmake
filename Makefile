CC = gcc
CFLAGS = -g -o

test.c: test.c
	$(CC) $(CFLAGS) test test.c
	@echo 'Done.'

clean:
	rm -rf *.o test.c
