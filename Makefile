SRC_PFX = "./src/base"
BUILD_PFX = "./build"

all: dir_create obj_build compile cleanup

dir_create:
	@mkdir \
	-pv \
	$(BUILD_PFX)

obj_build:
	$(CC) $(CFLAGS) -Wall -c $(SRC_PFX)/main.c -o $(BUILD_PFX)/main.o
	$(CC) $(CFLAGS) -Wall -c $(SRC_PFX)/wires.c -o $(BUILD_PFX)/wires.o
	$(CC) $(CFLAGS) -Wall -c $(SRC_PFX)/joystick.c -o $(BUILD_PFX)/joystick.o
	$(CC) $(CFLAGS) -Wall -c $(SRC_PFX)/save_io.c -o $(BUILD_PFX)/save_io.o
	$(CC) $(CFLAGS) -Wall -c $(SRC_PFX)/record_io.c -o $(BUILD_PFX)/record_io.o
	$(CC) $(CFLAGS) -Wall -c $(SRC_PFX)/gdata.c -o $(BUILD_PFX)/gdata.o
	$(CC) $(CFLAGS) -Wall -c $(SRC_PFX)/action.c -o $(BUILD_PFX)/action.o
	$(CC) $(CFLAGS) -Wall -c $(SRC_PFX)/screen.c -o $(BUILD_PFX)/screen.o

compile:
	@echo "creating binary"
	@cd $(BUILD_PFX) && $(CC) $(CFLAGS) \
		main.o wires.o joystick.o save_io.o record_io.o gdata.o action.o screen.o \
	-o ../butterfly-debug \
	-lncurses -lm \
	-ltinfo
	@echo "-> ./butterfly-debug"

cleanup:
	rm -rf $(BUILD_PFX)
