CC=clang
CFLAGS=-Wall -Wextra -Werror -Wpedantic

all: pq

pq: node.o pq.o
	$(CC) -o $@ $^

%.o: %.c
	clang $(CFLAGS) -c $<

clean:
	rm -f *.o pq
format:
	clang-format -i -style=file *.[ch]
scan-build: clean
	scan-build make
