#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <curses.h>

#include "./../header/save_io.h"
#include "./../header/record_io.h"
#include "./../header/joystick.h"
#include "./../header/wires.h"
#include "./../header/gdata.h"

//#include "./../header/screen.h"

#ifndef CTRL
#define CTRL(c) ((c) & 037)
#endif

const char* splash_ascii[] = {"______ _   _ _____ _____ _________________ _   __   __",
	"| ___ | | | |_   _|_   _|  ___| ___ |  ___| |  \\ \\ / /",
        "| |_/ | | | | | |   | | | |__ | |_/ | |_  | |   \\ V /  (.\\\\//.)",
        "| ___ | | | | | |   | | |  __||    /|  _| | |    \\ /    \\ () /",
        "| |_/ | |_| | | |   | | | |___| |\\ \\| |   | |____| |    (_/\\_)",
        "\\____/ \\___/  \\_/   \\_/ \\____/\\_| \\_\\_|   \\_____/\\_/  ",
        "------------------------------------------------------------------"
};

void board_header(int x, int y) {
    int * rec = record_reader();
    move(1, 0);
    printw("Butterfly v%s | KILLS:     | DEATHS:     | SPARES:   ", version()); // 25, 39, 53
    move(3, 0);
    printw("PLAYR:        | HP:    | STR:    "); // 7, 20, 30
    move(5, 0);
    printw("ENEMY:        | HP:    | STR:    "); // 7, 20, 30
    move(y, x);
}

void board_header_update(int x, int y, int m) {
    int * rec = record_reader();
    int * sav = save_reader();
    switch (m) {
        case 0: // kill count
            move(1, 25);
            printw("%d", rec[0]);
            if (rec[0] < 10) {
                move(1, 26); printw(" ");
            }
            break;
        case 1: // death count
            move(1, 39);
            printw("%d", rec[1]);
            if (rec[1] < 10) {
                move(1, 40); printw(" ");
            }
            break;
        case 2: // spare count
            move(1, 53);
            printw("%d", rec[2]);
            if (rec[2] < 10) {
                move(1, 53); printw(" ");
            }
            break;
        case 3: // player race
            move(3, 7);
            printw("%s", race_display(sav[0],0,0));
            break;
        case 4: // player hp
            move(3, 20);
            printw("%d", sav[1]);
            if (sav[1] < 10) {
                move(3, 21); printw(" ");
            }
            break;
        case 5: // player str
            move(3, 30);
            printw("%d", sav[2]);
            if (sav[2] < 10) {
                move(3, 31); printw(" ");
            }
            break;
        case 6: // enemy race
            move(5, 7);
            printw("%s", race_display(sav[3],1,0));
            break;
        case 7: // enemy hp
            move(5, 20);
            printw("%d", sav[4]);
            if (sav[5] < 10) {
                move(3, 21); printw(" ");
            }
            break;
        case 8: // enemy str
            move(5, 30);
            printw("%d", sav[5]);
            if (sav[5] < 10) {
                move(3, 31); printw(" ");
            }
            break;
    }
    refresh();
}

void scr_board() {
    int pos_x = 0; int pos_y = 0;
    save_writer(2, 95);
    board_header(pos_x, pos_y);
    for (int i = 0; i < 9; i++) { board_header_update(pos_x, pos_y, i); }
    sleep(1);
    board_header_update(pos_x, pos_y, 5); refresh();
    sleep(2);
}

void landing_reset() {
    int pos_x = 0; int pos_y = 13;
    move(pos_y, pos_x);
    printw("Just to verify, you want to reset your save files?");
    pos_y += 2; move(pos_y, pos_x);
    printw("[YES]");
    pos_y += 1; move(pos_y, pos_x);
    printw("[NO ]");
    pos_y = 15; pos_x = 6;
    int game = 0;
    while (game == 0) {
        move(pos_y, pos_x); printw("<");
        refresh();
        int ipu = getch();
        switch (ipu) {
            case 'q':
            case CTRL('q'):
            case CTRL('c'):
                screen_down();
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
				} else { pos_y -= 1; }
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
    }
    move(pos_y-3, 0);
    printw("\n");
    move(pos_y-2, 0);
    printw("\n");
    move(pos_y-1, 0);
    printw("\n");
    move(pos_y, 0);
    printw("\n");
    move(pos_y+1, 0);
    printw("\n");
    move(pos_y+2, 0);
    printw("\n");
    move(pos_y+3, 0);
    printw("\n");
    refresh();
}

void scr_landing() {
    clear();
    int pos_x = 0; int pos_y = 0;
    move(pos_y, pos_x);
    for (int i = 0; i < 7; i++) { printw("%s\n",splash_ascii[i]); pos_y += 1; move(pos_y, pos_x); } refresh();
    pos_y += 1; move(pos_y, pos_x);
    printw("[PLAY   ]");
    pos_y += 1; move(pos_y, pos_x);
    printw("[RESET  ]");
    pos_y += 1; move(pos_y, pos_x);
    printw("[CREDITS]");
    pos_y += 1; move(pos_y, pos_x);
    printw("[EXIT   ]");
    pos_y = 8; pos_x = 10; // position at PLAY
    int game_o = 0;
    while (game_o == 0) {
        save_exists(); record_exists();
        int game = 0;
        while (game == 0) {
            move(pos_y, pos_x); printw("<");
            refresh();
            int ipu = getch();
            switch (ipu) {
                case 'q':
                case CTRL('q'):
                case CTRL('c'):
                    screen_down();
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
                    if (pos_y < 11 || ! pos_y > 8) {
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
                    printw("play opt");
                    break;
                case 9:
                    landing_reset();
                    break;
                case 10:
                    printw("creds opt");
                    break;
                case 11:
                    return;
        } refresh();
    }
}