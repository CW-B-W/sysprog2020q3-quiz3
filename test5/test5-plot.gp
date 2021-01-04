set term png
set output 'test5-bench.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"

plot '0xFFF0FFF0FFF0FFF0.dat' using 1:2, '' using 1:3, '' using 1:4