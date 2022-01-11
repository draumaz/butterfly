butterfly:
	cd ./src/base; \
		g++ -march=native -O2 -Wall \
		main.cpp gtool.cpp tool.cpp screen.cpp stat_gen.cpp action.cpp \
		save_io.cpp record_io.cpp \
	        -o ../../butterfly-debug
