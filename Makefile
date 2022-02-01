butterfly:
	cd ./src/base; mkdir -pv build; cd build; \
        $(CC) $(CFLAGS) -Wall -c -lm ../gdata.c; \
        $(CC) $(CFLAGS) -Wall -c ../save_io.c ../record_io.c ../main.c; \
        $(CC) $(CFLAGS) -Wall -c -lncurses -ltinfo ../wires.c ../joystick.c ../screen.c ../action.c
	mv ./src/base/build ./build
	cd build; $(CC) $(CFLAGS) -Wall -lncurses -ltinfo -lm \
        main.o gdata.o wires.o joystick.o screen.o record_io.o save_io.o action.o \
        -o ../butterfly-debug
	rm -r ./build
