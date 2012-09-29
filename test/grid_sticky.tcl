#!/usr/bin/wish
# 修改自 http://www.beedub.com/book/2nd/
# "Practical Programming in Tcl and Tk" 原作者 Brent Welch
set index 0
foreach x {"" w e ew s ws es ews n nw ne new ns nws nes news} {
    frame .f$x -borderwidth 2 -relief ridge -width 40 -height 40
    grid .f$x  -sticky news \
	-row [expr $index/4] -column [expr $index%4]
    label .l$x -text $x -background white
    grid .l$x -sticky $x -padx 2 -pady 2 \
	-row [expr $index/4] -column [expr $index%4]
    incr index
}


