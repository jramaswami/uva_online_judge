CC = g++-5
CFLAGS = -std=c++11 -lm -O2 -Wall


all: clean build test

build:
	$(CC) $(CFLAGS) src/uva11340.cc -o uva11340

test: build
	@echo
	@echo "Running tests ..."
	bats test/test.bats

clean:
	-rm a.out
	-rm uva11340
	-rm test/output*.txt
