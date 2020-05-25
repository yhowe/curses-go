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

#include "odroid_go.h"
#include <unistd.h>

#include "./curses.h"

struct cpair {
	int16_t f;
	int16_t b;
};

cpair color_pairs[16];
char tmpstr[255];

extern int vol;

int bright = 255;

void
beep(void)
{
	if (vol)
		GO.Speaker.tone(2000, 100);
}

void
attrset(int n)
{
	GO.lcd.setTextColor(color_pairs[n].f, color_pairs[n].b);
}

void
init_pair(int N, int F, int B)
{
	color_pairs[N].f = F;
	color_pairs[N].b = B;
}

int
initscr(void)
{
	GO.lcd.invertDisplay(false);
	GO.lcd.setTextSize(APP_TEXTSIZE);
	GO.lcd.setTextFont(1);
	clear();

	return 1;
}

void
printw(const char *mystring, ...)
{
	va_list args;

	GO.lcd.setTextSize(APP_TEXTSIZE);
	GO.lcd.setTextFont(1);
	va_start(args, mystring);
	vsnprintf(tmpstr, sizeof(tmpstr), mystring, args);
	va_end(args);
	GO.lcd.print(tmpstr);
}

void
mvprintw(int Y, int X, const char *mystring, ...)
{
	va_list args;

	GO.lcd.setTextSize(APP_TEXTSIZE);
	GO.lcd.setTextFont(1);
	GO.lcd.setCharCursor(X, Y);
	va_start(args, mystring);
	vsnprintf(tmpstr, sizeof(tmpstr), mystring, args);
	va_end(args);
	GO.lcd.print(tmpstr);
}

void
clear()
{
	GO.lcd.setCharCursor(0, 0);
	GO.lcd.clearDisplay();
}

void
move(int Y, int X)
{
	GO.lcd.setCharCursor(X, Y);
}

int mytimeout = 0;

char readparse_buttons()
{
	int data;
	int timetowait = 0;
	char key = 0, oldkey = -1, holdkey = 1;
	bool keypressed = false;

	while (keypressed == false || oldkey != key) {
		if (holdkey && mytimeout && key == oldkey)
			break;
		if (holdkey)
			oldkey = key;
		if (mytimeout >= 0) {
			timetowait = (mytimeout * 1000);
			usleep(timetowait);
		}
		GO.update();
		data = GO.JOY_Y.isAxisPressed();
		if (data == DPAD_V_FULL) {
			if (oldkey == 't') {
				bright += 40;
				if (bright > 255)
					bright = 255;
				GO.lcd.setBrightness(bright);
				holdkey = 0;
				usleep(500000);
				continue;
			}
			key = 'u';
			continue;
		}
		if (data == DPAD_V_HALF) {
			if (oldkey == 't') {
				bright -= 40;
				if (bright < 0)
					bright = 0;
				GO.lcd.setBrightness(bright);
				holdkey = 0;
				usleep(500000);
				continue;
			}
			key = 'd';
			continue;
		}
		data = GO.JOY_X.isAxisPressed();
		if (data == DPAD_V_FULL) {
			key = 'l';
			continue;
		}
		if (data == DPAD_V_HALF) {
			key = 'r';
			continue;
		}

		data = GO.BtnA.isPressed();
		if (data) {
			key = 'a';
			continue;
		}

		data = GO.BtnB.isPressed();
		if (data) {
			key = 'b';
			continue;
		}

		data = GO.BtnSelect.isPressed();
		if (data) {
			key = 's';
			continue;
		}

		data = GO.BtnVolume.isPressed();
		if (data) {
			key = 'v';
			continue;
		}

		data = GO.BtnMenu.isPressed();
		if (data) {
			key = 'm';
			continue;
		}

		data = GO.BtnStart.isPressed();
		if (data) {
			key = 't';
			usleep(500000);
			continue;
		}

		holdkey = 1;

		if (mytimeout < 0 && key && !keypressed && !GO.JOY_X.isAxisPressed() &&
		    !GO.BtnA.isPressed() && !GO.BtnB.isPressed() &&
		    !GO.BtnStart.isPressed() && !GO.BtnSelect.isPressed() &&
		    !GO.JOY_Y.isAxisPressed())
			keypressed = true;
	}

	return key;
}

void
timeout(int n)
{
	mytimeout = n;
}
	
