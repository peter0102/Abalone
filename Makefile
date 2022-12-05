CC=gcc
CPPFLAGS= -DDEBUG
CFLAGS= -std=c99
LDFLAGS=
EXEC=abalone
all: $(EXEC)

abalone: main.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

#Dépendances
main.o: main.c main.h

.PHONY: clean cleanall

clean:
	rm -f *.o

cleanall:
	rm -f *.o $(EXEC)
