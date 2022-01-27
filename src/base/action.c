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

void attack(int x, int y, int way) {
    move(y, x);
    int * sav = save_reader();
    srand(time(0));
    float ran = ((float)rand())/(float)RAND_MAX;
    switch (way) {
        case 0: { // to enemy
            int dam_to_enemy = round(sav[2]/(ran*(4.1-3.2)+3.2)); // math is kinda weird
            save_writer(4, sav[4]-dam_to_enemy);
            board_header_update(x, y, 7);
            if (sav[4] <= 0) {
                printw("You deal the death blow, attacking with %dHP!\n"
                ,dam_to_enemy);
            } else {
                printw("You attack the %s, dealing %dHP!\n",
                race_display(sav[3],1,1),dam_to_enemy);
            }
            break; }
        case 1: { // to player
            int dam_to_player = round(sav[5]/(ran*(4.1-3.2)+3.2)); // should probably be fixed lol
            save_writer(1, sav[1]-dam_to_player);
            board_header_update(x, y, 4);
            if (sav[1] <= 0) {
                printw("The %s deals the death blow, attacking with %dHP!\n",
                race_display(sav[3],1,1),dam_to_player);
            } else {
                printw("The %s attacks you, dealing %dHP!\n",
                race_display(sav[3],1,1),dam_to_player);
            }
            break; }
    } refresh(); scr_sleep(750);
}

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