#!/usr/bin/wish

source color_model

proc RotateText {} {
    global count text_offset
    set msg "TK: the most portable GUI tool!"
    for {set i 0} {$i<$count} {incr i} {
	.box{$i} configure -text [string index $msg [expr ($i+$text_offset) % $count]]
    }
    after 300 RotateText
#    update idletasks
    set text_offset [expr ($text_offset+1) % $count]
}

proc RotateColor {} {
    global count color_offset
    for {set i 0} {$i<$count} {incr i} {
	set x [expr ($i+$color_offset) % $count / double($count)]
	.box{$i} configure -bg [HSBtoSTR $x 1 255]
    }
    after 260 RotateColor
#    update idletasks
    set color_offset [expr ($color_offset-1) % $count]
}

set coord {
  {0 0} {0 1} {0 2} {0 3} {0 4} {0 5} {0 6} 
  {1 6} {2 6} {2 5} {2 4} {3 4} {4 4} {4 5} {4 6} {5 6} 
  {6 6} {6 5} {6 4} {6 3} {6 2} {6 1} {6 0} 
  {5 0} {4 0} {4 1} {4 2} {3 2} {2 2} {2 1} {2 0} {1 0} 
}

# puts [lindex [lindex $coord 3] 1]

set count [llength $coord]
for {set i 0} {$i<$count} {incr i} {
    label .box{$i} -width 1
    grid .box{$i} -row [lindex [lindex $coord $i] 0] -column [lindex [lindex $coord $i] 1]
}

set color_offset 0
set text_offset 0
RotateText
RotateColor


