#!/usr/bin/wish

frame .upper -bg green
pack .upper  -side top -padx 5 -pady 5
frame .lower -bg blue
pack .lower  -side bottom -padx 5 -pady 5
button .ul -padx 5 -pady 5 -text ul -bg red
pack .ul -in .upper -side left -padx 5 -pady 5
button .ur -padx 5 -pady 5 -text ur -bg red
pack .ur -in .upper -side right -padx 5 -pady 5
button .ll -padx 5 -pady 5 -text ll -bg red
pack .ll -in .lower -side left -padx 5 -pady 5
button .lr -padx 5 -pady 5 -text lr -bg red
pack .lr -in .lower -side right -padx 5 -pady 5


