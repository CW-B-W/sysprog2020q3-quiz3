set term png
set output 'test2-bench.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"

plot     [0:100][0:0.05]\
         'func0.dat' with points title '2 branches', \
         'func1.dat' with points title '1 branches', \
         'func2.dat' with points title '0 branches', \
         'func3.dat' with points title 'naive', \
         'func4.dat' with points title 'math'

set term png
set output 'test2-bench-branch.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"

plot     [0:100][0:0.05]\
         'branch_func0.dat' with points title '2 branches', \
         'branch_func1.dat' with points title '1 branches', \
         'branch_func2.dat' with points title '0 branches', \
         'branch_func3.dat' with points title 'naive', \
         'branch_func4.dat' with points title 'math'
