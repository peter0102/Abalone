#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int coords_nbs_dictionary (char chr) {
    //Dictionnaire des coordonees numeriques (retourne -1 si le caractere est incorrect)
    switch (chr) {
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        default: return -1;
    }
}

int coords_ltr_dictionary (char chr) {
    //Dictionnaire des coordonees alphabetiques (retourne -1 si le caractere est incorrect)
    switch (chr) {
        case 'A': return 1;
        case 'B': return 2;
        case 'C': return 3;
        case 'D': return 4;
        case 'E': return 5;
        case 'F': return 6;
        case 'G': return 7;
        case 'H': return 8;
        default: return -1;
    }
}

Coords translate_coords(char* input) {
    //Traduit les coordonnes entrees (comme F6:E5) en index comme {x1=6, y1=6, x2=5, y2=5}
    //Retourne {-1,-1,-1,-1} en cas d'erreur
    Coords coords = {-1, -1, -1, -1};

    //Si la longueur de l'entree n'est pas 5, il y a erreur
    if (strlen(input) != 5) return coords;

    //Si le 3eme caractere n'est pas ':', il y a erreur
    if (input[2] != ':') return coords;

    int numbers[] = {
        coords_ltr_dictionary(input[0]),
        coords_nbs_dictionary(input[1]),
        coords_ltr_dictionary(input[3]),
        coords_nbs_dictionary(input[4])
    };

    for (int i = 0; i < 4; i++) {
        if (numbers[i] == -1) return coords;
    }
    coords.x1 = coords_ltr_dictionary(input[0]);
    coords.y1 = coords_nbs_dictionary(input[1]);
    coords.x2 = coords_ltr_dictionary(input[3]);
    coords.y2 = coords_nbs_dictionary(input[4]);
    return coords;
}

void print_coords(Coords coords) {
    printf("%i, %i\n%i, %i\n\n", coords.x1, coords.y1, coords.x2, coords.y2);
}

int main(int argc, char *argv[]) {
	int i=1;
	while(game!=0) {
		if(turn(i)==2) {
		printf("C'est au tour des noirs de jouer\n");


		}
		else {
		printf("C'est au tour des blancs de jouer \n");


		}
		i++;
	}

}

int turn(int current_turn){
	if (current_turn%2+1==2) return 2;
	else return 1;
}


int IsItWin(){
    int victory = 0;
        for (int i=0; i<=8; i++){
            if (Plateau[0][i]!=0) {victory = 1;}
            if (Plateau[i][9]!=0) {victory = 1;}
            if (Plateau[9][(9-i)]!=0) {victory = 1;}
            if (Plateau[(9-i)][0]!=0) {victory = 1;}
        }
    if (victory==1){
        printf("The game is won !\n\n");
    }
    return 0;
}
