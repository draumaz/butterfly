#include <stdio.h>
#include <unistd.h>

char* save_name = "data.txt";

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
	static int array[12];
	FILE *read_in = fopen(save_name, "r");
	int i = 0;
	int x = 0;
	fscanf(read_in, "%d", &i);
	while (!feof (read_in)) {
		array[x] = i; x += 1;
		fscanf(read_in, "%d", &i);
	}
	return array;
}

void save_writer(int line, int state) {
	if (state < 0) { state = 0; }
	int * save_in = save_reader();
	FILE *read_out = fopen(save_name, "w");
	for (int i = 0; i < 12; i++) {
		if (i == line) {
			fprintf(read_out, "%d\n", state);
		} else {
			fprintf(read_out, "%d\n", save_in[i]);
		}
	}
	fclose(read_out);
}

void save_generate() {
	FILE *generate = fopen(save_name, "w");
	for (int i = 0; i < 12; i++) {
		fprintf(generate, "%d\n", 0);
	}
	fclose(generate);
}

void save_exists() {
	if (access(save_name,F_OK) == -1) {
		save_generate();
	}
}
