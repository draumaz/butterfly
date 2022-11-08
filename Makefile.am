SUBDIRS = src/base src/header
AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = butterfly
butterfly_LDADD = -lm -lncurses

butterfly_SOURCES = \
	src/base/main.c \
	src/base/action.c \
	src/base/gdata.c \
	src/base/joystick.c \
	src/base/record_io.c \
	src/base/save_io.c \
	src/base/screen.c \
	src/base/wires.c \
	src/header/action.h \
	src/header/gdata.h \
	src/header/joystick.h \
	src/header/record_io.h \
	src/header/save_io.h \
	src/header/screen.h \
	src/header/wires.h \
	src/header/defz.h
