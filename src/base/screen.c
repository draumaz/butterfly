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

const char* board_screen_prompt = "\n\nFIGHT [1]\nITEMS [2]\nSPARE [3]\nEXIT  [4]\n\n";

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

char board_again_screen() {
	printw("\n\nPlay again?\n\nYES [1]\nNO [2]\n\n");
	return (char)getch();
}

void new_game_manager() {
	if (board_again_screen() == '1') {
		stats_deploy();
		board_screen();
	} else { 
                printw("\n"); 
                #ifdef _WIN32
			system("pause");
		#else
                        system("stty sane");
                #endif
                exit(0);
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
	printw("%dx POTION [1] (restore 10HP)\n%dx SPEAR  [2] (deal 9 damage)\n%dx POISON [3] (damage over 3 turns)\nBACK      [4]\n\n",sav[7],sav[8],sav[9]);
}

void board_screen() {
	srand(time(0));
	int * sav = save_reader();
	clear();
	if (sav[10] >= 1 && sav[10] <= 4) {
		if (sav[0] > 0 || sav[4] > 0) {
			if (sav[10] == 4) {
				save_writer(10, 0); // set poison effects back to 0 (disabled)
				clear();
				board_header_screen(0);
				printw("\nThe %s shakes off the poison.",race_display(sav[3],1,1));
			} else {
				int dam = (rand()%4)+1;
				save_writer(10, sav[10]+1); // increment
				save_writer(4, sav[4]-dam); // damage
				clear();
				board_header_screen(0);
				printw("\nThe %s loses %dHP from the poison!", race_display(sav[3],1,1), dam);
			}
		}
		refresh();
		game_sleep(1000);
		clear();
	}
	board_header_screen(1);
	if (sav[1] <= 0) {
		printw("\n\nYou died!\n"); record_writer(1); refresh();
		game_sleep(1000);
		new_game_manager();
	} else if (sav[4] <= 0) {
		printw("\n\nYou win!\n"); record_writer(0); refresh();
		game_sleep(1000);
		new_game_manager();
	}
	printw("%s",board_screen_prompt);
	switch (getch()) {
		case '1':
			if (sav[1] >= sav[4]) {
				attack(0);
				if (sav[4] > 0) { attack(1); }
			} else {
				attack(1);
				if (sav[1] > 0) { attack(0); }
			} break;
		case '2':
			if (items() == 0) {
				if (sav[4] > 0) {
					attack(1);
				}
			} break;
		case '3':
			if (spare() == 0 || sav[4] < 2) {
				clear();
				board_header_screen(1);
				new_game_manager();
			} else { attack(1); } break;
		case '4':
			splash_screen();
			break;
		default:
			break;
	}
	refresh();
	board_screen();
}

void reset_screen() {
	int pos_x = 8;
	int pos_y = 15;
	int loop = 0;
	//printw("Just to verify, you want to reset your save files?\n\nYES [1]\nNO  [2]\n\n");
	while (loop == 0) {
		move(13, 0);
		printw("Just to verify, you want to reset your save files?\n\nYES [1]\nNO  [2]\n\n");
		move(pos_y, pos_x); printw("< %d, %d", pos_x, pos_y);
		refresh();
		switch (getch()) {
			case 'q':
                curs_set(1);
				#ifdef _WIN32
					system("pause");
				#else
                	system("stty sane");
				#endif
				exit(0);
                break;
            case 's':
				if (pos_y == 16) {
					pos_y -= 1;
				} else { pos_y += 1; }
                break;
            case 'w':
				if (pos_y == 15) {
					pos_y += 1;
				} else { pos_y -= 1; }
                break;
            case '\n':
                loop = 1;
                break;
			default:
				curs_set(1); system("stty sane");
				exit(0); break;
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
	clear();
	printw("\n");
	lbl_reader("Butterfly",30);
	game_sleep(500);
	printw(" v"); fflush(stdout);
	lbl_reader(version(),10);
	game_sleep(1000);
	printw("\n\n");
	lbl_reader("Developed by draumaz",35);
	game_sleep(500);
	lbl_reader(" in C!",20);
	game_sleep(750);
	lbl_reader(" (with the lovely curses library)", 10);
	game_sleep(1000);
	printw("\n\n");
	lbl_reader("Special thanks to:",35);
	game_sleep(500);
	printw("\n\ncatboy6969!",25);
	refresh();
	game_sleep(750);
	printw("\nBryce Cano!", 25);
	refresh();
	game_sleep(1000);
}

void splash2(int pos_x, int pos_y) {
	int game = 0;
	save_exists();
    record_exists();
	while (game == 0) {
        clear();
		for (int i = 0; i < 7; i++) { printw("%s\n",splash_ascii[i]); }
		printw("\nPLAY    [1]\nRESET   [2]\nCREDITS [3]\nEXIT    [4]\n\n");
        move(pos_y, pos_x); printw("< ");
        printw("%d, %d", pos_x, pos_y);
        refresh();
        switch ((char)getch()) {
            case 'q':
                return;
                break;
            case 's':
                if (pos_y < 11 || ! pos_y > 8) {
                    pos_y += 1;
                } else if (pos_y == 5) {
                    pos_y = 3;
                }
                break;
            case 'w':
                if (pos_y > 8) {
                    pos_y -= 1;
                } else if (pos_y == 3) {
                    pos_y = 5;
                }
                break;
            case '\n':
                game = 1;
                break;
            default:
                break;
        }
    }
    if (game == 1) {
		move(14, 12);
        if (pos_y == 8) {
            printw(" You said yes!\n"); refresh(); sleep(1);
        } else if (pos_y == 9) {
            move(13, 0); reset_screen();
        } else if (pos_y == 10) {
            credits_screen();
        } else if (pos_y == 11) {
			return;
		}
        splash2(pos_x, pos_y);
    }
}

void splash_screen() {
        save_exists();
        record_exists();
		int x = 0;
		while (x == 0) {
			for (int i = 0; i < 7; i++) { printw("%s\n",splash_ascii[i]); }
			printw("\nPLAY    [1] | CREDITS   [3]\nRESET [2] | EXIT    [4]\n\n");
			refresh();
			switch (getch()) {
					case '1': {
							switch (in_prog_warn()) {
									case '1':
											stats_deploy();
											board_screen();
											break;
									case '2':
											break;
									case '3':
											splash_screen();
											break;
							}
							stats_deploy();
							board_screen();
							break; }
					case '2': {
							printw("Just to verify, you want to reset your save files?\n\nYES [1]\nNO  [2]\n\n");
				switch (getch()) {
					case '1':
						if (remove("data.txt") != 0 || remove("record.txt") != 0) {
							printw("Failed to delete temp files.");
						} else {
							printw("Successfully deleted.");
						}
						refresh();
						game_sleep(200);
						break;
					case '2':
						splash_screen();
						break;
				} break; }
					case '3': {
							clear();
							printw("\n");
				lbl_reader("Butterfly",30);
				game_sleep(500);
				printw(" v"); fflush(stdout);
				lbl_reader(version(),10);
				game_sleep(1000);
				printw("\n\n");
				lbl_reader("Developed by draumaz",35);
				game_sleep(500);
				lbl_reader(" in C!",20);
				game_sleep(750);
							lbl_reader(" (with the lovely curses library)", 10);
							game_sleep(1000);
				printw("\n\n");
				lbl_reader("Special thanks to:",35);
				game_sleep(500);
				printw("\n\ncatboy6969!",25);
							refresh();
				game_sleep(750);
				printw("\nBryce Cano!", 25);
							refresh();
				game_sleep(1000);
							break; }
					case '4': {
							clear();
							printw("\nThanks for playing my game!\n\nKeep up with development at ");
							lbl_reader("https://github.com/draumaz/butterfly.", 10);
							printw("\n\n");
							refresh();
							#ifdef _WIN32
					system("pause");
				#else
									system("stty sane");
							#endif
							exit(0);
							break; }
					default: {
							printw("Did you mean something else?");
							refresh();
							game_sleep(200);
							clear();
							splash_screen();
							break; }
			}
        refresh();
		}
        splash_screen();
}
