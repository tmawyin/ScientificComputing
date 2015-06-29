# gnuplot script for generating plot of ODE system
# created by Tomas Mawyin
# SCMP132 - HW 6

set term postscript enhanced color solid
set output 'plot_ODE.eps'
set xlabel 'Time (sec)'
set ylabel 'Position (m)'
set y2label 'Velocity (m/s)'
set title "Position and Velocity Response - Bouncing Particle"
set grid x y
set y2tics

set key right top

plot 'result.txt' u ($1):($2) lt rgb "black" lw 2 title 'x-position' w l axes x1y1, \
'result.txt' u ($1):($3) lt rgb "blue"  lw 2 title 'y-position' w l axes x1y1, \
'result.txt' u ($1):($4) lt rgb "red"   lw 2 title 'x-velocity' w l axes x1y2, \
'result.txt' u ($1):($5) lt rgb "green" lw 2 title 'y-velocity' w l axes x1y2, \
