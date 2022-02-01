butterfly:
	cd ./src/base; mkdir -pv build; cd build; \
		gcc -Wall -c -lncurses -ltinfo -lm \
		../main.c ../gdata.c ../wires.c ../joystick.c ../screen.c \
		../record_io.c ../save_io.c ../action.c
	gcc -Wall -lncurses -ltinfo -lm \
		./src/base/build/main.o \
		./src/base/build/gdata.o \
		./src/base/build/wires.o \
		./src/base/build/joystick.o \
		./src/base/build/screen.o \
		./src/base/build/record_io.o \
		./src/base/build/save_io.o \
		./src/base/build/action.o \
		./src/header/gdata.h \
		./src/header/wires.h \
		./src/header/joystick.h \
		./src/header/screen.h \
		./src/header/record_io.h \
		./src/header/save_io.h \
		./src/header/action.h \
		./src/header/selections.h -o butterfly-debug
	rm -r ./src/base/build
