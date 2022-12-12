CC=gcc
CPPFLAGS= -DDEBUG
CFLAGS= -std=c99
LDFLAGS=
EXEC=abalone
all: $(EXEC)

abalone: interface.o deplacement.o
	$(CC) `pkg-config --cflags gtk+-3.0` -o $@ $^ `pkg-config --libs gtk+-3.0` $(LDFLAGS)

interface.o: interface.c interface.h ../deplacement.h
	$(CC) `pkg-config --cflags gtk+-3.0` -c -o $@ $< `pkg-config --libs gtk+-3.0`

deplacement.o: ../deplacement.c ../deplacement.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<
	
.PHONY: clean cleanall

clean:
	rm -f *.o

cleanall:
	rm -f *.o $(EXEC)
