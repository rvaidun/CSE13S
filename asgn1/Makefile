CC=clang
CFLAGS=-Wall -Wextra -Werror -Wpedantic

all: lrc

lrc: lrc.o
	$(CC) -o lrc lrc.o
lrc.o: lrc.c
	$(CC) $(CFLAGS) -c lrc.c
clean:
	rm -f lrc lrc.o
scan-build: clean
	scan-build make
