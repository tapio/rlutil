CFLAGS=-g -O2 -Wall -Wextra

all: test example-c

test: rlutil.h test.cpp
	$(CXX) $(CFLAGS) -o test test.cpp

example-c: rlutil.h example.c
	$(CC) $(CFLAGS) -o example-c example.c

.PHONY: clean

clean:
	rm -f test example-c
	rm -rf *.dSYM
