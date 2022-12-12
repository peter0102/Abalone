CC=gcc
CPPFLAGS= -DDEBUG
CFLAGS= -std=c99
LDFLAGS=
EXEC=abalone
all: $(EXEC)

abalone: main.o deplacement.o allMove.o ListeDeplacement1Bille.o evaluate.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

#Dépendances
main.o: main.c main.h deplacement.h allMove.h ListeDeplacement1Bille.h evaluate.h
deplacement.o: deplacement.c deplacement.h
allMove.o: allMove.c allMove.h
ListeDeplacement1bille.o: ListeDeplacement1Bille.c ListeDeplacement1Bille.h allMove.h
evaluate.o: evaluate.c evaluate.h

.PHONY: clean cleanall

clean:
	rm -f *.o

cleanall:
	rm -f *.o $(EXEC)
