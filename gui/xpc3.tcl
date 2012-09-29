#!/usr/bin/wish

#
# GUI for PC3 scanning table controller
# Written By: Yuan Chao
# 2002/04/14
#

wm title . "NTUHEP/PC3"

global s_axis1 s_axis2 s_axis3 all_stat
global COMPORT COMM

set COMPORT /dev/ttyS0

set s_axis1 00.000
set s_axis2 00.000
set s_axis3 00.000


#set COMM [open $COMPORT "RDWR"]
#fconfigure $COMM -blocking yes -buffering none -mode 9600,n,8,1
#fconfigure $COMM -blocking yes -mode 9600,n,8,1

#puts -nonewline $COMM "V1 200\r"
after 200
#puts -nonewline $COMM "V2 2000\r"
after 200
#puts -nonewline $COMM "V3 200\r"
after 200
#flush $COMM

global m_top_lt m_btm_lt

set m_top_lt 0
set m_btm_lt 0

#exec xawtv &
#after 2000

global QX3

#set QX3 [open /proc/cpia/video0 "RDWR"]
#puts $QX3 "toplight: off"
#flush $QX3

frame .upper
pack .upper  -side top
frame .lower
pack .lower  -side bottom -fill both

frame .lower.left
pack .lower.left -side left -fill both
frame .lower.center
pack .lower.center -side left -fill both
frame .lower.right
pack .lower.right -side right -fill both

label .upper.status -text "X:+00.000\t Y:+00.000\t Z:+00.000 W WWW" -bg green
pack .upper.status -side left -fill x

label .lower.left.ftune -text "Fine Tune" -bg cyan
pack .lower.left.ftune -side top

frame .lower.left.axis1
pack .lower.left.axis1 -side top
frame .lower.left.axis2
pack .lower.left.axis2 -side top
frame .lower.left.axis3
pack .lower.left.axis3 -side top

button .lower.left.axis1.sub -text "-" -command { pc3_move 1 -$s_axis1 }
pack .lower.left.axis1.sub -side left
entry .lower.left.axis1.entry -width 8 -textvariable s_axis1
pack .lower.left.axis1.entry -side left
button .lower.left.axis1.add -text "+" -command { pc3_move 1 $s_axis1 }
pack .lower.left.axis1.add -side left

button .lower.left.axis2.sub -text "-" -command { pc3_move 2 -$s_axis2 }
pack .lower.left.axis2.sub -side left
entry .lower.left.axis2.entry -width 8 -textvariable s_axis2
pack .lower.left.axis2.entry -side left
button .lower.left.axis2.add -text "+" -command { pc3_move 2 $s_axis2 }
pack .lower.left.axis2.add -side left

button .lower.left.axis3.sub -text "-" -command { pc3_move 3 -$s_axis3 }
pack .lower.left.axis3.sub -side left
entry .lower.left.axis3.entry -width 8 -textvariable s_axis3
pack .lower.left.axis3.entry -side left
button .lower.left.axis3.add -text "+" -command { pc3_move 3 $s_axis3 }
pack .lower.left.axis3.add -side left

label .lower.center.cmd_set -text "Command set" -bg cyan
pack .lower.center.cmd_set -side top

button .lower.center.home -text "HOME" -command go_home
pack .lower.center.home -side left -fill both
button .lower.center.target -text "Target" -command go_target
pack .lower.center.target -side left -fill both
button .lower.center.step -text "STEP" -command go_step
pack .lower.center.step -side left -fill both

button .lower.center.q_stat -text "Querry" -command pc3_stat
pack .lower.center.q_stat -side left -fill both

label .lower.right.qx3 -text "QX3 Lit" -bg cyan
pack .lower.right.qx3 -side top

button .lower.right.top_lt -text "Top" -bg blue -fg white -command qx3_top_lt
pack .lower.right.top_lt -side top -fill both -expand yes
button .lower.right.btm_lt -text "Bottom" -bg blue -fg white -command qx3_btm_lt
pack .lower.right.btm_lt -side bottom -fill both -expand yes


proc pc3_move {m_dir m_dist} {
    global COMM

    if {$m_dir == 3} {
        set cmdString [format "M%d %+06.3f\r" $m_dir $m_dist]
        puts -nonewline $COMM $cmdString
    } else {
        puts -nonewline $COMM "M3 -0.1\r"
        after 300
        set cmdString [format "M%d %+06.3f\r" $m_dir $m_dist]
        puts -nonewline $COMM $cmdString
#        after 300
        pc3_wait
        puts -nonewline $COMM "M3 +0.1\r"
    }
    pc3_wait
}

