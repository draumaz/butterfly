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

#ifndef CTRL
#define CTRL(c) ((c) & 037)
#endif

#define NG_YES 9
#define NG_NO 10

#define RT_YES 15
#define RT_NO 16

#define BRD_FIGHT 7
#define BRD_ITEMS 8
#define BRD_SPARE 9
#define BRD_EXIT 10

#define LND_PLAY 8
#define LND_RESET 9
#define LND_CREDITS 10
#define LND_EXIT 11

#define HDR_KILL 25
#define HDR_DEATH 39
#define HDR_SPARE 53
#define HDR_RACE 7
#define HDR_HP 20
#define HDR_STR 30
#define HDR_ITM_POTION 12
#define HDR_ITM_SPEAR 13
#define HDR_ITM_POISON 14

char* splash_ascii[] = {"______ _   _ _____ _____ _________________ _   __   __ |",
	                    "| ___ | | | |_   _|_   _|  ___| ___ |  ___| |  \\ \\ / / |",
                        "| |_/ | | | | | |   | | | |__ | |_/ | |_  | |   \\ V /  |",
                        "| ___ | | | | | |   | | |  __||    /|  _| | |    \\ /   |",
                        "| |_/ | |_| | | |   | | | |___| |\\ \\| |   | |____| |   |",
                        "\\____/ \\___/  \\_/   \\_/ \\____/\\_| \\_\\_|   \\_____/\\_/   |",
                        "-------------------------------------------------------|"
};

void board_header(int x, int y) {
    move(1, 0);
    printw("Butterfly v%s | KILLS:     | DEATHS:     | SPARES:   ", version());
    move(3, 0);
    printw("PLAYR:        | HP:    | STR:    ");
    move(5, 0);
    printw("ENEMY:        | HP:    | STR:    ");
    move(y, x);
}

void board_header_update(int x, int y, int m) {
    int * rec = record_reader();
    int * sav = save_reader();
    switch (m) {
        case 0:
            move(1, HDR_KILL);
            printw("%d", rec[0]);
            if (rec[0] < 10) {
                move(1, HDR_KILL+1);
                printw(" ");
            }
            break;
        case 1:
            move(1, HDR_DEATH);
            printw("%d", rec[1]);
            if (rec[1] < 10) {
                move(1, HDR_DEATH+1);
                printw(" ");
            }
            break;
        case 2:
            move(1, HDR_SPARE);
            printw("%d", rec[2]);
            if (rec[2] < 10) {
                move(1, HDR_SPARE+1);
                printw(" ");
            }
            break;
        case 3:
            move(3, HDR_RACE);
            printw("%s", race_display(sav[0],0,0));
            break;
        case 4:
            move(3, HDR_HP);
            printw("%d", sav[1]);
            if (sav[1] < 10) {
                move(3, HDR_HP+1);
                printw(" ");
            }
            break;
        case 5:
            move(3, HDR_STR);
            printw("%d", sav[2]);
            if (sav[2] < 10) {
                move(3, HDR_STR+1);
                printw(" ");
            }
            break;
        case 6:
            move(5, HDR_RACE);
            printw("%s", race_display(sav[3],1,0));
            break;
        case 7:
            move(5, HDR_HP);
            printw("%d", sav[4]);
            if (sav[4] < 10) {
                move(5, HDR_HP+1);
                printw(" ");
            }
            break;
        case 8:
            move(5, HDR_STR);
            printw("%d", sav[5]);
            if (sav[5] < 10) {
                move(5, HDR_STR+1); 
                printw(" ");
            }
            break;
        case 9:
            move(HDR_ITM_POTION, 1);
            printw("%d", sav[7]);
            break;
        case 10:
            move(HDR_ITM_SPEAR, 1);
            printw("%d", sav[8]);
            break;
        case 11:
            move(HDR_ITM_POISON, 1);
            printw("%d", sav[9]);
            break;
    }
    move(y, x);
    refresh();
}

int entity_alive(int kind) {
	int * sav = save_reader();
	if (kind == 0) {
		if (sav[1] > 0) {
            return 0;
        } else if (sav[1] <= 0) {
            return 1;
        }
	} else if (kind == 1) {
		if (sav[4] > 0) { 
            return 0; 
        } else if (sav[4] <= 0) { 
            return 1;
        }
	}
	return 2;
}

