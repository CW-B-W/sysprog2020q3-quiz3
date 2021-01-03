set term png
set output 'test2-bench.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"

plot [0:1000][0:0.1] 'func0.dat' with points title '4 branches', \
         'func1.dat' with points title '3 branches', \
         'func2.dat' with points title 'naive'
