set term png
set output './plots/test4-test0.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"

plot [:][0:0.03] './plot-data/test0-func0.dat' with points title 'gcd recursive', \
                 './plot-data/test0-func1.dat' with points title 'gcd iterative', \
                 './plot-data/test0-func2.dat' with points title 'bgcd recursive', \
                 './plot-data/test0-func3.dat' with points title 'bgcd iterative', \
                 './plot-data/test0-func4.dat' with points title 'bgcd ctz'

set term png
set output './plots/test4-test1.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"

plot [:][0:0.03] './plot-data/test1-func0.dat' with points title 'gcd recursive', \
                 './plot-data/test1-func1.dat' with points title 'gcd iterative', \
                 './plot-data/test1-func2.dat' with points title 'bgcd recursive', \
                 './plot-data/test1-func3.dat' with points title 'bgcd iterative', \
                 './plot-data/test1-func4.dat' with points title 'bgcd ctz'

set term png
set output './plots/test4-test2.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"

plot [:][0:0.03] './plot-data/test2-func0.dat' with points title 'gcd recursive', \
                 './plot-data/test2-func1.dat' with points title 'gcd iterative', \
                 './plot-data/test2-func2.dat' with points title 'bgcd recursive', \
                 './plot-data/test2-func3.dat' with points title 'bgcd iterative', \
                 './plot-data/test2-func4.dat' with points title 'bgcd ctz'

set term png
set output './plots/test4-test3.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"

plot [:][0:0.03] './plot-data/test3-func0.dat' with points title 'gcd recursive', \
                 './plot-data/test3-func1.dat' with points title 'gcd iterative', \
                 './plot-data/test3-func2.dat' with points title 'bgcd recursive', \
                 './plot-data/test3-func3.dat' with points title 'bgcd iterative', \
                 './plot-data/test3-func4.dat' with points title 'bgcd ctz'

set term png
set output './plots/test4-test4.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"

plot [:][0:0.03] './plot-data/test4-func0.dat' with points title 'gcd recursive', \
                 './plot-data/test4-func1.dat' with points title 'gcd iterative', \
                 './plot-data/test4-func2.dat' with points title 'bgcd recursive', \
                 './plot-data/test4-func3.dat' with points title 'bgcd iterative', \
                 './plot-data/test4-func4.dat' with points title 'bgcd ctz'
