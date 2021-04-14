CC=clang
CFLAGS=-Wall -Wextra -Werror -Wpedantic

all: mathlib-test

mathlib-test: mathlib-test.o
	$(CC) -o mathlib-test mathlib-test.o
mathlib-test.o: mathlib-test.c
	$(CC) $(CFLAGS) -c mathlib-test.c
clean:
	rm -f mathlib-test mathlib-test.o
format:
  clang-format -i -style=file *.[ch]
scan-build: clean
	scan-build make
