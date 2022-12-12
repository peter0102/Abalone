#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "deplacement.h"
#include "allMove.h"
#include "ListeDeplacement1Bille.h"
#include "evaluate.h"

char* moves[200];

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

int miniMax(Plateau p,int depth,int alpha,int beta,bool isMaximizingPlayer){
	int lengthOfMoves=sizeof(moves)/sizeof(moves[0]); // taille de la liste de mouvements
    alpha=-INFINITY;
    beta=INFINITY;
    Move m;
    Move mback;
	if(depth==0) //S'arrête lorsque la profondeur souhaitée est atteinte
		return evaluate(p,CASE_NOIRE);
	    
	if(isMaximizingPlayer){ 
        int score=-INFINITY;
        for (int i=0;i<lengthOfMoves;i++) {
            char* charac=moves[i];
            translateMove(charac);
			m[0][0]=charac[0]-'@';
        	m[1][0]=charac[1]-'0';
        	m[0][1]=charac[3]-'@';
        	m[1][1]=charac[4]-'0';
            allMove(p,m,CASE_NOIRE,CASE_BLANCHE); // effectue un louvement
			int newScore=miniMax(p,depth-1,alpha,beta,false); // simule le tour de l'adversaire
        	mback[0][0]=m[0][1];
        	mback[1][0]=m[1][1];
        	mback[0][1]=m[0][0];
        	mback[1][1]=m[1][0];
            allMove(p,mback,CASE_NOIRE,CASE_BLANCHE); // on annule le mouvement joué
			if (newScore>score) score=newScore; // on prend le meilleur score
			if (alpha>newScore) alpha=newScore;
            if (alpha>=beta) break; // elagage
        }
		return score;
	}
	else {
        int score=INFINITY;
        for (int i=0;i<lengthOfMoves;i++) {
            char* charac=moves[i];
            translateMove(charac);
			m[0][0]=charac[0]-'@';
        	m[1][0]=charac[1]-'0';
        	m[0][1]=charac[3]-'@';
        	m[1][1]=charac[4]-'0';
            allMove(p,m,CASE_BLANCHE,CASE_NOIRE);
			int newScore=miniMax(p,depth-1,alpha,beta,true); // simule le tour de l'adversaire
        	mback[0][0]=m[0][1];
        	mback[1][0]=m[1][1];
        	mback[0][1]=m[0][0];
        	mback[1][1]=m[1][0];
            allMove(p,mback,CASE_BLANCHE, CASE_NOIRE);
			if (newScore<score) score=newScore; // on prend le moins bon score
			if (beta<newScore) alpha=newScore;
            if (beta<=alpha) break; // elagage
        }
		return score;
	}
}


char aiMove(Plateau p){
    int lengthOfMoves=sizeof(moves)/sizeof(moves[0]); // taille de la liste de mouvements
    Move m;
    Move mback; // pour "annuler" un mouvement
    Move bestMove; // prend le meilleur mouvement
    int score=-INFINITY;
    for(int i=0;i<lengthOfMoves;i++){
        char* charac=moves[i];
        translateMove(charac);
        m[0][0]=charac[0]-'@';
        m[1][0]=charac[1]-'0';
        m[0][1]=charac[3]-'@';
        m[1][1]=charac[4]-'0';
        allMove(p,m,CASE_NOIRE,CASE_BLANCHE);
        int newScore=miniMax(p,0,-INFINITY,INFINITY,false);
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
    Move m;
    char charac[1000]="";
    printf("Quel mouvement ? de type xx:xx\n");
    scanf("%s",charac);
    translateMove(charac);
    m[0][0]=charac[0]-'@';
    m[1][0]=charac[1]-'0';
    m[0][1]=charac[3]-'@';
    m[1][1]=charac[4]-'0';
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
