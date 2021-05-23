CC=clang
CFLAGS=-Wall -Wextra -Werror -Wpedantic -g

all: encode decode

pq: node.o pq.o
	$(CC) -o $@ $^

io: io.o code.o
	$(CC) -o $@ $^

encode: encode.o io.o code.o huffman.o pq.o node.o stack.o bitlib.o
	$(CC) -o $@ $^

decode: decode.o io.o code.o huffman.o pq.o stack.o node.o bitlib.o
	$(CC) -o $@ $^

%.o: %.c
	clang $(CFLAGS) -c $<

clean:
	rm -f *.o pq io encode decode
format:
	clang-format -i -style=file *.[ch]
scan-build: clean
	scan-build make
