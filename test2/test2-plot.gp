set term png
set output 'test2-bench.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"

plot     [0:100][0:0.05]\
         'func0.dat' with points title '4 branches', \
         'func1.dat' with points title '3 branches', \
         'func2.dat' with points title '0 branches', \
         'func3.dat' with points title 'naive'

set term png
set output 'test2-bench-branch.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"

plot     [0:100][0:0.05]\
         'branch_func0.dat' with points title '4 branches', \
         'branch_func1.dat' with points title '3 branches', \
         'branch_func2.dat' with points title '0 branches', \
         'branch_func3.dat' with points title 'naive'
