CC = g++-5
CFLAGS = -std=c++11 -lm -O2 -Wall


all: clean build test

build:
	$(CC) $(CFLAGS) src/uva10114.cc -o uva10114

test: build
	@echo
	@echo "Running tests ..."
	bats test/test.bats

clean:
	-rm a.out
	-rm uva10114
	-rm test/output*.txt
