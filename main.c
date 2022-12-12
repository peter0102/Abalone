#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "global.h"

//types de mouvement
#define LINE_HORIZONTAL_RIGHT 'a'
#define line_horizontal_left 'b'
#define line_vertical_down 'c'
#define line_vertical_up 'd'
#define lateral_two_horizontal 'e'
#define lateral_two_vertical 'f'
#define lateral_three_vertical_x0_down 'g'
#define lateral_three_vertical_x0_up 'h'
#define lateral_three_horizontal_y0_right 'i'
#define lateral_three_horizontal_y0_left 'j'
//gestion d'erreurs
#define ERROR 'x'
#define success 'l'
//définition des types
typedef char Plateau[10][10]; //caractères ASCII
typedef char Move[2][2]; //Mouvement {{x0,x1},{y0,y1}} valeurs numériques
typedef char Triple[2][3]; //coordonnées d'un joueur {{xj0,xj1,xj2},{yj0,yj1,yj2}} valeurs numériques

#include "main.h"
#include "deplacement.h"
#include "allMove.h"
#include "ListeDeplacement1Bille.h"
#include "evaluate.h"

char* moves[200];

Plateau plateau = {
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

void display(Plateau p){
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
    alpha=-INFTY;
    beta=INFTY;
    Move m;
    Move mback;
	if(depth==0) //S'arrête lorsque la profondeur souhaitée est atteinte
		return evaluate(p,BLACK);
	    
	if(isMaximizingPlayer){ 
        int score=-INFTY;
        for (int i=0;i<lengthOfMoves;i++) {
            char* charac=moves[i];
            translateMove(charac);
			m[0][0]=charac[0]-'@';
        	m[1][0]=charac[1]-'0';
        	m[0][1]=charac[3]-'@';
        	m[1][1]=charac[4]-'0';
            allMove(p,m,BLACK,WHITE); // effectue un louvement
			int newScore=miniMax(p,depth-1,alpha,beta,false); // simule le tour de l'adversaire
        	mback[0][0]=m[0][1];
        	mback[1][0]=m[1][1];
        	mback[0][1]=m[0][0];
        	mback[1][1]=m[1][0];
            allMove(p,mback,BLACK,WHITE); // on annule le mouvement joué
			if (newScore>score) score=newScore; // on prend le meilleur score
			if (alpha>newScore) alpha=newScore;
            if (alpha>=beta) break; // elagage
        }
		return score;
	}
	else {
        int score=INFTY;
        for (int i=0;i<lengthOfMoves;i++) {
            char* charac=moves[i];
            translateMove(charac);
			m[0][0]=charac[0]-'@';
        	m[1][0]=charac[1]-'0';
        	m[0][1]=charac[3]-'@';
        	m[1][1]=charac[4]-'0';
            allMove(p,m,WHITE,BLACK);
			int newScore=miniMax(p,depth-1,alpha,beta,true); // simule le tour de l'adversaire
        	mback[0][0]=m[0][1];
        	mback[1][0]=m[1][1];
        	mback[0][1]=m[0][0];
        	mback[1][1]=m[1][0];
            allMove(p,mback,WHITE, BLACK);
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
    int score=-INFTY;
    for(int i=0;i<lengthOfMoves;i++){
        char* charac=moves[i];
        translateMove(charac);
        m[0][0]=charac[0]-'@';
        m[1][0]=charac[1]-'0';
        m[0][1]=charac[3]-'@';
        m[1][1]=charac[4]-'0';
        allMove(p,m,BLACK,WHITE);
        int newScore=miniMax(p,0,-INFTY,INFTY,false);
        mback[0][0]=m[0][1];
        mback[1][0]=m[1][1];
        mback[0][1]=m[0][0];
        mback[1][1]=m[1][0];
        allMove(p,mback,BLACK,WHITE);
            if (newScore>score) {
            score=newScore;
            bestMove[0][0]=m[0][0];
            bestMove[0][1]=m[0][1];
            bestMove[1][0]=m[1][0];
            bestMove[1][1]=m[1][1];
            }
        }
    allMove(p,bestMove,BLACK,WHITE);
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
    char a=allMove(p,m,WHITE,BLACK);
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
