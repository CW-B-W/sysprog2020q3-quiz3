set term png
set output 'test4-bench.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"

plot     'func0.dat' with points title 'mod operator', \
         'func1.dat' with points title 'original', \
         'func2.dat' with points title 'ctz', \
