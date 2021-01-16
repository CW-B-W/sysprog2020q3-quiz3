set term png
set output 'test5-bench-mid_O2_UL.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"
plot [0:100][0:0.005]\
    '0x13579BDF2468ACE0_O2_UL.dat' using 1:2 title 'Mid Density naive', \
    '0x13579BDF2468ACE0_O2_UL.dat' using 1:3 title 'Mid Density improved', \
    '0x13579BDF2468ACE0_O2_UL.dat' using 1:4 title 'Mid Density improved more', \
    '0x13579BDF2468ACE0_O2_UL.dat' using 1:4 title 'Mid Density improved guaneec'

set term png
set output 'test5-bench-zero_O2_UL.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"
plot [0:100][0:0.005]\
    '0x0000000000000000_O2_UL.dat' using 1:2 title 'Zero Density naive', \
    '0x0000000000000000_O2_UL.dat' using 1:3 title 'Zero Density improved', \
    '0x0000000000000000_O2_UL.dat' using 1:4 title 'Zero Density improved more', \
    '0x0000000000000000_O2_UL.dat' using 1:4 title 'Zero Density improved guaneec'

set term png
set output 'test5-bench-one_O2_UL.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"
plot [0:100][0:0.005]\
    '0x0000000000000001_O2_UL.dat' using 1:2 title 'One Density naive', \
    '0x0000000000000001_O2_UL.dat' using 1:3 title 'One Density improved', \
    '0x0000000000000001_O2_UL.dat' using 1:4 title 'One Density improved more', \
    '0x0000000000000001_O2_UL.dat' using 1:4 title 'One Density improved guaneec'

set term png
set output 'test5-bench-almost_full_O2_UL.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"
plot [0:100][0:0.005]\
    '0x7FFFFFFFFFFFFFFF_O2_UL.dat' using 1:2 title 'Almost Full Density naive', \
    '0x7FFFFFFFFFFFFFFF_O2_UL.dat' using 1:3 title 'Almost Full Density improved', \
    '0x7FFFFFFFFFFFFFFF_O2_UL.dat' using 1:4 title 'Almost Full Density improved more', \
    '0x7FFFFFFFFFFFFFFF_O2_UL.dat' using 1:4 title 'Almost Full Density improved guaneec'

set term png
set output 'test5-bench-full_O2_UL.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"
plot [0:100][0:0.005]\
    '0xFFFFFFFFFFFFFFFF_O2_UL.dat' using 1:2 title 'Full Density naive', \
    '0xFFFFFFFFFFFFFFFF_O2_UL.dat' using 1:3 title 'Full Density improved', \
    '0xFFFFFFFFFFFFFFFF_O2_UL.dat' using 1:4 title 'Full Density improved more', \
    '0xFFFFFFFFFFFFFFFF_O2_UL.dat' using 1:4 title 'Full Density improved guaneec'