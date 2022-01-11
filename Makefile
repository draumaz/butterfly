butterfly:
	cd ./src/base; \
		gcc -O2 -lm -Wall \
		main.c gtool.c tool.c screen.c stat_gen.c action.c \
		save_io.c record_io.c \
	        -o ../../butterfly-debug
