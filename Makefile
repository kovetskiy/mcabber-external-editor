all:
	gcc editor.c -pedantic -Wall -Wextra \
		`pkg-config --cflags mcabber` -std=c99 \
		-shared -DMODULES_ENABLE  -fPIC\
		-o libeditor.so

install:
	install -D libeditor.so /usr/lib/mcabber/libeditor.so
