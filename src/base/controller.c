#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>

#include "./../header/screen.h"

void joystick() {
	initscr(); noecho(); raw(); curs_set(0);
	splash2(10, 8);
	clear(); curs_set(1);
	#ifdef _WIN32
		system("pause");
	#else
       	system("stty sane");
	#endif
	endwin();
}
