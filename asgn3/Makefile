CC=clang
CFLAGS=-Wall -Wextra -Werror -Wpedantic

all: quicksort

quicksort: quick.o stack.o queue.o
	$(CC) -o quicksort quick.o stack.o queue.o

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c
clean:
	rm -f quicksort quick.o stack.o queue.o
format:
	clang-format -i -style=file *.[ch]
scan-build: clean
	scan-build make
