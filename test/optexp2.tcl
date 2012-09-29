#!/usr/bin/wish
# 實驗各種 option 的效果. 此處以 -bg, -text, 與 -bd 為例.
# 當你遇到其他有疑問的 options 時, 不妨多多利用這個程式 (加以修改) 來實驗.

frame .show
pack .show -side left
label .show.watchme -relief ridge -text "<no files selected>"
pack .show.watchme -side top
scale .show.bd -orient horizontal -from 0 -to 50 -length 200 -command change_bd
pack .show.bd -side top

frame .control
pack .control -side left
button .control.bg -text -bg -command change_bg
pack .control.bg -side top
button .control.text -text -text -command change_text
pack .control.text -side top

# =================================================================

proc change_bd {bd} {
    .show.watchme configure -bd $bd
}

proc change_bg {} {
    set color [.show.watchme cget -bg]
    set color [tk_chooseColor -initialcolor $color]
    if {$color == ""} then return
    .show.watchme configure -bg $color
}

proc change_text {} {
    set fn [tk_getOpenFile]
    if {$fn == ""} then return
    .show.watchme configure -text $fn
}


