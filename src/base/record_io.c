#include <stdio.h>
#include <unistd.h>

char* record_name = "record.txt";

// record positions
// 0 kills
// 1 deaths
// 2 spares

int * record_reader() {
	static int array[4];
	FILE *read_in = fopen(record_name, "r");
	int i = 0;
	int x = 0;
	fscanf(read_in, "%d", &i);
	while (!feof (read_in)) {
		array[x] = i;
		x += 1;
		fscanf(read_in, "%d", &i);
	}
	return array;
}

void record_writer(int line) {
	int * record_in = record_reader();
	FILE *record_out = fopen(record_name, "w");
	for (int i = 0; i < 4; i++) {
		if (i == line) {
			record_in[i] += 1;
		} fprintf(record_out, "%d\n", record_in[i]);
	}
	fclose(record_out);
}

void record_generate() {
	FILE *generate = fopen(record_name, "w");
	for (int i = 0; i < 4; i++) {
		fprintf(generate, "%d\n", 0);
	}
	fclose(generate);
}

void record_exists() {
	if (access(record_name,F_OK) == -1) {
		record_generate();
	}
}
