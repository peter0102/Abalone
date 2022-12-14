
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "global.h"
#include "global.c"
#include "move.h"
#include "move.c"
#include "allMove.h"
#include "allMove.c"

#include "ListeDeplacementsString.h"
#include "ListeDeplacementsString.c"

char* TraduireV2(char* liste, int taille){

    char* m=malloc(taille);
    m=strncat(m, liste, taille);

    return(m);
}


int main(){

    char current_player;

    current_player=WHITE;

    char* resultat;

    resultat = FindAllMoves(current_player);

    printf(" Le resultat est %s\n\n", resultat);

// Le programme pour decouper la chaine en un array de chaines de taille 5

    int List_Length = strlen(resultat)/6;
	printf("Taille de la liste : %i \n", List_Length);
	char delim[] = ";";
	int tailleStrings=5; // La taille des strings à ranger. Ici, un Move est de taille 5
	char ListeStrings[List_Length][tailleStrings];
	char *tampon = strtok(resultat, delim);

	for(int i=0;i<List_Length;i++)
	{
		strcpy(ListeStrings[i],tampon);
		printf(" %s / ", ListeStrings[i]);

		tampon = strtok(NULL, delim);
		if((i+1)%5==0){
                printf("\n");
		}
	}

	printf("\n\n");

    return(0);
}
