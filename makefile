CC = gcc
CFLAGS = -g -o

test: test.c
	$(CC) $(CFLAGS) test test.c
	@echo 'Done.'

clean:
	rm -rf *.o test
