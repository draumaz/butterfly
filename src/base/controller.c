#include <stdio.h>
#include <curses.h>
#include <unistd.h>

#include "./../header/screen.h"

void joystick() {
	initscr(); noecho(); raw();
	splash_screen();
	sleep(1);
	endwin();
}