All: test1 test2 test4 test5

test1: ./test1/test1

test1-test: ./test1/test1
	cd test1 && ./test1

./test1/test1: ./test1/test1.cpp
	clang-format -i -style=file $^
	g++ --std=c++17 -fsanitize=undefined -Wall $^ -o $@

test2: ./test2/test2

test2-test: ./test2/test2
	cd test2 && ./test2

test2-plot: $(wildcard ./test2/*.dat)
	cd test2 && gnuplot test2-plot.gp

./test2/test2: ./test2/test2.cpp
	clang-format -i -style=file $^
	g++ --std=c++17 -Wall $^ -o $@

test4: ./test4/test4

test4-test: ./test4/test4
	cd test4 && ./test4

test4-plot: $(wildcard ./test4/*.dat)
	cd test4 && gnuplot test4-plot.gp

./test4/test4: ./test4/test4.cpp
	clang-format -i -style=file $^
	g++ --std=c++17 -Wall $^ -o $@ -O2

test5: ./test5/test5 ./test5/test5_O3

test5-test: ./test5/test5 ./test5/test5_O3
	cd test5 && ./test5
	cd test5 && ./test5_O3

test5-plot: $(wildcard ./test5/*.dat)
	cd test5 && gnuplot test5-plot.gp
	cd test5 && gnuplot test5-plot_O3.gp

./test5/test5: ./test5/test5.cpp
	clang-format -i -style=file $^
	g++ --std=c++17 -Wall $^ -o $@ -O2

./test5/test5_O3: ./test5/test5_O3.cpp
	clang-format -i -style=file $^
	g++ --std=c++17 -Wall $^ -o $@ -O3 -funroll-loops

clean:
	rm ./test1/test1 ./test2/test2 ./test4/test4 ./test5/test5 ./test5/test5_O3
