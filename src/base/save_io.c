// Savesys, an easily-implementable save manager
// draumaz, 2022 | MIT

// CONFIG START //
#define SAVE_LENGTH 11
#define SAVE_NAME "data.txt"
// CONFIG END   //

// save positions
// 0 player race
// 1 player health
// 2 player strength
// 3 enemy race
// 4 enemy health
// 5 enemy strength
// 6 last item position
// 7 potion qty
// 8 spear qty
// 9 poison qty
// 10 poison incrementer

#include <stdio.h>

int * save_reader() {
	static int array[SAVE_LENGTH];
	FILE *read_in = fopen(SAVE_NAME, "r");
	for (int i = 0; i < SAVE_LENGTH; i++) {
		fscanf(read_in, "%d", &array[i]);
	}
	fclose(read_in);
	return array;
}

void save_writer(int line, int state) {
	if (state < 0) { state = 0; }
	int * save_in = save_reader();
	FILE *read_out = fopen(SAVE_NAME, "w");
	for (int i = 0; i < SAVE_LENGTH; i++) {
		if (i == line) {
			fprintf(read_out, "%d\n", state);
		} else {
			fprintf(read_out, "%d\n", save_in[i]);
		}
	}
	fclose(read_out);
}

void save_generate() {
	FILE *generate = fopen(SAVE_NAME, "w");
	for (int i = 0; i < SAVE_LENGTH; i++) {
		fprintf(generate, "%d\n", 0);
	}
	fclose(generate);
}

void save_exists() {
	FILE *f;
	if ((f = fopen(SAVE_NAME, "r"))) {
	} else {
		save_generate();
	}
}
