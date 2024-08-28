CFLAGS = -lm -ansi -static -s -Ofast -march=native

light: light.c
	$(CC) light.c $(CFLAGS) -o light

install: light
	install light /usr/local/bin
