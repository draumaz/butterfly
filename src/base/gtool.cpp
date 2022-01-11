#include <iostream>
#include <chrono>
#include <thread>

void game_sleep(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
	
void lbl_reader(std::string line, int stile) {
	for (unsigned long int i = 0; i < line.length(); i++) {
		std::cout << line[i] << std::flush;
		game_sleep(stile);
	}
}

int user_input_int(int min, int max) {
	int u_ip;
	std::string s0 = "ACTION >> ";
	const char* s1 = "Did you mean something else?";
	printf("\n");
	lbl_reader(s0, 10);
	std::cin >> u_ip;
	while (std::cin.fail() || u_ip < min || u_ip > max) {
		std::cin.clear();
		std::cin.ignore(256, '\n');
		printf("\n%s\n",s1);
		game_sleep(250);
		printf("\n");
		lbl_reader(s0, 10);
		std::cin >> u_ip;
	}
	return u_ip;
}
