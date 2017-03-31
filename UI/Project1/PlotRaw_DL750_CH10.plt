set term png enhanced transparent truecolor font arial 11 size 640, 480
set out "PlotRaw_DL750_CH10.png"
set datafile separator ','
set multiplot 
set origin 0.0, 0.46
set size 1.0, 0.5
set lmargin 7.5
set rmargin 2
set tmargin 0
set bmargin 0
set label 2 left at graph 0.05,0.9 "{/Arial (a)} {/Arial:Italic n}_{/Arial e}"
set yrange [*<0:0<*]
plot "ECR00039.CSV" every 10 using (-0.01 + (column(0)) * 10 * 5e-07):10 with line

