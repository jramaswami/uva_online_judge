CC = g++-5
CFLAGS = -std=c++11 -lm -O2 -Wall


all: clean build test

build:
	$(CC) $(CFLAGS) src/uva573.cc -o uva573

test: build
	@echo
	@echo "Running tests ..."
	bats test/test.bats

clean:
	-rm a.out
	-rm uva573
	-rm test/output*.txt
