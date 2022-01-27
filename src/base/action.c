#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <curses.h>

#include "./../header/save_io.h"
#include "./../header/record_io.h"
#include "./../header/gdata.h"
#include "./../header/wires.h"
#include "./../header/screen.h"

#ifndef CTRL
#define CTRL(c) ((c) & 037)
#endif

int spare(int x, int y) {
    int result = 1;
    int * sav = save_reader();
    y += 2; move(y, 0);
    printw("You attempt to spare the %s", race_display(sav[3],1,1));
    refresh();
    for (int i = 0; i < 3; i++) {
        printw(".");
        refresh();
        scr_sleep(500);
    } scr_sleep(750);
    if (sav[1] >= sav[4]) {
        record_writer(2);
        printw("\n\nIt worked!");
        result = 0;
    } else if (sav[1] <= sav[4]) {
        printw("\n\nIt didn't work.");
        result = 1;
    } refresh(); scr_sleep(1000); 
    move(y, 0);
    printw("\n");
    move(y+1, 0);
    printw("\n");
    move(y+2, 0);
    printw("\n");
    move(y+3, x);
    refresh();
    return result;
}