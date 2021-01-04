set term png
set output 'test5-bench.png'
set xlabel "i-th test"
set ylabel "exec time (sec)"

plot [0:200] '0x0000000000000000.dat' using 1:2, '0x0000000000000000.dat' using 1:3, \
'0x0000000000000001.dat' using 1:2, '0x0000000000000001.dat' using 1:3, \
'0x0000000000000003.dat' using 1:2, '0x0000000000000003.dat' using 1:3, \
'0x0000FFFF0000FFFF.dat' using 1:2, '0x0000FFFF0000FFFF.dat' using 1:3, \
'0x13579BDF13579BDF.dat' using 1:2, '0x13579BDF13579BDF.dat' using 1:3, \
'0xF0F0F0F0F0F0F0F0.dat' using 1:2, '0xF0F0F0F0F0F0F0F0.dat' using 1:3, \
'0xFFFFFFFFFFFFFFFF.dat' using 1:2, '0xFFFFFFFFFFFFFFFF.dat' using 1:3, \