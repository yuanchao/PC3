#!/usr/bin/wish

set n_group 4
set n_item 3

for {set i 0} {$i < $n_group} {incr i} {
    frame .f$i -bd 4 -bg gray
    pack .f$i -side left
    bind .f$i <Button> [list complain .f$i]
    for {set j 0} {$j < $n_item} {incr j} {
	button .f$i.b$j -text "  " -command [list relinquish $i]
	pack .f$i.b$j -side top
    }
}

grab .f0
.f0 configure -bg red

proc complain { w } {
    puts "$w: click no one else but me!"
    for {set i 0} {$i < 3} {incr i} {
	$w configure -bg blue
	update idletasks
	after 100
	$w configure -bg red
	update idletasks
	after 100
    }
}

proc relinquish { i } {
    global n_group
    if {[.f$i cget -bg] == "gray"} {
	puts "No, not me, I am not allowed to respond now, sorry!"
	return
    }
    .f$i configure -bg gray
    set chosen [expr int(rand()*($n_group-1))]
    if {$chosen == $i} { set chosen [expr $n_group-1] }
    grab .f$chosen
    .f$chosen configure -bg red
}


