CFLAGS=-Wall -g -std=c99 -pedantic
CC=gcc

all: example clean

example: estring.o example.c

estring.o: estring.c estring.h

clean:
	@rm -f estring.o
	@echo "Clean OK"
