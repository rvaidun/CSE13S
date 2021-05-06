CC=clang
CFLAGS=-Wall -Wextra -Werror -Wpedantic
SRCS=bm.c bv.c
OBJS=$(SRCS:.c=.o)

all: bm

bm: $(OBJS)
	clang -o $@ $^

%.o: %.c
	clang $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) tsp
format:
	clang-format -i -style=file *.[ch]
scan-build: clean
	scan-build make
