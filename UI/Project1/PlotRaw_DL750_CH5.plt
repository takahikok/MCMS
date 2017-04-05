set term png enhanced transparent truecolor font arial 11 size 400, 200
set out "PlotRaw_DL750_CH5.png"
set datafile separator ','
set grid xtics ytics
set nokey
set multiplot 
set origin 0.200000, 0.250000
set size 0.750000, 0.650000
set margin 0, 0, 0, 0
set label 1 left at graph 0.000000, 1.060000 "CH5 - DL750"
set label 2 right at graph 1.000000, 1.060000 "#0"
set yrange [*<0:0<*]
set format y "%1.1tE%+-T"
set label 3 center at graph 0.500000, -0.300000 "Time [s]"
set label 4 center at graph -0.230000, 0.500000 rotate "Voltage [V]"
set xrange [-0.500000:4.505000]
plot "D7T00016.CSV" every 10 using (-0.5 + (column(0)) * 10 * 2e-05):2 with line
set print "PlotRaw_DL750_CH5.tmp"
print GPVAL_Y_MIN
print GPVAL_Y_MAX

