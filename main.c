#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "global.h"

//types de mouvement
#define LINE_HORIZONTAL_RIGHT 'a'
#define LINE_HORIZONTAL_LEFT 'b'
#define LINE_VERTICAL_DOWN 'c'
#define LINE_VERTICAL_UP 'd'
#define LATERAL_TWO_HORIZONTAL 'e'
#define LATERAL_TWO_VERTICAL 'f'
#define LATERAL_THREE_VERTICAL_X0_DOWN 'g'
#define LATERAL_THREE_VERTICAL_X0_UP 'h'
#define LATERAL_THREE_HORIZONTAL_Y0_RIGHT 'i'
#define LATERAL_THREE_HORIZONTAL_Y0_LEFT 'j'
//gestion d'erreurs
#define ERROR 'x'
#define success 'l'
//définition des types
typedef char Board[10][10]; //caractères ASCII
typedef char Move[2][2]; //Mouvement {{x0,x1},{y0,y1}} valeurs numériques
typedef char Triple[2][3]; //coordonnées d'un joueur {{xj0,xj1,xj2},{yj0,yj1,yj2}} valeurs numériques

#include "main.h"
#include "ai.h"
#include "allMove.h"

void display(Board board){
    for (int i=1; i<MAX_I-1; i++){
        for (int j=1; j<MAX_J-1; j++){
            if (p[i][j]==WHITE){
                printf("W | ");
            }
            if (p[i][j]==BLACK){
                printf("B | ");
            }
            if (p[i][j]==EMPTY){
                printf(". | ");
            }
        }
        printf("\n");
    }
}

char isItWin(Board board){
    for(char i=0; i<=8; i++){
        if(p[0][i]!=0 || p[i][9]!=0 || p[9][(9-i)]!=0 || p[(9-i)][0]!=0){
            return(ERROR);
        }
    }
    return SUCCESS;
}

char playerMove(Plateau p){
    Move m;
    char charac[1000]="";
    printf("Quel mouvement ? de type xx:xx\n");
    scanf("%s",charac);
    translateMove(m,charac);
    char a=allMove(p,m,WHITE,BLACK);
}

int main(int argc, char *argv[]) {
    Board b = {
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, EMPTY},
            {EMPTY, EMPTY, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, EMPTY, EMPTY},
            {EMPTY, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}
    };
    char current_player;
    char other_player;
    int turn_count=1;
    printf("Début du jeu\n");
    display(plateau);
    while (isItWin(p)!=ERROR){
		if(turn_count%2==1) { //turn_count = 1 --> current_player = 'B'
            current_player = BLACK;
            other_player = WHITE;
            printf("Tour %i\n",turn_count);
		    printf("C'est au tour des noirs (IA) de jouer\n");
		    aiMove(plateau,current_player,other_player);
            display(plateau);
            printf("\n*************************************\n");
		}
		else { //turn_count = 2 --> current_player = 'W'
            current_player = WHITE;
            other_player = BLACK;
            printf("Tour %i\n",turn_count);
	    	printf("C'est à votre tour de jouer\n");
		    playerMove(plateau);
            display(plateau);
            printf("\n*************************************\n");
		}
		turn_count++;
	}
}
