#!/usr/bin/wish

set current_file ""

wm protocol . WM_DELETE_WINDOW OnQuit
frame .menubar -relief raised -bd 2
pack .menubar -side top -fill x
frame .status -relief sunken -bd 2
pack .status -side bottom -fill x
canvas .worksp -width 300 -height 200
pack .worksp -side top -fill both -expand yes

menubutton .menubar.file -text File -menu .menubar.file.menu
menu .menubar.file.menu -tearoff 0
.menubar.file.menu add command -label Open -command OnOpen
.menubar.file.menu add separator
.menubar.file.menu add command -label Quit -command OnQuit
menubutton .menubar.options -text Options -menu .menubar.options.menu
menu .menubar.options.menu -tearoff 0
.menubar.options.menu add command -label Background -command OnChangeBackground
.menubar.options.menu add checkbutton -label "Show border" -command OnShowBorder
menubutton .menubar.help -text Help -menu .menubar.help.menu
menu .menubar.help.menu -tearoff 0
.menubar.help.menu add command -label About -command HelpAbout
pack .menubar.file .menubar.options -side left
pack .menubar.help -side right

label .status.filename -textvariable current_file
pack .status.filename -side left

#=================================================================

proc OnOpen {} {
    global current_file
    set fn [tk_getOpenFile]
    if {$fn != ""} { set current_file $fn }
}

proc OnQuit {} {
    set ans [tk_messageBox -title quit -type yesnocancel -message \
	"File may have been modified. Save file before quitting?" ]
    if {$ans == "Cancel"} { return }
    # save file if $ans eq "Yes";
    # clean up
    exit
}

proc OnChangeBackground {} {
    set color [.worksp cget -bg]
    set color [tk_chooseColor -initialcolor $color]
    if {$color != ""} { .worksp configure -bg $color }
}

proc HelpAbout {} {
    set ans [tk_messageBox -title "About me" -type ok -message \
	"Nice to know that you are interested in this program!" ]
}

proc OnShowBorder {} {
    set mn [.menubar.options cget -menu]
    set st [$mn entrycget 0 -state]
# Q: I really don't mean "-state" here. Is there a clean way
# to query the current state of a checkbutton entry in a menu,
# without ever having to define an associated variable?
    puts $st
}


