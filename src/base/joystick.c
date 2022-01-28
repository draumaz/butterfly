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
    keypad(stdscr, false);
    endwin();
    curs_set(1);
    #ifdef _WIN32
        system("pause");
    #else
        system("stty sane");
    #endif
}

void joystick() {
    screen_up();
    scr_landing();
    screen_down();
}