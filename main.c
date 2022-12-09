#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "deplacement.h"
#include "allMove.h"
#include "ListeDeplacement1Bille.h"

#define MAX_I 10
#define MAX_J 10
#define INFINITY 147483648

#define CASE_VIDE '0'
#define CASE_NOIRE 'N'
#define CASE_BLANCHE 'B'

Plateau plateau = {
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE}
};

void display(Plateau p){
    for (int i=1; i<MAX_I-1; i++){
        for (int j=1; j<MAX_J-1; j++){
            if (p[i][j]==CASE_BLANCHE){
                printf("W | ");
            }
            if (p[i][j]==CASE_NOIRE){
                printf("B | ");
            }
            if (p[i][j]==CASE_VIDE){
                printf(". | ");
            }
        }
        printf("\n");
    }
}

int isItWin(Plateau p){
    int victory = 0;
        for (int i=0; i<=8; i++){
            if (p[0][i]!=0) {victory = 1;}
            if (p[i][9]!=0) {victory = 1;}
            if (p[9][(9-i)]!=0) {victory = 1;}
            if (p[(9-i)][0]!=0) {victory = 1;}
        }
    if (victory==1){
        printf("The game is won !\n\n");
    }
    return victory;
}

void resetBoard(Plateau p) {
    p=plateau;
}

int minimax(Plateau p,int depth,int alpha,int beta,bool isMaximizingPlayer){
	return 1;
}

char aiMove(Plateau p) {
    Move m;
	int score=-INFINITY;
	for (int i=1;i<MAX_I-1;i++) {
		for (int j=1;j<MAX_J-1;j++) {
			if (p[i][j]==CASE_NOIRE) {
                //possibleMove(p); // liste des mouvements possible
                m.x1=i;
                m.y1=j;
                m.x2=i-1;
                m.y2=j;
                allMove(p,m);
				int scoreMove=minimax(p,0,1,1,false);
				resetBoard(p);
				if (scoreMove>score) { // choisit le meilleur move en fonction du score
					score=scoreMove;
                    m.x1=i;
                    m.y1=j;
                    m.x2=i+1;
                    m.y2=j+1;
				}
			}
		}
	}
    char a=allMove(p,m);
    printf("\n\nRetour de la fonction allMove : %d\n",a);
}

char playerMove(Plateau p){
    char charac[1000]="";
    printf("Quel mouvement ? de type xx:xx\n");
    scanf("%s",charac);
    Move m=translate_move(charac);
    char a=allMove(p,m);
    printf("\n\nRetour de la fonction allMove : %d",a);
}

int main(int argc, char *argv[]) {
    int end=0;
    int turn_count=1;
    printf("Début du jeu\n");
    display(plateau);
    while (end!=1) {
		if(turn_count%2==1) { //turn_count = 1 --> current_player = 'B'
            printf("Tour %i\n",turn_count);
		    printf("C'est au tour des noirs(ia) de jouer\n");
		    aiMove(plateau);
            display(plateau);
            printf("\n*************************************\n");
		}
		else { //turn_count = 2 --> current_player = 'W'
            printf("Tour %i\n",turn_count);
	    	printf("C'est à votre tour de jouer\n");
		    playerMove(plateau);
            printf("\n*************************************\n");
		}
		turn_count++;
	}
}