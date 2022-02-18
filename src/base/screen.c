#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <curses.h>

#include "./../header/save_io.h"
#include "./../header/gdata.h"
#include "./../header/record_io.h"
#include "./../header/joystick.h"
#include "./../header/wires.h"
#include "./../header/gdata.h"
#include "./../header/action.h"
#include "./../header/screen.h"
#include "./../header/defz.h"

struct readers {
	int * rec;
	int * sav;
};

struct game_vars {
	int loop;
	int game;
	int empty;
	int game_o;
	int pos_x;
	int pos_y;
};

char* splash_ascii[] = {"______ _   _ _____ _____ _________________ _   __   __ |",
						"| ___ | | | |_   _|_   _|  ___| ___ |  ___| |  \\ \\ / / |",
						"| |_/ | | | | | |   | | | |__ | |_/ | |_  | |   \\ V /  |",
						"| ___ | | | | | |   | | |  __||    /|  _| | |    \\ /   |",
						"| |_/ | |_| | | |   | | | |___| |\\ \\| |   | |____| |   |",
						"\\____/ \\___/  \\_/   \\_/ \\____/\\_| \\_\\_|   \\_____/\\_/   |",
						"-------------------------------------------------------|"
};

void board_header(int x, int y) {
	move(HDR_ROW_STATS, 0);
	printw("Butterfly v%s | KILLS:     | DEATHS:     | SPARES:   ", VERSION);
	move(HDR_ROW_PLAYER, 0);
	printw("PLAYR:        | HP:    | STR:    ");
	move(HDR_ROW_ENEMY, 0);
	printw("ENEMY:        | HP:    | STR:    ");
	move(y, x);
}

void board_header_update(int x, int y, int m) {
	struct readers rd;
	rd.rec = record_reader();
	rd.sav = save_reader();
	switch (m) {
		case 0:
			move(HDR_ROW_STATS, HDR_KILL);
			printw("%d", rd.rec[0]);
			if (rd.rec[0] < 10) {
				move(HDR_ROW_STATS, HDR_KILL+1);
				printw(" ");
			}
			break;
		case 1:
			move(HDR_ROW_STATS, HDR_DEATH);
			printw("%d", rd.rec[1]);
			if (rd.rec[1] < 10) {
				move(HDR_ROW_STATS, HDR_DEATH+1);
				printw(" ");
			}
			break;
		case 2:
			move(HDR_ROW_STATS, HDR_SPARE);
			printw("%d", rd.rec[2]);
			if (rd.rec[2] < 10) {
				move(HDR_ROW_STATS, HDR_SPARE+1);
				printw(" ");
			}
			break;
		case 3:
			move(HDR_ROW_PLAYER, HDR_RACE);
			printw("%s", player_race_display(0));
			break;
		case 4:
			move(HDR_ROW_PLAYER, HDR_HP);
			printw("%d", rd.sav[1]);
			if (rd.sav[1] < 10) {
				move(HDR_ROW_PLAYER, HDR_HP+1);
				printw(" ");
			}
			break;
		case 5:
			move(HDR_ROW_PLAYER, HDR_STR);
			printw("%d", rd.sav[2]);
			if (rd.sav[2] < 10) {
				move(HDR_ROW_PLAYER, HDR_STR+1);
				printw(" ");
			}
			break;
		case 6:
			move(HDR_ROW_ENEMY, HDR_RACE);
			printw("%s", enemy_race_display(0));
			break;
		case 7:
			move(HDR_ROW_ENEMY, HDR_HP);
			printw("%d", rd.sav[4]);
			if (rd.sav[4] < 10) {
				move(HDR_ROW_ENEMY, HDR_HP+1);
				printw(" ");
			}
			break;
		case 8:
			move(HDR_ROW_ENEMY, HDR_STR);
			printw("%d", rd.sav[5]);
			if (rd.sav[5] < 10) {
				move(HDR_ROW_ENEMY, HDR_STR+1); 
				printw(" ");
			}
			break;
		case 9:
			move(HDR_ITM_POTION, 1);
			printw("%d", rd.sav[7]);
			break;
		case 10:
			move(HDR_ITM_SPEAR, 1);
			printw("%d", rd.sav[8]);
			break;
		case 11:
			move(HDR_ITM_POISON, 1);
			printw("%d", rd.sav[9]);
			break;
	}
	move(y, x);
	refresh();
}

