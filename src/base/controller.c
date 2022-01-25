#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>

#include "./../header/screen.h"

void joystick() {
	initscr(); noecho(); raw(); curs_set(0); keypad(stdscr, true);
	splash_screen(10, 8);
	clear(); curs_set(1); endwin(); keypad(stdscr, false);
	#ifdef _WIN32
		system("pause");
	#else
       	system("stty sane");
	#endif
}
