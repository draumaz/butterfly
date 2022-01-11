#include <stdio.h>
#include <unistd.h>

const char* save_name = "data.txt";

int * save_reader() {
	static int array[9];
	FILE *read_in = fopen(save_name, "r");
	int i = 0; int j = 0; int x = 0;
	j = fscanf(read_in, "%d", &i);
	while (!feof (read_in)) {
		array[x] = i; x += 1;
		j = fscanf(read_in, "%d", &i);
	} j += 1; return array;
}

void save_writer(int line, int state) {
	if (state < 0) { state = 0; }
	int * save_in = save_reader();
	FILE *read_out = fopen(save_name, "w");
	for (int i = 0; i < 9; i++) {
		if (i == line) {
			fprintf(read_out, "%d\n", state);
		} else {
			fprintf(read_out, "%d\n", save_in[i]);
		}
	} fclose(read_out);
}

void save_generate() {
	FILE *generate = fopen(save_name, "w");
	for (int i = 0; i < 9; i++) {
		if (i <= 6) {
			fprintf(generate, "%d\n", 0);
		} else {
			fprintf(generate, "%d\n", 1); // items
		}
	}
}

void save_exists() {
	if (access(save_name,F_OK) == -1) {
		save_generate();
	}
}
