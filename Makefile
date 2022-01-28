butterfly:
	cd ./src/base; \
		gcc -lncurses -ltinfo -lm \
		main.c gdata.c wires.c joystick.c screen.c \
		record_io.c save_io.c action.c \
	        -o ../../butterfly
