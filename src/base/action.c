#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <curses.h>

#include "./../header/save_io.h"
#include "./../header/record_io.h"
#include "./../header/gtool.h"
#include "./../header/stat_gen.h"
#include "./../header/screen.h"

int spare() {
    int result = 1;
    int * sav = save_reader();
    printw("\nYou attempt to spare the %s", race_display(sav[3],1,1));
    for (int i = 0; i < 3; i++) {
        printw(".");
        refresh();
        game_sleep(500);
    } game_sleep(750);
    if (sav[1] >= sav[4]) {
        record_writer(2);
        printw("\n\nIt worked!");
        result = 0;
    } else if (sav[1] <= sav[4]) {
        printw("\n\nIt didn't work.");
        result = 1;
    } refresh(); game_sleep(1000); return result;
}

int items() {
    int item_used = 1;
    int * sav = save_reader();
    int loop = 0;
    item_options_screen();
    int pos_x = 12; int pos_y = 12;
    while (loop == 0) {
        move(pos_y, pos_x); printw("<");
        refresh();
		switch (getch()) {
			case 'q':
                curs_set(1);
                clear();
				#ifdef _WIN32
					system("pause");
				#else
                	system("stty sane");
				#endif
				exit(0);
                break;
            case 's':
				mvdelch(pos_y, pos_x);
				if (pos_y == 15) {
					pos_y = 12;
				} else { pos_y += 1; }
                break;
            case 'w':
				mvdelch(pos_y, pos_x);
				if (pos_y == 12) {
					pos_y = 15;
				} else { pos_y -= 1; }
                break;
            case '\n':
                loop = 1;
                break;
			default:
                break;
		}
    }
    if (loop == 1) {
        switch (pos_y) {
            case 12:
                move(pos_y+5, 0);
                if (sav[7] > 0) { // use potion
                    item_used = 0;
                    save_writer(7, 0);
                    save_writer(1, (sav[1]+10));
                    printw("You drink the potion, recovering 10HP!");
                } else { // no potions
                    item_used = 1;
                    printw("\nYou don't have any potions left.");
                }
                refresh();
                game_sleep(1000);
                break;
            case 13:
                move(pos_y+4, 0);
                if (sav[8] > 0) { // use spear
                    item_used = 0;
                    save_writer(8, 0);
                    save_writer(4, (sav[4]-9));
                    printw("You throw the spear, dealing 9HP!");
                } else { // no spears
                    item_used = 1;
                    printw("You don't have any spears left.");
                }
                refresh();
                game_sleep(1000);
                break;
            case 14:
                if (sav[9] > 0) {
                    item_used = 0;
                    save_writer(9, 0); // poison thrown
                    save_writer(10, 1); // poison loop active
                    move(pos_y+2, 0);
                    printw("\nYou throw the poison! The %s feels the pain", 
                    race_display(sav[3],1,1));
                    refresh();
                    for (int i = 0; i < 3; i++) {
                        printw(".");
                        refresh();
                        game_sleep(300);
                    }
                } else {
                    item_used = 1;
                    puts("\nYou don't have any more poison.");
                    refresh();
                }
                break;
            case 15:
                break;
        }
    } return item_used;
}

void attack(int dir) {
    srand(time(0));
    float ran = ((float)rand())/(float)RAND_MAX;
    int * sav = save_reader();
    switch (dir) {
        case 0: { // attack enemy
            int dam_to_enemy = round(sav[2]/(ran*(4.1-3.2)+3.2)); // math is kinda weird
            save_writer(4, sav[4]-dam_to_enemy);
            //board_header_screen(0);
            if (sav[4] <= 0) {
                printw("You deal the death blow, attacking with %dHP!\n"
                ,dam_to_enemy);
            } else {
                printw("You attack the %s, dealing %dHP!\n",
                race_display(sav[3],1,1),dam_to_enemy);
            } break; }
        case 1: { // get attacked
            int dam_to_player = round(sav[5]/(ran*(4.1-3.2)+3.2)); // should probably be fixed lol
            save_writer(1, sav[1]-dam_to_player);
            //board_header_screen(0);
            if (sav[1] <= 0) {
                printw("The %s deals the death blow, attacking with %dHP!\n",
                race_display(sav[3],1,1),dam_to_player);
            } else {
                printw("The %s attacks you, dealing %dHP!\n",
                race_display(sav[3],1,1),dam_to_player);
            } break; }
    } refresh(); game_sleep(1000);
}
