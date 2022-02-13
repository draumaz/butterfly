CM = cd ./src/base/build

butterfly:
	mkdir \
	-pv \
	./src/base/build
	$(CM) && $(CC) $(CFLAGS) -Wall -c ../gdata.c
	$(CM) && $(CC) $(CFLAGS) -Wall -c ../save_io.c
	$(CM) && $(CC) $(CFLAGS) -Wall -c ../record_io.c
	$(CM) && $(CC) $(CFLAGS) -Wall -c ../wires.c
	$(CM) && $(CC) $(CFLAGS) -Wall -c ../joystick.c
	$(CM) && $(CC) $(CFLAGS) -Wall -c ../screen.c
	$(CM) && $(CC) $(CFLAGS) -Wall -c ../action.c
	$(CM) && $(CC) $(CFLAGS) -Wall -c ../main.c
	$(CM) && $(CC) $(CFLAGS) -Wall -lncurses -lm \
	-ltinfo \
	main.o gdata.o wires.o joystick.o screen.o record_io.o save_io.o action.o \
	-o ../../../butterfly-debug
	rm -r ./src/base/build
