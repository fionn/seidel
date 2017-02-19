#!/usr/bin/gnuplot

set xlabel "{/:Italic x}"
set ylabel "{/:Italic y}"
set zlabel "{/:Italic E_x}"

#set surface
unset colorbox
unset key

set dgrid3d 100,100 qnorm 4
#set dgrid3d 100,100 exp
set style data lines
set xyplane 0

splot "ey.dat" w l palette

pause -1

