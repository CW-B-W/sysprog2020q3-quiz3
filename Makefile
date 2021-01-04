All: test1 test2 test4

test1: ./test1/test1

./test1/test1: ./test1/test1.cpp
	clang-format -i -style=file $^
	g++ -fsanitize=undefined -Wall $^ -o $@

test2: ./test2/test2

test2-plot: ./test2/test2
	cd test2 && gnuplot test2-plot.gp

./test2/test2: ./test2/test2.cpp
	clang-format -i -style=file $^
	g++ -Wall $^ -o $@

test4: ./test4/test4

./test4/test4: ./test4/test4.cpp
	clang-format -i -style=file $^
	g++ -Wall $^ -o $@

clean:
	rm ./test1/test1 ./test2/test2 ./test4/test4
