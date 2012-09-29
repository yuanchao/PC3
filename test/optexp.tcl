#!/usr/bin/wish
# ����U�� option ���ĪG. ���B�H -justify �P -anchor ����.
# ��A�J���L���ðݪ� options ��, �����h�h�Q�γo�ӵ{�� (�[�H�ק�) �ӹ���.

frame .show
pack .show -side left
label .show.watchme -width 30 -height 8 -bd 2 -relief groove -text \
    "Effect\nOf justify\nAnd anchor"
pack .show.watchme -side top
label .show.costr
pack .show.costr -side top

frame .control
pack .control -side left
button .control.action -text "Change It!" -command change_it
pack .control.action -side top
frame .control.just
pack .control.just -side top
radiobutton .control.just.left
radiobutton .control.just.center
radiobutton .control.just.right
pack .control.just.left .control.just.center .control.just.right -side left
set v_just center
foreach item {left center right} {
    .control.just.$item configure -variable v_just -value $item -text $item
}

listbox .control.anchor
pack .control.anchor -side top
.control.anchor insert 0 nw n ne w center e sw s se
.control.anchor selection set 4

proc change_it {} {
    global v_just
    set anchor [.control.anchor get [.control.anchor curselection]]
    .show.costr configure -text "-justify $v_just -anchor $anchor"
    .show.watchme configure -justify $v_just -anchor $anchor
}


