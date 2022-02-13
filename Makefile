CDR = cd ./src/base/build

butterfly:
	mkdir \
	-pv \
	./src/base/build
	$(CC) $(CFLAGS) -Wall -c ./src/base/gdata.c -o ./src/base/build/gdata.o
	$(CC) $(CFLAGS) -Wall -c ./src/base/save_io.c -o ./src/base/build/save_io.o
	$(CC) $(CFLAGS) -Wall -c ./src/base/record_io.c -o ./src/base/build/record_io.o
	$(CC) $(CFLAGS) -Wall -c ./src/base/wires.c -o ./src/base/build/wires.o
	$(CC) $(CFLAGS) -Wall -c ./src/base/joystick.c -o ./src/base/build/joystick.o
	$(CC) $(CFLAGS) -Wall -c ./src/base/screen.c -o ./src/base/build/screen.o
	$(CC) $(CFLAGS) -Wall -c ./src/base/action.c -o ./src/base/build/action.o
	$(CC) $(CFLAGS) -Wall -c ./src/base/main.c -o ./src/base/build/main.o
	$(CDR) && $(CC) $(CFLAGS) -Wall -lncurses -lm \
	-ltinfo \
	main.o gdata.o wires.o joystick.o screen.o record_io.o save_io.o action.o \
	-o ../../../butterfly-debug
	rm -r ./src/base/build
