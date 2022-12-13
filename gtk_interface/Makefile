CC=gcc
CPPFLAGS= -DDEBUG
CFLAGS= -std=c99
LDFLAGS=
EXEC=abalone
all: $(EXEC)

abalone: interface.o move.o logic_main.o ai.o allMove.o evaluate.o global.o
	$(CC) `pkg-config --cflags gtk+-3.0` -o $@ $^ `pkg-config --libs gtk+-3.0` $(LDFLAGS)

interface.o: interface.c interface.h ../global.h logic_main.h ../move.h
	$(CC) `pkg-config --cflags gtk+-3.0` -c -o $@ $< `pkg-config --libs gtk+-3.0`

logic_main.o: logic_main.c logic_main.h ../global.h ../ai.h ../allMove.h ../move.h interface.h
	$(CC) `pkg-config --cflags gtk+-3.0` -c -o $@ $< `pkg-config --libs gtk+-3.0`

move.o: ../move.c ../move.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

global.o: ../global.c ../global.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

ai.o: ../ai.c ../ai.h ../global.h ../evaluate.h ../allMove.h ../move.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

allMove.o: ../allMove.c ../allMove.h interface.h
	$(CC) `pkg-config --cflags gtk+-3.0` -c -o $@ $< `pkg-config --libs gtk+-3.0`

evaluate.o: ../evaluate.c ../evaluate.h ../global.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

.PHONY: clean cleanall

clean:
	rm -f *.o

cleanall:
	rm -f *.o $(EXEC)
