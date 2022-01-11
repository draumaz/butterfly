#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <errno.h>

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
		printf("%c",line[i]); fflush(stdout);
		game_sleep(stile);
	}
}

int user_input_int(int min, int max) {
	char in[99] = "";
	const char* s0 = "ACTION >> ";
	const char* s1 = "Did you mean something else?";
	int x,y = 0;
	while (x < x+1) {
		printf("\n");
		lbl_reader(s0, 10);
		scanf("%s",in);
		for (long unsigned int i = 0; i < strlen(in); i++) {
			if (! isdigit(in[i])) {
				y = 1;
			}
		}
		if (y == 1) {
			printf("\n");
			lbl_reader(s1, 5);
			y = 0;
			game_sleep(100);
			printf("\n");
		} else { break; }
	} return atoi(in);
}