int entity_alive(int kind) {
	struct readers rd;
	rd.sav = save_reader();
	if (kind == 0) {
		if (rd.sav[1] > 0) {
			return 0;
		} else if (rd.sav[1] <= 0) {
			return 1;
			}
	} else if (kind == 1) {
		if (rd.sav[4] > 0) { 
			return 0; 
		} else if (rd.sav[4] <= 0) { 
			return 1;
		}
	}
	return 2;
}

void scr_newgame(int x, int y) {
	struct game_vars gv;
	for (int i = 6; i < 11; i++) { // destroy anything below header
		move(i, 0);
		printw("\n");
	}
	refresh();
	gv.loop = 0;
	move(BRD_SPAWN_OPTS, 0);
	printw("Play again?");
	move(NG_YES, 0);
	printw(TBOARD_YES);
	move(NG_NO, 0);
	printw(TBOARD_NO);
	gv.pos_y = NG_YES;
	gv.pos_x = 6;
	while (gv.loop == 0) {
		move(gv.pos_y, gv.pos_x);
		printw("<");
		refresh();
		switch (getch()) {
			case 'q':
			case CTRL('q'):
			case CTRL('c'):
				screen_down();
				exit(0);
				break;
			case KEY_DOWN:
			case 's':
			case 'k':
				mvdelch(gv.pos_y, gv.pos_x);
				if (gv.pos_y == NG_NO) {
					gv.pos_y = NG_YES;
				} else {
					gv.pos_y += 1;
				}
				break;
			case KEY_UP:
			case 'w':
			case 'i':
				mvdelch(gv.pos_y, gv.pos_x);
				if (gv.pos_y == NG_YES) {
					gv.pos_y = NG_NO;
				} else {
					gv.pos_y -= 1;
				}
				break;
			case '\n':
				mvdelch(gv.pos_y, gv.pos_x);
				gv.loop = 1;
				break;
			default:
				break;
		}
	}
	if (gv.pos_y == 9) {
		stats_deploy();
		scr_board();
	} else if (gv.pos_y == 10) {
		screen_down();
		exit(0);
	}
}

void scr_poison(int x, int y) {
	struct readers rd;
	rd.sav = save_reader();
	if (rd.sav[10] >= 1 && rd.sav[10] <= 4 && rd.sav[1] > 0 && rd.sav[4] > 0) {
		// potion is active and below 4, player/enemy alive
		move(12, 0);
		if (rd.sav[10] == 4) {
			save_writer(10, 0); // set poison effects back to 0 (disabled)
			printw("The %s shakes off the poison.", enemy_race_display(1));
			refresh();
			scr_sleep(750);
		} else {
			int dam = (rand()%4)+1;
			save_writer(10, rd.sav[10]+1); // increment
			save_writer(4, rd.sav[4]-dam); // damage
			board_header_update(0, 12, 7);
			printw("The %s lost %dHP from the poison!", enemy_race_display(1), dam);
			refresh();
			scr_sleep(750);
		}
	}
	move(ITM_SPAWN_OPTS, 0);
	printw("\n");
	refresh();
	move(y, x);
}

void scr_result(int x, int y) {
	if (entity_alive(0) == 0 && entity_alive(1) == 1) {
		record_writer(0);
		board_header_update(x, y, 0);
		for (int i = 7; i < 11; i++) {
			move(i, 0);
			printw("\n");
		}
		move(7, 0);
		printw("You win!");
		refresh();
		scr_sleep(750);
		move(y, 0);
		scr_newgame(x, y);
	}
	if (entity_alive(0) == 1 && entity_alive(1) == 0) {
		record_writer(1);
		board_header_update(x, y, 0);
		for (int i = 7; i < 11; i++) {
			move(i, 0);
			printw("\n");
		}
		move(y, 0);
		printw("You died!");
		refresh();
		scr_sleep(750);
		move(y, 0);
		scr_newgame(x, y);
	}
}

