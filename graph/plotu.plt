#!/usr/bin/gnuplot

set xlabel "{/:Italic x}"
set ylabel "{/:Italic y}"
set zlabel "{/:Italic u}"

#set surface
unset colorbox
unset key
set zrange[0:1]
set xyplane 0

splot "<awk -f addblanks.awk u.dat" w pm3d

pause -1

