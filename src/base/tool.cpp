#include <iostream>
#include <fstream>
#include <unistd.h>

const char* version() { return "0.08_01"; }

int screen_clear() {
	const char* cmd = NULL;
	#ifdef _WIN32
		cmd = "cls";
	#else
		cmd = "clear";
	#endif
	return system(cmd);
}