void scr_board() {
	struct game_vars gv;
	struct readers rd;
	gv.pos_x = 0;
	gv.pos_y = 0;
	gv.game = 0;
	gv.game_o = 0;
	rd.sav = save_reader();
	int sel_int[4] = {BRD_FIGHT, BRD_ITEMS, BRD_SPARE, BRD_EXIT};
	char* sel_txt[4] = {TBOARD_FIGHT, TBOARD_ITEMS, TBOARD_SPARE, TBOARD_EXIT_IG};
	clear();
	board_header(gv.pos_x, gv.pos_y);
	for (int i = 0; i < 9; i++) {
		board_header_update(gv.pos_x, gv.pos_y, i);
	}
	for (int i = 0; i < 4; i++) {
		move(sel_int[i], gv.pos_x);
		printw("%s", sel_txt[i]);
	}
	refresh();
	gv.pos_y = BRD_FIGHT;
	gv.pos_x = 8;
	while (gv.game_o == 0) { // begin main loop
		scr_result(gv.pos_x, gv.pos_y); // did somebody win?
		while (gv.game == 0) { // begin play loop
			move(gv.pos_y, gv.pos_x);
			printw("<");
			refresh();
			switch (getch()) {
				case 'q':
				case CTRL('q'):
				case CTRL('c'):
					screen_down();
					exit(0);
					break;
				case KEY_DOWN:
				case 's':
				case 'k':
					mvdelch(gv.pos_y, gv.pos_x);
					if (gv.pos_y == BRD_EXIT) {
						gv.pos_y = BRD_FIGHT;
					} else {
						gv.pos_y += 1;
					}
					break;
				case KEY_UP:
				case 'w':
				case 'i':
					mvdelch(gv.pos_y, gv.pos_x);
					if (gv.pos_y == BRD_FIGHT) {
						gv.pos_y = BRD_EXIT;
					} else {
						gv.pos_y -= 1;
					}
					break;
				case '\n':
					gv.game = 1; // newline causes game loop break
					break;
				default:
					break;
			}
		}
		if (gv.game == 1) {
			switch (gv.pos_y) {
				case 7:
					attack(0, 12, 0);
					rd.sav = save_reader();
					if (rd.sav[1] > 0 && rd.sav[4] > 0) {
						attack(0, 13, 1);
					}
					move(gv.pos_y+5, 0); // clear popup
					printw("\n");
					move(gv.pos_y+6, 0);
					printw("\n");
					move(gv.pos_y, gv.pos_x);
					refresh();
					scr_poison(gv.pos_x, gv.pos_y);  // check if poison loop is active
					gv.game = 0; // re-enter main loop
					break;
				case 8:
					if (items(gv.pos_x, gv.pos_y) == 0) {
						rd.sav = save_reader();
						if (rd.sav[4] > 0) {
							attack(0, 12, 1);
						}
					}
					move(12, 0);
					printw("\n");
					move(gv.pos_y, gv.pos_x);
					scr_poison(gv.pos_x, gv.pos_y);
					refresh();
					gv.game = 0;
					break;
				case 9:
					if (spare(gv.pos_y, gv.pos_x) == 1) {
						attack(0, 12, 1);
						move(12, 0);
						printw("\n");
					} else {
						move(12, 0);
						printw("\n");
						move(gv.pos_y, gv.pos_x);
						refresh();
						scr_newgame(gv.pos_x, gv.pos_y);
					}
					refresh();
					gv.game = 0;
					break;
				case 10:
					scr_landing();
					break;
			}
		}
	}
}

void landing_credits() {
	char* catboy_contribs[5] = {"ARMv8 experimentation", "Quality assurance", "Battle design", "Game naming", "Playtest"};
	char* draumaz_contribs[3] = {"Developed by draumaz", " in C!", " (with the lovely curses library)"};
	int b[3] = {500, 500, 100};
	int c[3] = {35, 20, 10};
	int pos = HDR_SPAWN;
	clear();
	move(1, 0);
	scr_popwrite("Butterfly", 30); printw(",");
	refresh();
	scr_sleep(500);
	printw(" v");
	scr_popwrite(VERSION, 15);
	scr_sleep(500);
	pos += 2;
	move(pos, 0);
	for (int i = 0 ; i < 3; i++) {
		scr_popwrite(draumaz_contribs[i], c[i]);
		scr_sleep(b[i]);
	}
	scr_sleep(1000);
	pos += 2;
	move(pos, 0);
	scr_popwrite("Contributors:",35);
	scr_sleep(500);
	pos += 2;
	move(pos, 0);
	printw("catboy6969!");
	pos += 2;
	move(pos, 0);
	for (int i = 0; i < 5; i++) {
		scr_popwrite(catboy_contribs[i], 25);
		pos += 1;
		move(pos, 0);
		refresh();
	}
	scr_sleep(1000);
}

