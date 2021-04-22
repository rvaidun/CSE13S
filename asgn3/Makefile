CC=clang
CFLAGS=-Wall -Wextra -Werror -Wpedantic
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

all: sorting

sorting: $(OBJS)
	clang -o $@ $^

%.o: %.c
	clang $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) sorting
format:
	clang-format -i -style=file *.[ch]
scan-build: clean
	scan-build make
