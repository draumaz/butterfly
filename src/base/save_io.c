#include <stdio.h>
#include <unistd.h>

#define SAVE_LENGTH 11
#define SAVE_NAME "data.txt"

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

int * save_reader() {
	static int array[SAVE_LENGTH];
	FILE *read_in = fopen(SAVE_NAME, "r");
	int i = 0;
	int x = 0;
	fscanf(read_in, "%d", &i);
	while (!feof (read_in)) {
		array[x] = i; x += 1;
		fscanf(read_in, "%d", &i);
	}
	fclose(read_in);
	return array;
}

void save_writer(int line, signed int state) {
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
	if (access(SAVE_NAME,F_OK) == -1) {
		save_generate();
	}
}