void landing_reset() {
	struct game_vars gv;
	struct readers rd;
	gv.pos_x = 0;
	gv.pos_y = 13;
	gv.empty = 0;
	gv.game = 0;
	rd.sav = save_reader();
	rd.rec = record_reader();
	move(gv.pos_y, gv.pos_x);
	for (int i = 0; i < 12; i++) {
		if (i < 3) {
			if (rd.rec[i] == 0) {
					gv.empty += 1;
			}
		}
		if (rd.sav[i] == 0) {
			gv.empty += 1;
		}
	}
	if (gv.empty == 15) {
		printw("No need to reset, your files are already blank.");
		refresh();
		scr_sleep(500);
		for (int i = 0; i < 7; i++) {
			move(gv.pos_y-(i-6),0);
			printw("\n");
		}
		return;
	}
	printw("Just to verify, you want to reset all your files?");
	move(RT_YES, 0);
	printw(TBOARD_YES);
	move(RT_NO, 0);
	printw(TBOARD_NO);
	gv.pos_y = RT_YES;
	gv.pos_x = 6;
	while (gv.game == 0) {
		move(gv.pos_y, gv.pos_x);
		printw("<");
		refresh();
		switch (getch()) {
			case 'q':
			case CTRL('q'):
			case CTRL('c'):
				screen_down();
				exit(0);
				return;
			case KEY_UP:
			case 'w':
			case 'i':
				mvdelch(gv.pos_y, gv.pos_x);
				if (gv.pos_y == RT_NO) {
					gv.pos_y -= 1;
				} else {
					gv.pos_y += 1;
				}
				break;
			case KEY_DOWN:
			case 's':
			case 'k':
				mvdelch(gv.pos_y, gv.pos_x);
				if (gv.pos_y == RT_YES) {
					gv.pos_y += 1;
				} else {
					gv.pos_y -= 1;
				}
				break;
			case '\n':
				gv.game = 1;
				break;
			default:
				break;
		}
	}
	switch (gv.pos_y) {
		case 15:
			move(18, 0);
			if (remove("data.txt") != 0 || remove("record.txt") != 0) {
				printw("Unable to delete.");
			} else {
				printw("Successfully deleted.");
			}
			refresh();
			scr_sleep(200);
			break;
		case 16:
			break;
	}
	for (int i = 0; i < 10; i++) {
		move(gv.pos_y-(i-6),0);
		printw("\n");
	}
	refresh();
}

void scr_landing() {
	struct game_vars gv;
	gv.pos_x = 0;
	gv.pos_y = 0;
	save_exists();
	record_exists();
	clear();
	int sel_int[4] = {LND_PLAY, LND_RESET, LND_CREDITS, LND_EXIT};
	char* sel_txt[4] = {TBOARD_PLAY, TBOARD_RESET, TBOARD_CREDITS, TBOARD_EXIT_SP};
	move(gv.pos_y, gv.pos_x);
	for (int i = 0; i < 7; i++) {
		printw("%s\n", splash_ascii[i]);
		gv.pos_y += 1;
		move(gv.pos_y, gv.pos_x);
	}
	refresh();
	for (int i = 0; i < 4; i++) {
		move(sel_int[i], gv.pos_x);
		printw("%s", sel_txt[i]);
	}
	gv.pos_y = LND_PLAY;
	gv.pos_x = 10;
	gv.game_o = 0;
	while (gv.game_o == 0) {
		gv.game = 0;
		save_exists();
		record_exists();
		while (gv.game == 0) {
			move(gv.pos_y, gv.pos_x);
			printw("<");
			refresh();
			switch (getch()) {
				case 'q':
				case CTRL('q'):
				case CTRL('c'):
					screen_down();
					exit(0);
					return;
				case KEY_UP:
				case 'w':
				case 'i':
					mvdelch(gv.pos_y, gv.pos_x);
					if (gv.pos_y == LND_PLAY) {
						gv.pos_y = LND_EXIT;
					} else {
						gv.pos_y -= 1;
					}
					break;
				case KEY_DOWN:
				case 's':
				case 'k':
					mvdelch(gv.pos_y, gv.pos_x);
					if (gv.pos_y == LND_EXIT) {
						gv.pos_y = LND_PLAY;
					} else {
						gv.pos_y += 1;
					}
					break;
				case '\n':
					gv.game = 1;
					break;
				default:
					break;
			}
		}
		switch (gv.pos_y) {
			case 8:
				gv.game_o = 1;
				break;
			case 9:
				landing_reset();
				break;
			case 10:
				landing_credits();
				scr_landing();
				break;
			case 11:
				screen_down();
				exit(0);
				break;
		}
		refresh();
	}
	int * sav = save_reader();
	if (gv.game_o == 1) {
	for (int i = 0; i < 5; i++) {
		if (sav[i] == 0) {
			stats_deploy();
			break;
		}
	}
	scr_board();
	}
}