proc pc3_wait {} {
    global COMM

    pc3_stat

    set all_stat "R"
    set stat_x "R"
    set stat_y "R"
    set stat_z "R"

    while { $all_stat == "R" || \
            $stat_x == "R" || $stat_y == "R" || $stat_z == "R" } {
        flush $COMM
        puts -nonewline $COMM "Q\r"
        after 200
        gets $COMM m_axis1
        gets $COMM m_axis2
        gets $COMM m_axis3

        gets $COMM all_stat
        gets $COMM stat_x
        gets $COMM stat_y
        gets $COMM stat_z

        set m_stat [format "X:%+07.3f\t Y:%+07.3f\t Z:%+07.3f %s %s%s%s" \
                $m_axis1 $m_axis2 $m_axis3 $all_stat $stat_x $stat_y $stat_z ]

        .upper.status config -text $m_stat 
        update

        after 200
    }
}

proc go_home {} {
    global COMM
#    puts -nonewline $COMM "H\r"
    pc3_stat
    puts -nonewline $COMM "V0 2000\r"
    after 300
    puts -nonewline $COMM "M3 -20.000\r"
    after 1000
    puts -nonewline $COMM "M1 -30.000\r"
    after 500
    puts -nonewline $COMM "M2 -99.999\r"
    pc3_wait
    puts -nonewline $COMM "C0 +00.000\r"

    puts -nonewline $COMM "V1 200\r"
    after 200
    puts -nonewline $COMM "V3 200\r"
    after 200
    pc3_stat
}

proc go_target {} {
    global COMM

    go_home
#    puts -nonewline $COMM "H\r"
    pc3_stat
    puts -nonewline $COMM "V0 2000\r"
    after 300
    puts -nonewline $COMM "M1 +06.800\r"
    after 500
    puts -nonewline $COMM "M2 +12.000\r"
    pc3_wait
    puts -nonewline $COMM "M3 +16.000\r"
    pc3_wait
                                                                                
    puts -nonewline $COMM "V1 200\r"
    after 200
    puts -nonewline $COMM "V3 200\r"
    after 200
    pc3_stat

}

proc go_step {} {
    global COMM COMPORT

    puts "Stepping..."
    close $COMM

    set f_name ../[clock format [clock seconds] -format "%Y%m%d%H%M%S"].dat
    exec ../pc3 $f_name

    puts "done..."
    set COMM [open $COMPORT "RDWR"]
    fconfigure $COMM -blocking yes -buffering none -mode 9600,n,8,1

}

proc pc3_stat {} {
#    global COMM s_axis1 s_axis2 s_axis3 all_stat
    global COMM
    set garbage ""

    flush $COMM
    puts -nonewline $COMM "Q\r"
    after 200
    gets $COMM m_axis1
    gets $COMM m_axis2
    gets $COMM m_axis3

    gets $COMM all_stat
    gets $COMM stat_x
    gets $COMM stat_y
    gets $COMM stat_z

    set m_stat [format "X:%+07.3f\t Y:%+07.3f\t Z:%+07.3f %s %s%s%s" \
                $m_axis1 $m_axis2 $m_axis3 $all_stat $stat_x $stat_y $stat_z ]

    .upper.status config -text $m_stat 
    update
}

proc qx3_top_lt {} {
    global QX3
    global m_top_lt
    global m_btm_lt

    set QX3 [open /proc/cpia/video0 "RDWR"]

    if {$m_top_lt == 0} {
       puts $QX3 "toplight: on"
       flush $QX3
       set m_top_lt 1
       .lower.right.top_lt config -bg orange
    } else {
       puts $QX3 "toplight: off"
       flush $QX3
       set m_top_lt 0
       .lower.right.top_lt config -bg blue
    }

    close $QX3
}

proc qx3_btm_lt {} {
    global QX3
    global m_top_lt
    global m_btm_lt

    set QX3 [open /proc/cpia/video0 "RDWR"]

    if {$m_btm_lt == 0} {
       puts $QX3 "bottomlight: on"
       flush $QX3
       set m_btm_lt 1
       .lower.right.btm_lt config -bg orange
    } else {
       puts $QX3 "bottomlight: off"
       flush $QX3
       set m_btm_lt 0
       .lower.right.btm_lt config -bg blue
    }

    close $QX3
}

