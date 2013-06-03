CC=gcc
CXX=g++
CFLAGS=-I. -Wall -Wextra

all: test example-c

test:
	$(CXX) $(CFLAGS) -o test test.cpp

example-c:
	$(CC) $(CFLAGS) -o example-c example.c
	
.PHONY: clean

clean:
	rm test example-c
