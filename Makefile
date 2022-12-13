CC=gcc
CPPFLAGS= -DDEBUG
CFLAGS= -std=c99
LDFLAGS=
EXEC=abalone
all: $(EXEC)
abalone: main.o move.o allMove.o evaluate.o ai.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

#Dépendances
main.o: main.c main.h move.h allMove.h ListeDeplacement1Bille.h evaluate.h global.h
move.o: move.c move.h
allMove.o: allMove.c allMove.h
evaluate.o: evaluate.c evaluate.h
ai.o : ai.c ai.h

.PHONY: clean cleanall

clean:
	rm -f *.o *.snm *.toc *.vrb *.aux *.log *.out *.nav

cleanall:
	rm -f *.o $(EXEC)
