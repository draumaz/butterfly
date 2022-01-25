#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>

#include "./../header/save_io.h"
#include "./../header/record_io.h"
#include "./../header/gtool.h"
#include "./../header/stat_gen.h"
#include "./../header/action.h"

#include "./../header/screen.h" // self-referential

#ifndef CTRL
#define CTRL(c) ((c) & 037)
#endif

const char* board_screen_prompt = "\n\n[FIGHT]\n[ITEMS]\n[SPARE]\n[EXIT ]\n\n";

const char* splash_ascii[] = {"______ _   _ _____ _____ _________________ _   __   __",
	"| ___ | | | |_   _|_   _|  ___| ___ |  ___| |  \\ \\ / /",
        "| |_/ | | | | | |   | | | |__ | |_/ | |_  | |   \\ V /  (.\\\\//.)",
        "| ___ | | | | | |   | | |  __||    /|  _| | |    \\ /    \\ () /",
        "| |_/ | |_| | | |   | | | |___| |\\ \\| |   | |____| |    (_/\\_)",
        "\\____/ \\___/  \\_/   \\_/ \\____/\\_| \\_\\_|   \\_____/\\_/  ",
        "------------------------------------------------------------------"
};

char in_prog_warn() {
	int * s = save_reader();
	int warn = 1;
	for (int i = 0; i < 6; i++) {
		if (s[i] != 0) {
			warn = 0;
			break;
		}
	} if (warn == 0) {
		printw("Game in progress.\n\nCONTINUE [1]\nRESET    [2]\nBACK     [3]\n\n");
		return (char)getch();
	} return 'a';
}

int board_again_screen() {
	int pos_y = 9; int pos_x = 6;
	printw("Play again?\n\n[YES]\n[NO ]\n\n");
	int loop = 0;
	while (loop == 0) {
		move(pos_y, pos_x); printw("<");
		refresh();
		int ipu; ipu = getch();
		switch (ipu) {
			case 'q':
			case CTRL('q'):
            case CTRL('c'):
                curs_set(1);
				clear();
				endwin();
				#ifdef _WIN32
					system("pause");
				#else
                	system("stty sane");
				#endif
				exit(0);
                break;
			case KEY_DOWN:
            case 's':
			case 'k':
				mvdelch(pos_y, pos_x);
				if (pos_y == 10) {
					pos_y = 9;
				} else { pos_y += 1; }
                break;
			case KEY_UP:
            case 'w':
			case 'i':
				mvdelch(pos_y, pos_x);
				if (pos_y == 9) {
					pos_y = 10;
				} else { pos_y -= 1; }
                break;
            case '\n':
				mvdelch(pos_y, pos_x);
                loop = 1;
                break;
			default:
                break;
		}
	}
	return pos_y;
}

void new_game_manager() {
	if (board_again_screen() == 9) {
		stats_deploy();
		board_screen(8, 7);
	} else { 
        splash_screen(10, 8);
    }
}

void board_header_screen(int fake_options) {
	int * rec = record_reader();
	int * sav = save_reader();
	printw("\nButterfly v%s | KILLS: %d | DEATHS: %d | SPARES: %d", version(), rec[0], rec[1], rec[2]);
	printw("\n\nRACE: %s | HP: %d | STR: %d", race_display(sav[0],0,0), sav[1], sav[2]);
	printw("\n\nENEMY RACE: %s | HP: %d | STR: %d", race_display(sav[3],1,0),sav[4],sav[5]);
	if (fake_options == 0) {
		printw("%s",board_screen_prompt);
	}
}

void item_options_screen() {
	int * sav = save_reader();
	printw("[%dx POTION]\n[%dx SPEAR ]\n[%dx POISON]\n[BACK     ]\n\n",sav[7],sav[8],sav[9]);
}

int entity_alive(int kind) {
	int * sav = save_reader();
	if (kind == 0) {
		if (sav[1] > 0) { return 0; }
		if (sav[1] <= 0) { return 1; }
	} else if (kind == 1) {
		if (sav[4] > 0) { return 0; }
		if (sav[4] <= 0) { return 1;}
	}
	return 2;
}

