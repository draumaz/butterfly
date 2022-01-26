#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>

#include "./../header/screen.h"

void screen_up() {
    initscr();
    noecho();
    curs_set(0);
    raw();
    keypad(stdscr, true);
}

void screen_down() {
    clear();
    curs_set(1);
    keypad(stdscr, false);
    endwin();
}

void joystick() {
    screen_up();
    scr_landing();
    screen_down();
}