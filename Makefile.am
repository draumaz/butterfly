SUBDIRS = src/base src/header
AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = butterfly
butterfly_LDADD = -lm -lncurses
butterfly_SOURCES = \
	src/base/main.c \
	src/base/action.c \
	src/header/action.h \
	src/base/gdata.c \
	src/header/gdata.h \
	src/base/joystick.c \
	src/header/joystick.h \
	src/base/record_io.c \
	src/header/record_io.h \
	src/base/save_io.c \
	src/header/save_io.h \
	src/base/screen.c \
	src/header/screen.h \
	src/base/wires.c \
	src/header/wires.h \
	src/header/defz.h