void scr_newgame(int x, int y) {
    for (int i = 6; i < 11; i++) { // destroy anything below header
        move(i, 0); printw("\n");
    }
    refresh();
    int pos_y = 7;
    int pos_x = 6;
    move(pos_y, 0);
    printw("Play again?");
    pos_y += 2; move(pos_y, 0); // 9
    printw("[YES]");
    pos_y += 1; move(pos_y, 0); // 10
    printw("[NO ]");
	int loop = 0;
    pos_y = 9; // position at YES
	while (loop == 0) {
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
			case KEY_DOWN:
            case 's':
			case 'k':
				mvdelch(pos_y, pos_x);
				if (pos_y == 10) {
					pos_y = 9;
				} else {
                    pos_y += 1;
                }
                break;
			case KEY_UP:
            case 'w':
			case 'i':
				mvdelch(pos_y, pos_x);
				if (pos_y == 9) {
					pos_y = 10;
				} else {
                    pos_y -= 1;
                }
                break;
            case '\n':
				mvdelch(pos_y, pos_x);
                loop = 1;
                break;
			default:
                break;
		}
	}
    if (pos_y == 9) {
        stats_deploy();
        scr_board();
    } else if (pos_y == 10) {
        screen_down();
        exit(0);
    }
}

void scr_poison(int x, int y) {
    int * sav = save_reader();
    if (sav[10] >= 1 && sav[10] <= 4) {
        move(12, 0);
        if (sav[10] == 4) {
			save_writer(10, 0); // set poison effects back to 0 (disabled)
			printw("The %s shakes off the poison.",race_display(sav[3],1,1));
            refresh();
            scr_sleep(750);
		} else {
			int dam = (rand()%4)+1;
			save_writer(10, sav[10]+1); // increment
			save_writer(4, sav[4]-dam); // damage
            board_header_update(0, 12, 7);
			printw("The %s lost %dHP from the poison!", race_display(sav[3],1,1), dam);
            refresh();
            scr_sleep(750);
		}
    } move(12,0); printw("\n"); refresh(); move(y, x);
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
    int pos_x = 0;
    int pos_y = 0;
    int game = 0;
    int game_o = 0;
    int sel_int[] = {BRD_FIGHT, BRD_ITEMS, BRD_SPARE, BRD_EXIT};
    char* sel_txt[] = {"[FIGHT  ]", "[ITEMS  ]", "[SPARE  ]", "[EXIT   ]"};
    clear();
    board_header(pos_x, pos_y);
    for (int i = 0; i < 9; i++) {
        board_header_update(pos_x, pos_y, i);
    }
    for (int i = 0; i < 4; i++) {
        move(sel_int[i], pos_x);
        printw("%s", sel_txt[i]);
    }
    refresh();
    pos_y = 7; // position at FIGHT
    pos_x = 10;
    while (game_o == 0) { // begin main loop
        scr_result(pos_x, pos_y); // did somebody win?
        while (game == 0) { // begin play loop
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
                case KEY_DOWN:
                case 's':
                case 'k':
                    mvdelch(pos_y, pos_x);
                    if (pos_y == 10) {
                        pos_y = 7;
                    } else {
                        pos_y += 1;
                    }
                    break;
                case KEY_UP:
                case 'w':
                case 'i':
                    mvdelch(pos_y, pos_x);
                    if (pos_y == 7) {
                        pos_y = 10;
                    } else {
                        pos_y -= 1;
                    }
                    break;
                case '\n':
                    game = 1; // newline causes game loop break
                    break;
                default:
                    break;
            }
        }
        if (game == 1) {
            switch (pos_y) {
                case 7:
                    attack(0, 12, 0);
                    int * sav = save_reader();
                    if (sav[1] > 0 && sav[4] > 0) {
                        attack(0, 13, 1);
                    }
                    move(pos_y+5, 0); // clear popup
                    printw("\n");
                    move(pos_y+6, 0);
                    printw("\n");
                    move(pos_y, pos_x);
                    refresh();
                    scr_poison(pos_x, pos_y);  // check if poison loop is active
                    game = 0; // re-enter main loop
                    break;
                case 8:
                    if (items(pos_x, pos_y) == 0) {
                        if (sav[4] > 0) {
                            attack(0, 12, 1);
                        }
                        move(12, 0); printw("\n");
                        move(pos_y, pos_x);
                        if (sav[4] > 0) {
                            scr_poison(pos_x, pos_y);
                        }
                    }
                    refresh();
                    game = 0;
                    break;
                case 9:
                    if (spare(pos_y, pos_x) == 1) {
                        attack(0, 12, 1);
                        move(12, 0);
                        printw("\n");
                    } else {
                        move(12, 0);
                        printw("\n");
                        move(pos_y, pos_x);
                        refresh();
                        scr_newgame(pos_x, pos_y);
                    }
                    refresh();
                    game = 0;
                    break;
                case 10:
                    scr_landing();
                    break;
            }
        }
    }
}

