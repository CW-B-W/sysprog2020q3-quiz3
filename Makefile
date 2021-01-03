test1: test1.cpp
	g++ -fsanitize=undefined -Wall test1.cpp -o test1

clean:
	rm test1
