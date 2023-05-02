CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
SRC = 1450.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.exe *.o *.out

test: main
	./test.sh