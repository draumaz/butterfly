#include <iostream>
#include <fstream>
#include <unistd.h>

const char* save_name = "data.txt";
const int save_size = 9;

int * save_reader() {
	static int array[save_size];
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
	std::ofstream save_out(save_name);
	for (int i = 0; i < save_size; i++) {
		if (i == line) {
			save_out << state;
		} else {
		save_out << save_in[i];
		}
		save_out << "\n";
	}
}

void save_generate() {
	std::ofstream gen(save_name);
	for (int i = 0; i < save_size; i++) {
		if (i <= 6) {
		gen << "0\n";
		} else {
			gen << "1\n"; // items
		}
	}
}

void save_exists() {
	if (access(save_name,F_OK) == -1) {
		save_generate();
	}
}
