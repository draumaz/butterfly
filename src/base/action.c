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
#include "./../header/joystick.h"
#include "./../header/selections.h"

int items(int x, int y) {
    int pos_x = 0; 
    int pos_y = 12; 
    int game = 0;
    int item_used = 2;
    int * sav = save_reader();
    move(ITM_POTION, pos_x);
    printw("[%dx POTION]", sav[7]);
    move(ITM_SPEAR, pos_x);
    printw("[%dx SPEAR ]", sav[8]);
    move(ITM_POISON, pos_x);
    printw("[%dx POISON]", sav[9]);
    move(ITM_BACK, pos_x);
    printw("[BACK     ]");
    if (sav[6] == 0 || sav[6] == 15) {
        pos_y = ITM_POTION;
    } else {
        pos_y = sav[6]; // position at last saved
    }
    pos_x = 12;
    while (game == 0) {
        move(pos_y, pos_x);
        printw("<");
        refresh();
        switch (getch()) {
            case 'q':
            case CTRL('q'):
            case CTRL('c'):
                screen_down();
                exit(0);
                break;
            case KEY_UP:
            case 'w':
            case 'i':
                mvdelch(pos_y, pos_x);
                if (pos_y == ITM_POTION) {
                    pos_y = ITM_BACK;
                } else {
                    pos_y -= 1;
                }
                break;
            case KEY_DOWN:
            case 's':
			case 'k':
				mvdelch(pos_y, pos_x);
				if (pos_y == ITM_BACK) {
					pos_y = ITM_POTION;
				} else { 
                    pos_y += 1; 
                }
                break;
            case '\n':
                game = 1;
                break;
			default:
                break;
        }
    }
    if (pos_y != sav[6]) {
        save_writer(6, pos_y);
    }
    switch (pos_y) {
        case 12:
            if (sav[7] > 0) {
                item_used = 0;
                save_writer(7, sav[7]-1);
                save_writer(1, sav[1]+10);
            }
            board_header_update(pos_x, pos_y, 9);
            board_header_update(pos_x, pos_y, 4);
            move(17, 0);
            refresh();
            if (item_used == 0) {
                printw("You drink the potion, recovering 10HP!");
            } else { 
                printw("You don't have any potions left.");
            }
            refresh();
            scr_sleep(750);
            break;
        case 13:
            if (sav[8] > 0) {
                item_used = 0;
                save_writer(8, sav[8]-1);
                save_writer(4, sav[4]-9);
            }
            board_header_update(pos_x, pos_y, 10);
            board_header_update(pos_x, pos_y, 7);
            move(17, 0); refresh();
            if (item_used == 0) {
                printw("You throw the spear, dealing 9HP!");
            } else {
                item_used = 1;
                printw("You don't have any spears left.");
            }
            refresh();
            scr_sleep(750);
            break;
        case 14:
            if (sav[9] > 0) {
                item_used = 0;
                save_writer(9, sav[9]-1); // poison throw
                save_writer(10, 1); // activate poison loop
            }
            board_header_update(pos_x, pos_y, 11);
            move(17, 0);
            refresh();
            if (item_used == 0) {
                printw("You throw the poison! The %s feels the pain...", enemy_race_display(1));
            } else {
                item_used = 1;
                printw("You don't have any poison left.");
            }
            refresh();
            scr_sleep(750);
            break;
        case 15:
            item_used = 1;
            break;
    }
    move(y, x);
    refresh();
    for (int i = 0; i < 6; i++) {
        move(i+12,0);
        printw("\n");
    }
    return item_used;
}

void attack(int x, int y, int way) {
    srand(time(0));
    int * sav = save_reader();
    float ran = ((float)rand())/(float)RAND_MAX;
    move(y, x);
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
                enemy_race_display(1), dam_to_enemy);
            }
            break; }
        case 1: { // to player
            int dam_to_player = round(sav[5]/(ran*(4.1-3.2)+3.2)); // should probably be fixed lol
            save_writer(1, sav[1]-dam_to_player);
            board_header_update(x, y, 4);
            if (sav[1] <= 0) {
                printw("The %s deals the death blow, attacking with %dHP!\n",
                enemy_race_display(1), dam_to_player);
            } else {
                printw("The %s attacks you, dealing %dHP!\n",
                enemy_race_display(1), dam_to_player);
            }
            break; }
    } refresh(); scr_sleep(750);
}

int spare(int x, int y) {
    int result;
    int * sav = save_reader();
    y += 2;
    move(y, 0);
    printw("You attempt to spare the %s", enemy_race_display(1));
    refresh();
    for (int i = 0; i < 3; i++) {
        printw(".");
        refresh();
        scr_sleep(500);
    } scr_sleep(750);
    y += 2;
    move(y, 0);
    if (sav[1] <= sav[4]){
        printw("It didn't work.");
        result = 1;
    } else {
        record_writer(2);
        board_header_update(0, y, 2);
        printw("It worked!");
        result = 0;
    }
    refresh();
    scr_sleep(1000);
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
