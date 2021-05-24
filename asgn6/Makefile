CC=clang
CFLAGS=-Wall -Wextra -Werror -Wpedantic

all: encode decode entropy

encode: encode.o io.o code.o huffman.o pq.o node.o stack.o bitlib.o
	$(CC) -o $@ $^

decode: decode.o io.o code.o huffman.o pq.o stack.o node.o bitlib.o
	$(CC) -o $@ $^

entropy: entropy.o
	$(CC) -o $@ $^ -lm

%.o: %.c
	clang $(CFLAGS) -c $<

clean:
	rm -f *.o encode decode entropy
format:
	clang-format -i -style=file *.[ch]
scan-build: clean
	scan-build make
