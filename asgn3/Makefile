CC=clang
CFLAGS=-Wall -Wextra -Werror -Wpedantic

all: quicksort

quicksort: quick.o stack.o
	$(CC) -o quicksort quick.o stack.o
quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c
clean:
	rm -f quicksort quick.o stack.o
format:
	clang-format -i -style=file *.[ch]
scan-build: clean
	scan-build make
