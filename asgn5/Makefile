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
# encode.o: encode.c
# 	$(CC) $(CFLAGS) -c $^

# hamming.o: hamming.c
# 	$(CC) $(CFLAGS) -c $^

# bm.o: bm.c
# 	$(CC) $(CFLAGS) -c $^

# bv.o: bv.c
# 	$(CC) $(CFLAGS) -c $^

%.o: %.c
	clang $(CFLAGS) -c $<

clean:
	rm -f *.o encode decode entropy error
format:
	clang-format -i -style=file *.[ch]
scan-build: clean
	scan-build make
