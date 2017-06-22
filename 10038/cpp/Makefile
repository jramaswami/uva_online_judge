CC = g++-5
CFLAGS = -std=c++11 -lm -O2 -Wall


all: clean build test

build:
	$(CC) $(CFLAGS) src/uva10038.cc -o uva10038

test: build
	@echo
	@echo "Running tests ..."
	bats test/test.bats

clean:
	-rm a.out
	-rm uva10038
	-rm test/output*.txt