void landing_credits() {
	char* catboy_contribs[] = {"ARMv8 experimentation", "Quality assurance", "Battle design", "Playtest"};
	char* draumaz_contribs[] = {"Developed by draumaz", " in C!", " (with the lovely curses library)"};
    char* cano_contribs[] = {"Character design", "Inspiration"};
	int b[] = {500, 500, 100};
    int c[] = {35, 20, 10};
    int pos = 1;
	clear();
	move(1, 0);
	scr_popwrite("Butterfly", 30); printw(",");
    refresh();
    scr_sleep(500);
    printw(" v");
	scr_popwrite(version(), 15);
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
	scr_popwrite("Special thanks to:",35);
	scr_sleep(500);
	pos += 2;
    move(pos, 0);
	printw("catboy6969!");
	pos += 2;
    move(pos, 0);
	for (int i = 0; i < 4; i++) {
		scr_popwrite(catboy_contribs[i], 25);
		pos += 1;
        move(pos, 0);
        refresh();
	} 
    scr_sleep(500);
    pos+= 1;
    move(pos, 0);
	printw("Bryce Cano!");
    pos += 2;
    move(pos, 0);
    for (int i = 0; i < 2; i++) {
        scr_popwrite(cano_contribs[i], 25);
        pos +=1;
        move(pos, 0);
        refresh();
    }
	refresh();
	scr_sleep(1000);
}

void landing_reset() {
    int pos_x = 0;
    int pos_y = 13;
    int game = 0;
    move(pos_y, pos_x);
    printw("Just to verify, you want to reset your save and record files?");
    move(RT_YES, pos_x);
    printw("[YES]"); // 15
    move(RT_NO, pos_x);
    printw("[NO ]"); // 16
    pos_y = 15; // position at YES
    pos_x = 6;
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
                return;
            case KEY_UP:
            case 'w':
            case 'i':
                mvdelch(pos_y, pos_x);
                if (pos_y == 16) {
                    pos_y -= 1;
                } else {
                    pos_y += 1;
                }
                break;
            case KEY_DOWN:
            case 's':
			case 'k':
				mvdelch(pos_y, pos_x);
				if (pos_y == 15) {
					pos_y += 1;
				} else {
                    pos_y -= 1;
                }
                break;
            case '\n':
                game = 1;
                break;
			default:
                break;
        }
    }
    switch (pos_y) {
        case 15:
            move(18, 0);
            if (remove("data.txt") != 0 || remove("record.txt") != 0) {
                printw("Failed to delete temp files.");
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
        move(pos_y-(i-6),0);
        printw("\n");
    }
    refresh();
}

void scr_landing() {
    clear();
    int pos_x = 0;
    int pos_y = 0;
    save_exists(); record_exists();
    move(pos_y, pos_x);
    int sel_int[] = {LND_PLAY, LND_RESET, LND_CREDITS, LND_EXIT};
    char* sel_txt[] = {"[PLAY   ]", "[RESET  ]", "[CREDITS]", "[EXIT   ]"};
    for (int i = 0; i < 7; i++) {
        printw("%s\n",splash_ascii[i]);
        pos_y += 1;
        move(pos_y, pos_x);
    }
    refresh();
    for (int i = 0; i < 4; i++) {
        move(sel_int[i], pos_x);
        printw("%s", sel_txt[i]);
    }
    pos_y = 8; // position at PLAY
    pos_x = 10;
    int game_o = 0;
    while (game_o == 0) {
        int game = 0;
        save_exists();
        record_exists();
        while (game == 0) {
            move(pos_y, pos_x); printw("<");
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
                    mvdelch(pos_y, pos_x);
                    if (pos_y > 8) {
                        pos_y -= 1;
                    } else if (pos_y == 8) {
                        pos_y = 11;
                    }
                    break;
                case KEY_DOWN:
                case 's':
                case 'k':
                    mvdelch(pos_y, pos_x);
                    if (pos_y < 11) {
                        pos_y += 1;
                    } else if (pos_y == 11) {
                        pos_y = 8;
                    }
                    break;
                case '\n':
                    game = 1;
                    break;
                default:
                    break;
            }
        } switch (pos_y) {
                case 8:
                    game_o = 1;
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
    if (game_o == 1) {
        for (int i = 0; i < 5; i++) {
            if (sav[i] == 0) {
                stats_deploy();
            }
        }
        scr_board();
    }
}
