set term png
set output 'test2-bench.png'

plot 'func0.dat' with points title '4 branches', \
         'func1.dat' with points title '3 branches'
