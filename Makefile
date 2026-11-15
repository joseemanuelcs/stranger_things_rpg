CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -Iinclude
SRC = $(wildcard src/*.c)

all: jogo_mac

jogo_mac: $(SRC) $(wildcard include/*.h)
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	rm -f jogo_mac

.PHONY: all clean
