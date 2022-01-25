#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <curses.h>

const char* version() {
    return "0.12";
}

void game_sleep(int ms) {
	struct timespec ts; int res;
	if (ms < 0) { errno = EINVAL; }
	ts.tv_sec = ms / 1000;
	ts.tv_nsec = (ms % 1000) * 1000000;
	do {
		res = nanosleep(&ts, &ts);
	} while (res && errno == EINTR);
}

void lbl_reader(const char* line, int stile) {
	for (unsigned long int i = 0; i < strlen(line); i++) {
		printw("%c",line[i]); refresh();
		game_sleep(stile);
	}
}
