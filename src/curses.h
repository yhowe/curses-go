/*-
 * Copyright (c) 2019 Y. Howe <yhowe01@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <utility/Display.h>

#define	__arraycount(__x)	(sizeof(__x) / sizeof(__x[0]))

char readparse_buttons(void);
void attrset(int n);
void init_pair(int, int, int);
int  initscr(void);
void clear(void);
void move(int, int);
void printw(const char *, ...);
void mvprintw(int, int, const char *, ...);
void timeout(int);
void beep(void);

#if defined(APP_TEXTSIZE1)
#define APP_TEXTSIZE 1
#define COLS 53
#define LINES 28
#elif defined(APP_TEXTSIZE2)
#define APP_TEXTSIZE 2
#define COLS 26
#define LINES 15
#else
#error must define APP_TEXTSIZE(1,2,3,4)
#endif

#define getch() readparse_buttons()

#define COLOR_BLACK TFT_BLACK
#define COLOR_WHITE TFT_WHITE
#define COLOR_RED TFT_RED
#define COLOR_GREEN TFT_DARKGREEN
#define COLOR_BLUE TFT_BLUE
#define COLOR_CYAN TFT_DARKCYAN
#define COLOR_YELLOW TFT_YELLOW
#define COLOR_MAGENTA TFT_MAGENTA
#define COLOR_CYAN TFT_DARKCYAN

#define COLOR_PAIR

#define refresh()
#define endwin()
#define has_colors() 1
#define start_color()
#define flushinp() {}
