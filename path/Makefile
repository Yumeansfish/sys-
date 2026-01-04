CC = gcc
CFLAGS = -Wall -g

all: test_path

test_path: test_path.c path.c path.h
	$(CC) $(CFLAGS) -o test_path test_path.c path.c

test: test_path
	./test_path

clean:
	rm -f test_path

.PHONY: all test clean
