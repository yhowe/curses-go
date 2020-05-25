# curses-go
curses(3) display and input function wrappers for the ODROID-GO

Functions are avail like getch, beep, init_colorpair, mvprintw.
See src/curses.h for more info

Applictians need to pass APPTEXT_SIZE1/2/3/ or 4 in CFLAGS in the
applications makefile or define it in the component makefile for
text font size selection.

ie:

CPPFLAGS += -DAPP_TEXTSIZE1=1

in the applications makefile.
