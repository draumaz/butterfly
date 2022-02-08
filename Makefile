butterfly:
	mkdir \
	-pv \
	./src/base/build
	cd ./src/base/build; \
	$(CC) $(CFLAGS) -Wall -c ../gdata.c ../save_io.c ../record_io.c ../main.c \
	../wires.c ../joystick.c ../screen.c ../action.c
	cd ./src/base/build; \
	$(CC) $(CFLAGS) -Wall -lncurses -lm \
	-ltinfo \
	main.o gdata.o wires.o joystick.o \
	screen.o record_io.o save_io.o action.o -o ../../../butterfly-debug
	rm -r ./src/base/build
