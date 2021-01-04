All: test1 test2 test4

test1: ./test1/test1

test1-test: ./test1/test1
	cd test1 && ./test1

./test1/test1: ./test1/test1.cpp
	clang-format -i -style=file $^
	g++ -fsanitize=undefined -Wall $^ -o $@

test2: ./test2/test2

test2-test: ./test2/test2
	cd test2 && ./test2

test2-plot: $(wildcard ./test2/*.dat)
	cd test2 && gnuplot test2-plot.gp

./test2/test2: ./test2/test2.cpp
	clang-format -i -style=file $^
	g++ -Wall $^ -o $@

test4: ./test4/test4

test4-test: ./test4/test4
	cd test4 && ./test4

test4-plot: $(wildcard ./test4/*.dat)
	cd test4 && gnuplot test4-plot.gp

./test4/test4: ./test4/test4.cpp
	clang-format -i -style=file $^
	g++ -Wall $^ -o $@ -O2

clean:
	rm ./test1/test1 ./test2/test2 ./test4/test4
