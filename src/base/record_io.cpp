#include <fstream>
#include <unistd.h>

const char* record_name = "record.txt";
const int record_size = 4;

int * record_reader() {
	static int array[record_size];
	FILE *read_in = fopen(record_name, "r");
	int i = 0; int j = 0; int x = 0;
	j = fscanf(read_in, "%d", &i);
	while (!feof (read_in)) {
		array[x] = i; x += 1;
		j = fscanf(read_in, "%d", &i);
	} j += 1; return array;
}

void record_writer(int line) { // C++
	int * record_in = record_reader();
	std::ofstream record_out(record_name);
	for (int i = 0; i < 4; i++) {
		if (i == line) {
			record_in[i] += 1;
		} record_out << record_in[i];
		record_out << "\n";
	}
}

void record_generate() {
	std::ofstream gen(record_name);
	for (int i = 0; i < 4; i++) {
		gen << "0\n";
	}
}

void record_exists() {
	if (access(record_name,F_OK) == -1) {
		record_generate();
	}
}
