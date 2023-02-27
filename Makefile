CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
SRC = 1726.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f main $(OBJ)

test: main
	./test.sh