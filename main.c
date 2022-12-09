#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "deplacement.h"
#include "allMove.h"
#include "ListeDeplacement1Bille.h"
#include "evaluate.h"

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

int minimax(Plateau p,int depth,int alpha,int beta,bool isMaximizingPlayer){
	return 1;
}

char aiMove(Plateau p){
    int lengthOfMoves=sizeof(moves)/sizeof(moves[0]); // taille de la liste de mouvements
    Move m;
    Move mback; // pour "annuler" un mouvement
    Move bestMove; // prend le meilleur mouvement
    int score=-INFINITY;
    for(int i=0;i<lengthOfMoves;i++){
        char* charac=moves[i];
        m=translate_move(charac);
        allMove(p,m,CASE_NOIRE,CASE_BLANCHE);
        int newScore=minimax(p,0,-INFINITY,INFINITY,false);
        mback[0][0]=m[0][1];
        mback[1][0]=m[1][1];
        mback[0][1]=m[0][0];
        mback[1][1]=m[1][0];
        allMove(p,mback,CASE_NOIRE,CASE_BLANCHE);
            if (newScore>score) {
            score=newScore;
            bestMove[0][0]=m[0][0];
            bestMove[0][1]=m[0][1];
            bestMove[1][0]=m[1][0];
            bestMove[1][1]=m[1][1];
            }
        }
    allMove(p,bestMove,CASE_NOIRE,CASE_BLANCHE);
}


char playerMove(Plateau p){
    char charac[1000]="";
    printf("Quel mouvement ? de type xx:xx\n");
    scanf("%s",charac);
    Move m=translate_move(charac);
    char a=allMove(p,m,CASE_BLANCHE,CASE_NOIRE);
    printf("\n\nRetour de la fonction allMove : %d",a);
}

int main(int argc, char *argv[]) {
    char current_player;
    char other_player;
    int win_condition=isItWin(plateau);
    int turn_count=1;
    printf("Début du jeu\n");
    display(plateau);
    while (win_condition !=1) {
		if(turn_count%2==1) { //turn_count = 1 --> current_player = 'B'
            current_player = 'B';
            other_player = 'W';
            printf("Tour %i\n",turn_count);
		    printf("C'est au tour des noirs (IA) de jouer\n");
		    aiMove(plateau);
            display(plateau);
            printf("\n*************************************\n");
		}
		else { //turn_count = 2 --> current_player = 'W'
            current_player = 'W';
            other_player = 'B';
            printf("Tour %i\n",turn_count);
	    	printf("C'est à votre tour de jouer\n");
		    playerMove(plateau);
            printf("\n*************************************\n");
		}
		turn_count++;
	}
}