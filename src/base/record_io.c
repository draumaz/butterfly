// Savesys, an easily-implementable save manager
// draumaz, 2022 | MIT

// CONFIG START //
#define RECORD_LENGTH 2
#define RECORD_NAME "record.txt"
// CONFIG END   //

#include <stdio.h>

int * record_reader() {
	static int array[RECORD_LENGTH];
	FILE *read_in = fopen(RECORD_NAME, "r");
	for (int i = 0; i < RECORD_LENGTH; i++) {
		fscanf(read_in, "%d", &array[i]);
	}
	fclose(read_in);
	return array;
}

void record_writer(int line, int state) {
	if (state < 0) { state = 0; }
	int * save_in = record_reader();
	FILE *read_out = fopen(RECORD_NAME, "w");
	for (int i = 0; i < RECORD_LENGTH; i++) {
		if (i == line) {
			fprintf(read_out, "%d\n", state);
		} else {
			fprintf(read_out, "%d\n", save_in[i]);
		}
	}
	fclose(read_out);
}

void record_generate() {
	FILE *generate = fopen(RECORD_NAME, "w");
	for (int i = 0; i < RECORD_LENGTH; i++) {
		fprintf(generate, "%d\n", 0);
	}
	fclose(generate);
}

void record_exists() {
	FILE *f;
	if ((f = fopen(RECORD_NAME, "r"))) {
	} else {
		record_generate();
	}
}
