butterfly:
	cd ./src/base; \
		gcc -lncurses -ltinfo -lm \
		main.c screen.c controller.c save_io.c record_io.c \
		gtool.c stat_gen.c action.c \
	        -o ../../butterfly-debug