CC=gcc
CPPFLAGS= -DDEBUG
CFLAGS= -std=c99
LDFLAGS=
EXEC=abalone
all: $(EXEC)

abalone: interface.o move.o logicMain.o ai.o allMove.o evaluate.o global.o initCheck.o client.o server.o listMove.o
	$(CC) `pkg-config --cflags gtk+-3.0` -o $@ $^ `pkg-config --libs gtk+-3.0` $(LDFLAGS)

logicMain.o: src/gtk_interface/logicMain.c src/gtk_interface/logicMain.h src/global.h src/ai.h src/allMove.h src/move.h src/gtk_interface/interface.h src/initCheck.h
	$(CC) `pkg-config --cflags gtk+-3.0` -c -o $@ $< `pkg-config --libs gtk+-3.0`

interface.o: src/gtk_interface/interface.c src/gtk_interface/interface.h src/global.h src/gtk_interface/logicMain.h src/move.h src/initCheck.h
	$(CC) `pkg-config --cflags gtk+-3.0` -c -o $@ $< `pkg-config --libs gtk+-3.0`

global.o: src/global.c src/global.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

move.o: src/move.c src/move.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

initCheck.o: src/initCheck.c src/initCheck.h src/client.h src/server.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

client.o: src/client.c src/client.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

server.o: src/server.c src/server.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

ai.o: src/ai.c src/ai.h src/global.h src/evaluate.h src/allMove.h src/move.h src/listMove.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

allMove.o: src/allMove.c src/allMove.h src/gtk_interface/interface.h
	$(CC) `pkg-config --cflags gtk+-3.0` -c -o $@ $< `pkg-config --libs gtk+-3.0`

evaluate.o: src/evaluate.c src/evaluate.h src/global.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

listMove.o: src/listMove.c src/listMove.h src/global.h src/allMove.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

.PHONY: clean cleanall

clean:
	rm -f *.o

cleanall:
	rm -f *.o $(EXEC)

docs:
	doxygen doxygen/Doxyfile
	ln -s doxygen/html/index.html Documentation