#include <stdio.h>
#include <unistd.h>

const char* save_name = "data.txt";

int * save_reader() {
	static int array[12];
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
	for (int i = 0; i < 12; i++) {
		if (i == line) {
			fprintf(read_out, "%d\n", state);
		} else {
			fprintf(read_out, "%d\n", save_in[i]);
		}
	} fclose(read_out);
}

void save_generate() {
	FILE *generate = fopen(save_name, "w");
	for (int i = 0; i < 12; i++) {
		fprintf(generate, "%d", 0);
	}
}

void save_exists() {
	if (access(save_name,F_OK) == -1) {
		save_generate();
	}
}
