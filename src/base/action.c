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

struct readers {
	int * sav;
	int * rec;
};

struct action_vars {
	int game;
	int pos_x;
	int pos_y;
	int item_used;
	int dam_to_enemy;
	int dam_to_player;
	float ran;
};

int items(int x, int y) {
	struct action_vars av;
	struct readers rd;
	av.pos_x = 0; 
	av.pos_y = 12; 
	av.game = 0;
	av.item_used = 2;
	rd.sav = save_reader();
	move(ITM_POTION, av.pos_x);
	printw("[%dx POTION]", rd.sav[7]);
	move(ITM_SPEAR, av.pos_x);
	printw("[%dx SPEAR ]", rd.sav[8]);
	move(ITM_POISON, av.pos_x);
	printw("[%dx POISON]", rd.sav[9]);
	move(ITM_BACK, av.pos_x);
	printw("[BACK     ]");
	if (rd.sav[6] == 0 || rd.sav[6] == 15) {
		av.pos_y = ITM_POTION;
	} else {
		av.pos_y = rd.sav[6]; // position at last saved
	}
	av.pos_x = 12;
	while (av.game == 0) {
		move(av.pos_y, av.pos_x);
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
				mvdelch(av.pos_y, av.pos_x);
				if (av.pos_y == ITM_POTION) {
					av.pos_y = ITM_BACK;
				} else {
					av.pos_y -= 1;
				}
				break;
			case KEY_DOWN:
			case 's':
			case 'k':
				mvdelch(av.pos_y, av.pos_x);
				if (av.pos_y == ITM_BACK) {
					av.pos_y = ITM_POTION;
				} else { 
				av.pos_y += 1; 
				}
				break;
			case '\n':
				av.game = 1;
				break;
			default:
				break;
		}
	}
	if (av.pos_y != rd.sav[6]) {
		save_writer(6, av.pos_y);
	}
	switch (av.pos_y) {
		case 12:
			if (rd.sav[7] > 0) {
				av.item_used = 0;
				save_writer(7, rd.sav[7]-1);
				save_writer(1, rd.sav[1]+10);
			}
			board_header_update(av.pos_x, av.pos_y, 9);
			board_header_update(av.pos_x, av.pos_y, 4);
			move(17, 0);
			refresh();
			if (av.item_used == 0) {
				printw("You drink the potion, recovering 10HP!");
			} else {
				av.item_used = 1;
				printw("You don't have any potions left.");
			}
			refresh();
			scr_sleep(750);
			break;
		case 13:
			if (rd.sav[8] > 0) {
				av.item_used = 0;
				save_writer(8, rd.sav[8]-1);
				save_writer(4, rd.sav[4]-9);
			}
			board_header_update(av.pos_x, av.pos_y, 10);
			board_header_update(av.pos_x, av.pos_y, 7);
			move(17, 0);
			refresh();
			if (av.item_used == 0) {
				printw("You throw the spear, dealing 9HP!");
			} else {
				av.item_used = 1;
				printw("You don't have any spears left.");
			}
			refresh();
			scr_sleep(750);
			break;
		case 14:
			if (rd.sav[9] > 0) {
				av.item_used = 0;
				save_writer(9, rd.sav[9]-1); // poison throw
				save_writer(10, 1); // activate poison loop
			}
			board_header_update(av.pos_x, av.pos_y, 11);
			move(17, 0);
			refresh();
			if (av.item_used == 0) {
				printw("You throw the poison! The %s feels the pain...", enemy_race_display(1));
			} else {
				av.item_used = 1;
				printw("You don't have any poison left.");
			}
			refresh();
			scr_sleep(750);
			break;
		case 15:
			av.item_used = 1;
			break;
	}
	move(y, x);
	refresh();
	for (int i = 0; i < 6; i++) {
		move(i+12,0);
		printw("\n");
	}
	return av.item_used;
}

void attack(int x, int y, int way) {
	struct action_vars av;
	struct readers rd;
	srand(time(0));
	rd.sav = save_reader();
	av.ran = ((float)rand())/(float)RAND_MAX;
	move(y, x);
	switch (way) {
		case 0: { // to enemy
			av.dam_to_enemy = round(rd.sav[2]/(av.ran*(4.1-3.2)+3.2)); // math is kinda weird
			save_writer(4, rd.sav[4]-av.dam_to_enemy);
			board_header_update(x, y, 7);
			if (rd.sav[4] <= 0) {
				printw("You deal the death blow, attacking with %dHP!\n", av.dam_to_enemy);
			} else {
				printw("You attack the %s, dealing %dHP!\n", enemy_race_display(1), av.dam_to_enemy);
			}
			break; }
		case 1: { // to player
			av.dam_to_player = round(rd.sav[5]/(av.ran*(4.1-3.2)+3.2)); // should probably be fixed lol
			save_writer(1, rd.sav[1]-av.dam_to_player);
			board_header_update(x, y, 4);
			if (rd.sav[1] <= 0) {
				printw("The %s deals the death blow, attacking with %dHP!\n", enemy_race_display(1), av.dam_to_player);
			} else {
				printw("The %s attacks you, dealing %dHP!\n", enemy_race_display(1), av.dam_to_player);
			}
			break; }
	} 
	refresh();
	scr_sleep(750);
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
	}
	scr_sleep(750);
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
