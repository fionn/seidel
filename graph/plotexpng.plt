#!/usr/bin/gnuplot

#set xlabel "{/:Italic x}"
#set ylabel "{/:Italic y}"
#set zlabel "{/:Italic E_x}"

#set surface
unset colorbox
unset key
unset border
unset tics

set dgrid3d 100,100 qnorm 4
#set dgrid3d 100,100 exp
set style data lines
set xyplane 0
set view 75,310

set terminal pngcairo size 2000,2000 crop transparent
set output "ex_cairo.png"

splot "ex.dat" w l palette

pause -1
