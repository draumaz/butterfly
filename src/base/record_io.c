#include <stdio.h>
#include <unistd.h>

#define RECORD_LENGTH 3
#define RECORD_NAME "record.txt"

// record positions
// 0 kills
// 1 deaths
// 2 spares

int * record_reader() {
	static int array[RECORD_LENGTH];
	FILE *record_in = fopen(RECORD_NAME, "r");
	int i = 0;
	int x = 0;
	fscanf(record_in, "%d", &i);
	while (!feof (record_in)) {
		array[x] = i;
		x += 1;
		fscanf(record_in, "%d", &i);
	}
	fclose(record_in);
	return array;
}

void record_writer(int line) {
	int * record_in = record_reader();
	FILE *record_out = fopen(RECORD_NAME, "w");
	for (int i = 0; i < RECORD_LENGTH; i++) {
		if (i == line) {
			record_in[i] += 1;
		} fprintf(record_out, "%d\n", record_in[i]);
	}
	fclose(record_out);
}

void record_generate() {
	FILE *generate = fopen(RECORD_NAME, "w");
	for (int i = 0; i < RECORD_LENGTH; i++) {
		fprintf(generate, "%d\n", 0);
	}
	fclose(generate);
}

void record_exists() {
	if (access(RECORD_NAME,F_OK) == -1) {
		record_generate();
	}
}
