light: light.c
	$(CC) light.c $(CFLAGS) -lm -o light

install: light
	install light /usr/local/bin
