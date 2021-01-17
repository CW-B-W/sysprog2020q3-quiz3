set term png
set output './plots/test5-bench-mid_O2_UL8.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"
plot [0:100][0:0.002]\
    './plot-data/0x13579BDF2468ACE0_O2_UL8.dat' using 1:2 title 'Mid Density naive', \
    './plot-data/0x13579BDF2468ACE0_O2_UL8.dat' using 1:3 title 'Mid Density improved', \
    './plot-data/0x13579BDF2468ACE0_O2_UL8.dat' using 1:4 title 'Mid Density improved more'

set term png
set output './plots/test5-bench-zero_O2_UL8.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"
plot [0:100][0:0.002]\
    './plot-data/0x0000000000000000_O2_UL8.dat' using 1:2 title 'Zero Density naive', \
    './plot-data/0x0000000000000000_O2_UL8.dat' using 1:3 title 'Zero Density improved', \
    './plot-data/0x0000000000000000_O2_UL8.dat' using 1:4 title 'Zero Density improved more'

set term png
set output './plots/test5-bench-one_O2_UL8.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"
plot [0:100][0:0.002]\
    './plot-data/0x0000000000000001_O2_UL8.dat' using 1:2 title 'One Density naive', \
    './plot-data/0x0000000000000001_O2_UL8.dat' using 1:3 title 'One Density improved', \
    './plot-data/0x0000000000000001_O2_UL8.dat' using 1:4 title 'One Density improved more'

set term png
set output './plots/test5-bench-almost_full_O2_UL8.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"
plot [0:100][0:0.002]\
    './plot-data/0x7FFFFFFFFFFFFFFF_O2_UL8.dat' using 1:2 title 'Almost Full Density naive', \
    './plot-data/0x7FFFFFFFFFFFFFFF_O2_UL8.dat' using 1:3 title 'Almost Full Density improved', \
    './plot-data/0x7FFFFFFFFFFFFFFF_O2_UL8.dat' using 1:4 title 'Almost Full Density improved more'

set term png
set output './plots/test5-bench-full_O2_UL8.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"
plot [0:100][0:0.002]\
    './plot-data/0xFFFFFFFFFFFFFFFF_O2_UL8.dat' using 1:2 title 'Full Density naive', \
    './plot-data/0xFFFFFFFFFFFFFFFF_O2_UL8.dat' using 1:3 title 'Full Density improved', \
    './plot-data/0xFFFFFFFFFFFFFFFF_O2_UL8.dat' using 1:4 title 'Full Density improved more'