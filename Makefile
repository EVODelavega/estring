CFLAGS=-Wall -g -std=c99 -pedantic
CC=gcc

all: clean example

example: estring.c estring.h example.c

clean:
	@rm -f example
	@echo "Clean OK"
