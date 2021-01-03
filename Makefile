All: test1 test2

test1: test1.cpp
	clang-format -i -style=file $^
	g++ -fsanitize=undefined -Wall $^ -o $@

test2: test2.cpp
	clang-format -i -style=file $^
	g++ -fsanitize=undefined -Wall $^ -o $@
	gnuplot test2-plot.gp

clean:
	rm test1 test2
