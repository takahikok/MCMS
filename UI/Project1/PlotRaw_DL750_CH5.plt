set term png enhanced transparent truecolor font arial 11 size 400, 200
set out "PlotRaw_DL750_CH5.png"
set datafile separator ','
set grid xtics ytics
set nokey
set multiplot 
set origin 0.2, 0.25
set size 0.75, 0.65
set lmargin 0
set rmargin 0
set tmargin 0
set bmargin 0
set label 2 left at graph 0,1.06 "CH5 - DL750"
set label 3 right at graph 1,1.06 "#0"
set yrange [*<0:0<*]
set format y "%1.1tE%+-T"
set label 10 center at graph 0.5, -0.3 "Time [s]"
set label 11 center at graph -0.23, 0.5 rotate "Voltage [V]"
set xrange [-0.5:4.505]
plot "D7T00011.CSV" every 10 using (-0.5 + (column(0)) * 10 * 2e-05):2 with line

