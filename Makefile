CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -Iinclude
SRC = $(wildcard src/*.c)

all: jogo_mac

jogo_mac: $(SRC) $(wildcard include/*.h)
	$(CC) $(CFLAGS) $(SRC) -o $@

run: jogo_mac
	./jogo_mac

clean:
	rm -f jogo_mac

.PHONY: all run clean
