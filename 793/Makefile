problem = network

all: clean $(problem) test

$(problem): $(problem).cc
	g++ -pedantic -std=c++11 -Wall -O2 -Wextra -Wfloat-equal -Wconversion -fsanitize=address $(problem).cc -o $(problem)

test: $(problem)
	bash test.sh

clean:
	-rm $(problem)
	-rm output*.txt
	# -rm test_random*.txt
	# -rm expected_random*.txt
