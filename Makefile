All: test1 test2

test1: test1.cpp
	g++ -fsanitize=undefined -Wall test1.cpp -o test1

test2: test2.cpp
	g++ -fsanitize=undefined -Wall test2.cpp -o test2

clean:
	rm test1 test2
