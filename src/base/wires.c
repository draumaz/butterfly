#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <curses.h>

char* version() {
    return "0.13";
}

void game_ender() {
    #ifdef _WIN32
		system("pause");
	#else
        system("stty sane");
	#endif
}

void scr_sleep(int ms) {
    struct timespec ts;
    int res;
    if (ms < 0) {
        errno = EINVAL;
    }
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    do { 
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);
}

void scr_popwrite(char* l, int p) {
    for (unsigned long int i = 0; i < strlen(l); i++) {
        printw("%c",l[i]); refresh();
        scr_sleep(p);
    }
}