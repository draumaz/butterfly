#include <stdio.h>
#include <stdlib.h>

#include "./../header/tool.hpp"
#include "./../header/save_io.hpp"
#include "./../header/record_io.hpp"
#include "./../header/gtool.hpp"
#include "./../header/stat_gen.hpp"
#include "./../header/action.hpp"
#include "./../header/screen.hpp"

int board_again_screen() {
	printf("\n\nPlay again?\n\nYES [1]\nNO [2]\n");
	return user_input_int(1, 2);
}

void new_game_manager() {
	if (board_again_screen() == 1) {
			stats_write();
			stats_randomize();
			save_writer(7, 1);
			save_writer(8, 1);
			board_screen();
	} else { printf("\n"); exit(0); }
}

void item_options_screen() {
	int * sav = save_reader();
	printf("\n%dx POTION [1] (restore 10HP)\n%dx SPEAR [2] (deal 9 damage)\nBACK [3]\n",sav[7],sav[8]);
}

void board_header_screen(int fake_options) {
	int * rec = record_reader();
	int * sav = save_reader();
	printf("\nButterfly v%s | KILLS: %d | DEATHS: %d | SPARES: %d", version(), rec[0], rec[1], rec[2]);
	printf("\n\nRACE: %s | HP: %d | STR: %d", race_display(sav[0],0,true), sav[1], sav[2]);
	printf("\n\nENEMY RACE: %s | HP: %d | STR: %d", race_display(sav[3],1,true),sav[4],sav[5]);
	if (fake_options == 0) {
		printf("\n\nFIGHT [1]\nITEMS [2]\nSPARE [3]\nEXIT  [4]\n");
	}
}

void board_screen() {
	int * sav = save_reader();
	screen_clear();
	board_header_screen(1);
	if (sav[1] <= 0) {
		printf("\n\nYou died!"); record_writer(1); fflush(stdout);
		game_sleep(1000);
		new_game_manager();
	} else if (sav[4] <= 0) {
		printf("\n\nYou win!"); record_writer(0); fflush(stdout);
		game_sleep(1000);
		new_game_manager();
	}
	printf("\n\nFIGHT [1]\nITEMS [2]\nSPARE [3]\nEXIT  [4]\n");
	switch (user_input_int(1, 4)) {
		case 1:
			if (sav[1] >= sav[4]) {
				attack(0);
				if (sav[4] > 0) { attack(1); }
			} else {
				attack(1);
				if (sav[1] > 0) { attack(0); }
			} break;
		case 2:
			if (items() == 0 || sav[1] < 5) {
				attack(1);
			} break;
		case 3:
			if (spare() == 0 || sav[4] < 2) {
				screen_clear();
				board_header_screen(1);
				new_game_manager();
			} else { attack(1); } break;
		case 4:
			splash_screen();
			break;
		default:
			break;
	}
	fflush(stdout);
	board_screen();
}

int gip_warn() {
	int * s = save_reader();
	int warn = 1;
	for (int i = 0; i < 6; i++) {
		if (s[i] != 0) {
			warn = 0;
			break;
		}
	} if (warn == 0) {
		printf("\nGame in progress.\n\nCONTINUE [1]\nRESET [2]\nBACK [3]\n");
		return (user_input_int(1,3)-1);
	} return 1;
}

void splash_screen() {
	screen_clear();
	save_exists();
	record_exists();
	const char* splash_ascii[] = {"______ _   _ _____ _____ _________________ _   __   __",
	"| ___ | | | |_   _|_   _|  ___| ___ |  ___| |  \\ \\ / /",
	"| |_/ | | | | | |   | | | |__ | |_/ | |_  | |   \\ V /  (.\\\\//.)",
	"| ___ | | | | | |   | | |  __||    /|  _| | |    \\ /    \\ () /",
	"| |_/ | |_| | | |   | | | |___| |\\ \\| |   | |____| |    (_/\\_)",
	"\\____/ \\___/  \\_/   \\_/ \\____/\\_| \\_\\_|   \\_____/\\_/  ",
	"------------------------------------------------------------------"};
	for (int i = 0; i < 7; i++) { printf("%s\n",splash_ascii[i]); }
	printf("\nPLAY  [1] | CREDITS [3]\nRESET [2] | EXIT    [4]\n");
	switch (user_input_int(1, 4)) {
		case 1:
			switch (gip_warn()) {
				case 0:
					board_screen();
					break;
				case 1:
					stats_write();
					save_writer(7, 1);
					save_writer(8, 1);
					stats_randomize();
					board_screen();
					break;
				case 2:
					splash_screen();
					break;
			} break;
		case 2:
			printf("\nJust to verify, you want to reset your save files?\n\nYES [1]\nNO [2]\n");
			switch (user_input_int(1, 2)) {
				case 1:
					if (remove("data.txt") != 0 || remove("record.txt") != 0) {
					printf("\nFailed to delete temp files.");
				} else {
					printf("\nSuccessfully deleted.");
				}
				fflush(stdout);
				game_sleep(200);
			} break;
		case 3: {
			screen_clear();
			printf("\n");
			lbl_reader("Butterfly",30);
			game_sleep(500);
			printf(" v"); fflush(stdout);
			lbl_reader(version(),10);
			game_sleep(1000);
			printf("\n\n");
			lbl_reader("Developed by draumaz",35);
			game_sleep(500);
			lbl_reader(" in C++!",20);
			game_sleep(1000);
			printf("\n\n");
			lbl_reader("Special thanks to:",35);
			game_sleep(500);
			lbl_reader("\n\ncatboy6969!",25);
			game_sleep(500);
			lbl_reader("\nBryce Cano!", 25);
			game_sleep(1000);
			break; }
		case 4:
			screen_clear();
			printf("\nThanks for playing my game!\n\nKeep up with development at ");
			lbl_reader("https://github.com/draumaz/butterfly.", 10);
			printf("\n\n");
			exit(0);
			break;			
	} splash_screen();
}
