CC=clang
CFLAGS=-Wall -Wextra -Werror -Wpedantic

all: all

all: $(OBJS)
	clang -o $@ $^

encode: hamming.o bv.o bm.o encode.o
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
	rm -f *.o encode
format:
	clang-format -i -style=file *.[ch]
scan-build: clean
	scan-build make
