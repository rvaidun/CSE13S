CC=clang
CFLAGS=-Wall -Wextra -Werror -Wpedantic

all: encode decode entropy error

encode: hamming.o bv.o bm.o encode.o
	$(CC) -o $@ $^

decode: hamming.o bv.o bm.o decode.o
	$(CC) -o $@ $^

entropy: entropy.o
	$(CC) -o $@ $^ -lm

error: error.o
	$(CC) -o $@ $^
%.o: %.c
	clang $(CFLAGS) -c $<

clean:
	rm -f *.o encode decode entropy error
format:
	clang-format -i -style=file *.[ch]
scan-build: clean
	scan-build make
