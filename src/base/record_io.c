#include <stdio.h>
#include <unistd.h>

const char* record_name = "record.txt";

int * record_reader() {
	static int array[4];
	FILE *read_in = fopen(record_name, "r");
	int i = 0; int j = 0; int x = 0;
	j = fscanf(read_in, "%d", &i);
	while (!feof (read_in)) {
		array[x] = i; x += 1;
		j = fscanf(read_in, "%d", &i);
	} j += 1; return array;
}

void record_writer(int line) {
	int * record_in = record_reader();
	FILE *record_out = fopen(record_name, "w");
	for (int i = 0; i < 4; i++) {
		if (i == line) {
			record_in[i] += 1;
		} fprintf(record_out, "%d\n", record_in[i]);
	} fclose(record_out);
}

void record_generate() {
	FILE *generate = fopen(record_name, "w");
	for (int i = 0; i < 4; i++) {
		fprintf(generate, "%d\n", 0);
	}
}

void record_exists() {
	if (access(record_name,F_OK) == -1) {
		record_generate();
	}
}
