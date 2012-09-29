#!/usr/bin/wish

frame .upper -bg green
pack .upper  -side top -padx 5 -pady 5
frame .lower -bg blue
pack .lower  -side bottom -padx 5 -pady 5
button .upper.left -padx 5 -pady 5 -text ul -bg red
pack .upper.left -side left -padx 5 -pady 5
button .upper.right -padx 5 -pady 5 -text ur -bg red
pack .upper.right -side right -padx 5 -pady 5
button .lower.left -padx 5 -pady 5 -text ll -bg red
pack .lower.left -side left -padx 5 -pady 5
button .lower.right -padx 5 -pady 5 -text lr -bg red
pack .lower.right -side right -padx 5 -pady 5

