#include <iostream>
#include <fstream>
#include <unistd.h>

float version() { return 0.08; }

int screen_clear() {
	const char* cmd = NULL;
	#ifdef _WIN32
		cmd = "cls";
	#else
		cmd = "clear";
	#endif
	return system(cmd);
}