void board_screen(int pos_x, int pos_y) {
	int * sav = save_reader();
	int loop = 0;
	clear();
	move(0, 0);
	board_header_screen(1);
	printw("%s", board_screen_prompt);
	if (sav[10] >= 1 && sav[10] <= 4) {
			if (sav[0] > 0 || sav[4] > 0) {
				if (sav[10] == 4) {
					save_writer(10, 0); // set poison effects back to 0 (disabled)
					printw("The %s shakes off the poison.",race_display(sav[3],1,1));
				} else {
					int dam = (rand()%4)+1;
					save_writer(10, sav[10]+1); // increment
					save_writer(4, sav[4]-dam); // damage
					printw("The %s lost %dHP from the poison!", race_display(sav[3],1,1), dam);
				}
			}
			refresh();
			game_sleep(1000);
	}
	if (entity_alive(0) == 1) {
		clear(); board_header_screen(1); move(pos_y, 0);
		printw("You died!\n"); record_writer(1); refresh();
		game_sleep(1000);
		move(pos_y, 0);
		new_game_manager();
	} if (entity_alive(1) == 1) {
		clear(); board_header_screen(1); move(pos_y, 0);
		printw("You win!\n"); record_writer(0); refresh();
		game_sleep(1000);
		move(pos_y, 0);
		new_game_manager();
	}
	while (loop == 0) {
		move(pos_y, pos_x); printw("<");
		refresh();
		int ipu; ipu = getch();
		switch (ipu) {
			case 'q':
			case CTRL('q'):
            case CTRL('c'):
                curs_set(1);
				clear();
				endwin();
				#ifdef _WIN32
					system("pause");
				#else
                	system("stty sane");
				#endif
				exit(0);
                break;
			case KEY_DOWN:
            case 's':
			case 'k':
				mvdelch(pos_y, pos_x);
				if (pos_y == 10) {
					pos_y = 7;
				} else { pos_y += 1; }
                break;
			case KEY_UP:
            case 'w':
			case 'i':
				mvdelch(pos_y, pos_x);
				if (pos_y == 7) {
					pos_y = 10;
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
			case 7:
				move(pos_y+5, 0);
				if (sav[1] >= sav[4]) {
					attack(0);
					if (sav[4] > 0) { attack(1); }
				} else {
					attack(1);
					if (sav[1] > 0) { attack(0); }
				}
				break;
			case 8:
				move(pos_y+4, 0);
				if (items() == 0) {
					if (sav[4] > 0) {
						move(pos_y+10, 0);
						attack(1);
					}
				}
				break;
			case 9:
				move(pos_y+2, 0);
				if (spare() == 0 || sav[4] < 2) {
					clear();
					board_header_screen(1);
					move(pos_y-2, 0);
					new_game_manager();
				} else { attack(1); } break;
				break;
			case 10:
				return;
				break;
		}
	} board_screen(pos_x, pos_y);
}

void reset_screen() {
	int pos_x = 6;
	int pos_y = 15;
	int loop = 0;
	printw("Just to verify, you want to reset your save files?\n\n[YES]\n[NO ]\n\n");
	while (loop == 0) {
		move(pos_y, pos_x); printw("<");
		refresh();
		int ipu; ipu = getch();
		switch (ipu) {
			case 'q':
			case CTRL('q'):
            case CTRL('c'):
                curs_set(1);
				clear();
				endwin();
				#ifdef _WIN32
					system("pause");
				#else
                	system("stty sane");
				#endif
				exit(0);
                break;
			case KEY_UP:
            case 'w':
			case 'i':
				mvdelch(pos_y, pos_x);
				if (pos_y == 16) {
					pos_y -= 1;
				} else { pos_y += 1; }
                break;
			case KEY_DOWN:
            case 's':
			case 'k':
				mvdelch(pos_y, pos_x);
				if (pos_y == 15) {
					pos_y += 1;
				} else { pos_y -= 1; }
                break;
            case '\n':
                loop = 1;
                break;
			default:
                break;
		}
	}
	if (pos_y == 15) {
		move(18, 0);
		if (remove("data.txt") != 0 || remove("record.txt") != 0) {
			printw("Failed to delete temp files.");
		} else {
			printw("Successfully deleted.");
		}
		refresh();
		game_sleep(200);
	}
}

void credits_screen() {
	const char* catboy_contribs[] = {"ARMv8 experimentation", "Quality assurance", "Battle design", "Playtest"};
	const char* a[] = {"Developed by draumaz", " in C!", " (with the lovely curses library)"};
	int b[] = {500, 500, 100}; int c[] = {35, 20, 10};
	clear();
	int pos = 1;
	move(1, 0);
	lbl_reader("Butterfly", 30); printw(","); refresh(); game_sleep(500); printw(" v");
	lbl_reader(version(), 15);
	game_sleep(500);
	pos += 2; move(pos, 0);
	for (int i = 0 ; i < 3; i++) {
		lbl_reader(a[i], c[i]);
		game_sleep(b[i]);
	} game_sleep(1000);
	pos += 2; move(pos, 0);
	lbl_reader("Special thanks to:",35);
	game_sleep(500);
	pos += 2; move(pos, 0);
	printw("catboy6969!", 30);
	pos += 2; move(pos, 0);
	for (int i = 0; i < 4; i++) {
		lbl_reader(catboy_contribs[i], 25);
		pos += 1; move(pos, 0); refresh();
	} game_sleep(500); pos+= 1; move(pos, 0);
	printw("Bryce Cano!");
	pos += 2; move(pos, 0);
	lbl_reader("Character design", 25);
	pos += 1; move(pos, 0);
	lbl_reader("Inspiration", 25);
	refresh();
	game_sleep(1000);
}

void splash_screen(int pos_x, int pos_y) {
	int game = 0;
	save_exists();
    record_exists();
	clear();
	for (int i = 0; i < 7; i++) { printw("%s\n",splash_ascii[i]); }
	printw("\n[PLAY   ]\n[RESET  ]\n[CREDITS]\n[EXIT   ]\n\n");
	while (game == 0) {
        move(pos_y, pos_x); printw("<");
        refresh();
		int ipu; ipu = getch();
        switch (ipu) {
            case 'q':
			case CTRL('q'):
			case CTRL('c'):
                return;
                break;
            case KEY_DOWN:
			case 's':
			case 'k':
				mvdelch(pos_y, pos_x);
                if (pos_y < 11 || ! pos_y > 8) {
                    pos_y += 1;
                } else if (pos_y == 11) {
                    pos_y = 8;
                }
                break;
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
            case '\n':
                game = 1;
                break;
            default:
                break;
        }
    }
	move(14, 12);
    if (pos_y == 8) {
		int * sav = save_reader();
		for (int i = 0; i < 5; i++) {
			if (sav[i] == 0) {
				stats_deploy();
			}
		}
        board_screen(8, 7);
    } else if (pos_y == 9) {
        move(13, 0); reset_screen();
    } else if (pos_y == 10) {
        credits_screen();
    } else if (pos_y == 11) {
		return;
	}
	splash_screen(pos_x, pos_y);
}
