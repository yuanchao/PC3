#!/usr/bin/wish

button .n -bg blue
button .s -bg blue
button .w -bg red
button .e -bg green
button .ne -bg magenta
button .sw -bg cyan

grid .n -row 0 -column 0 -sticky news
grid .s -row 4 -column 1 -sticky news
grid .w -row 1 -column 0 -sticky news
grid .e -row 0 -column 4 -sticky news
grid .ne -row 0 -column 2 -sticky news
grid .sw -row 2 -column 0 -sticky news

grid .n .s -columnspan 4
grid .w .e -rowspan 4
grid .ne .sw -columnspan 3
grid .ne .sw -rowspan 3

for {set i 0} {$i < 5} {incr i} {
    grid columnconfigure . $i -minsize 30
    grid rowconfigure . $i -minsize 30
}

grid rowconfigure . 1 -weight 1
grid rowconfigure . 2 -weight 3
grid rowconfigure . 3 -weight 1
grid columnconfigure . 1 -weight 1
grid columnconfigure . 2 -weight 3
grid columnconfigure . 3 -weight 1

foreach x {.n .s .w .e .ne .sw} {
    # $x configure -command [list raise $x]
    bind $x <Enter> {raise %W}
}


