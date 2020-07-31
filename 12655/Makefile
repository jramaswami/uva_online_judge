problem = trucks

all: clean $(problem) test

$(problem): $(problem).cc
	g++ -pedantic -std=c++11 -Wall -O2 -Wextra -Wfloat-equal -Wconversion -fsanitize=address $(problem).cc -o $(problem)

test: $(problem)
	./$(problem) < test0.txt > output0.txt
	diff expected0.txt output0.txt
	./$(problem) < test1.txt > output1.txt
	diff expected1.txt output1.txt
	./$(problem) < test2.txt > output2.txt
	diff expected2.txt output2.txt
	./$(problem) < test3.txt > output3.txt
	diff expected3.txt output3.txt

clean:
	-rm $(problem)
	-rm output0.txt
	-rm output1.txt
	-rm output2.txt
	-rm output3.txt
