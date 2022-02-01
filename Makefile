butterfly:
	cd ./src/base; mkdir -pv build; cd build; \
		$(CC) $(CFLAGS) -Wall -c -lncurses -ltinfo -lm ../main.c \
		../main.c ../gdata.c ../wires.c ../joystick.c ../screen.c \
		../record_io.c ../save_io.c ../action.c
	$(CC) $(CFLAGS) -Wall -lncurses -ltinfo -lm \
		./src/base/build/main.o \
		./src/base/build/gdata.o \
		./src/base/build/wires.o \
		./src/base/build/joystick.o \
		./src/base/build/screen.o \
		./src/base/build/record_io.o \
		./src/base/build/save_io.o \
		./src/base/build/action.o -o butterfly-debug
	rm -r ./src/base/build
