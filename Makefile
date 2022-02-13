butterfly:
	mkdir \
	-pv \
	./build
	$(CC) $(CFLAGS) -Wall -c ./src/base/gdata.c -o ./build/gdata.o
	$(CC) $(CFLAGS) -Wall -c ./src/base/save_io.c -o ./build/save_io.o
	$(CC) $(CFLAGS) -Wall -c ./src/base/record_io.c -o ./build/record_io.o
	$(CC) $(CFLAGS) -Wall -c ./src/base/wires.c -o ./build/wires.o
	$(CC) $(CFLAGS) -Wall -c ./src/base/joystick.c -o ./build/joystick.o
	$(CC) $(CFLAGS) -Wall -c ./src/base/screen.c -o ./build/screen.o
	$(CC) $(CFLAGS) -Wall -c ./src/base/action.c -o ./build/action.o
	$(CC) $(CFLAGS) -Wall -c ./src/base/main.c -o ./build/main.o
	cd ./build && $(CC) $(CFLAGS) -Wall -lncurses -lm \
	-ltinfo \
	main.o gdata.o wires.o joystick.o screen.o record_io.o save_io.o action.o \
	-o ../butterfly-debug
	rm -r ./build
