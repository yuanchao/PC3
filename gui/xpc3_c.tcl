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

# the correction constant
set c_corr_1 0.011
set c_corr_2 0.028
set c_corr_3 0.

# the correction applied
set m_corr_1 0.
set m_corr_2 0.
set m_corr_3 0.

# the direction of last step
set m_last_dir_1 1
set m_last_dir_2 1
set m_last_dir_3 1

set COMM [open $COMPORT "RDWR"]
fconfigure $COMM -blocking yes -buffering none -mode 9600,n,8,1
#fconfigure $COMM -blocking yes -mode 9600,n,8,1

puts -nonewline $COMM "V0 100\r"
sleep 1
puts -nonewline $COMM "M0 -1.0\r"
sleep 3
puts -nonewline $COMM "M0 +1.0\r"
sleep 3

frame .upper
pack .upper  -side top
frame .lower
pack .lower  -side bottom -fill both

frame .lower.left
pack .lower.left -side left -fill both
frame .lower.right
pack .lower.right -side right -fill both

label .upper.status -text "X:+00.000\t Y:+00.000\t Z:+00.000 " -bg green
pack .upper.status -side left -fill x

label .lower.left.ftune -text "Fine Tune" -bg cyan
pack .lower.left.ftune -side top

frame .lower.left.axis1
pack .lower.left.axis1 -side top
frame .lower.left.axis2
pack .lower.left.axis2 -side top
frame .lower.left.axis3
pack .lower.left.axis3 -side top

button .lower.left.axis1.sub -text "-" -command axis1_sub
pack .lower.left.axis1.sub -side left
entry .lower.left.axis1.entry -width 8 -textvariable s_axis1
pack .lower.left.axis1.entry -side left
button .lower.left.axis1.add -text "+" -command axis1_add
pack .lower.left.axis1.add -side left

button .lower.left.axis2.sub -text "-" -command axis2_sub
pack .lower.left.axis2.sub -side left
entry .lower.left.axis2.entry -width 8 -textvariable s_axis2
pack .lower.left.axis2.entry -side left
button .lower.left.axis2.add -text "+" -command axis2_add
pack .lower.left.axis2.add -side left

button .lower.left.axis3.sub -text "-" -command axis3_sub
pack .lower.left.axis3.sub -side left
entry .lower.left.axis3.entry -width 8 -textvariable s_axis3
pack .lower.left.axis3.entry -side left
button .lower.left.axis3.add -text "+" -command axis3_add
pack .lower.left.axis3.add -side left

label .lower.right.ftune -text "Command set" -bg cyan
pack .lower.right.ftune -side top

button .lower.right.home -text "HOME" -command go_home
pack .lower.right.home -side left -fill both
button .lower.right.step -text "STEP" -command go_step
pack .lower.right.step -side left -fill both

button .lower.right.q_stat -text "Querry" -command q_stat
pack .lower.right.q_stat -side left -fill both


proc axis1_add {} {
    global COMM s_axis1
    if { $m_last_dir_1 == -1} then {
	set s_axis1 [expr $s_axis1+$c_corr_1]
	set m_corr_1 [expr $m_corr_1+$c_corr_1]
    }
    set cmdString [format "M1 +%06.3f\r" $s_axis1]
    puts -nonewline $COMM $cmdString
    set m_last_dir_1 1
}
proc axis1_sub {} {
    global COMM s_axis1
    if { $m_last_dir_1 == 1} then {
	set s_axis1 [expr $s_axis1+$c_corr_1]
	set m_corr_1 [expr $m_corr_1-$c_corr_1]
    }
    set cmdString [format "M1 -%06.3f\r" $s_axis1]
    puts -nonewline $COMM $cmdString
    set m_last_dir_1 -1
}

proc axis2_add {} {
    global COMM s_axis2
    if { $m_last_dir_2 == -1} then {
	set s_axis2 [expr $s_axis2+$c_corr_2]
	set m_corr_2 [expr $m_corr_2+$c_corr_2]
    }
    set cmdString [format "M2 +%06.3f\r" $s_axis2]
    puts -nonewline $COMM $cmdString
    set m_last_dir_2 1
}
proc axis2_sub {} {
    global COMM s_axis2
    if { $m_last_dir_2 == 1} then {
	set s_axis2 [expr $s_axis2+$c_corr_2]
	set m_corr_2 [expr $m_corr_2-$c_corr_2]
    }
    set cmdString [format "M2 -%06.3f\r" $s_axis2]
    puts -nonewline $COMM $cmdString
    set m_last_dir_2 -1
}

proc axis3_add {} {
    global COMM s_axis3
    if { $m_last_dir_3 == -1} then {
	set s_axis3 [expr $s_axis3+$c_corr_3]
	set m_corr_3 [expr $m_corr_3+$c_corr_3]
    }
    set cmdString [format "M3 +%06.3f\r" $s_axis3]
    puts -nonewline $COMM $cmdString
    set m_last_dir_3 1
}
proc axis3_sub {} {
    global COMM s_axis3
    if { $m_last_dir_3 == 1} then {
	set s_axis3 [expr $s_axis3+$c_corr_3]
	set m_corr_3 [expr $m_corr_3-$c_corr_3]
    }
    set cmdString [format "M3 -%06.3f\r" $s_axis3]
    puts -nonewline $COMM $cmdString
    set m_last_dir_3 -1
}

proc go_home {} {
    global COMM
    puts -nonewline $COMM "H\r"
}
proc go_step {} {
    global COMM COMPORT

    puts "Stepping..."
    close $COMM

    exec ./pc3 output.log

    puts "done..."
    set COMM [open $COMPORT "RDWR"]
    fconfigure $COMM -blocking yes -buffering none -mode 9600,n,8,1

}

proc q_stat {} {
#    global COMM s_axis1 s_axis2 s_axis3 all_stat
    global COMM
    set garbage ""

    puts -nonewline $COMM "Q\r"
    flush $COMM
    after 200
    gets $COMM m_axis1
    gets $COMM m_axis2
    gets $COMM m_axis3

    set m_axis1 [expr $m_axis1-$c_corr_1]
    set m_axis2 [expr $m_axis2-$c_corr_2]
    set m_axis3 [expr $m_axis3-$c_corr_3]

    gets $COMM all_stat
    gets $COMM garbage
    gets $COMM garbage
    gets $COMM garbage

    set m_stat [format "X:%+07.3f\t Y:%+07.3f\t Z:%+07.3f %s" \
                                      $m_axis1 $m_axis2 $m_axis3 $all_stat]

   .upper.status config -text $m_stat 
}
