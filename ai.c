#include <stdbool.h>
#include <stdio.h>
#include "global.h"
#include "evaluate.h"
#include "move.h"
#include "allMove.h"

int miniMax(Plateau p,int depth,int alpha,int beta,bool isMaximizingPlayer){
	int lengthOfMoves=sizeof(moves)/sizeof(moves[0]); // taille de la liste de mouvements
    alpha=-INFTY;
    beta=INFTY;
    Move m;
    Move mback;
	if(depth==0){ //S'arrête lorsque la profondeur souhaitée est atteinte
		return evaluate(p,BLACK);
	}
	    
	if(isMaximizingPlayer){ 
        int score=-INFTY;
        for (int i=0;i<lengthOfMoves;i++) {
            char* charac=moves[i];
            m=translateMove(charac);
            allMove(p,m,BLACK,WHITE); // effectue un mouvement
			int newScore=miniMax(p,depth-1,alpha,beta,false); // simule le tour de l'adversaire
        	mback[0][0]=m[0][1];
        	mback[1][0]=m[1][1];
        	mback[0][1]=m[0][0];
        	mback[1][1]=m[1][0];
            allMove(p,mback,BLACK,WHITE); // on annule le mouvement joué
			if (newScore>score) score=newScore; // on choisit le mouvement donnant le meilleur score
			if (alpha>newScore) alpha=newScore;
            if (alpha>=beta) break; // elagage
        }
		return score;

	}
	else {
        int score=INFTY;
        for (int i=0;i<lengthOfMoves;i++) {
            char* charac=moves[i];
            m=translateMove(charac);
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


char aiMove(Plateau p,char current_player, char other_player){
    int lengthOfMoves=sizeof(moves)/sizeof(moves[0]); // taille de la liste de mouvements
    Move m;
    Move mback; // pour "annuler" un mouvement
    Move bestMove; // prend le meilleur mouvement
    int score=-INFTY;
    for(int i=0;i<lengthOfMoves;i++){
        char* charac=moves[i];
        m=translateMove(charac);
        if (p[m[0][1]][m[1][1]]!=BLACK) {
        allMove(p,m,BLACK,WHITE);
        int newScore=miniMax(p,2,-INFTY,INFTY,false);
        mback[0][0]=m[0][1];
        mback[1][0]=m[1][1];
        mback[0][1]=m[0][0];
        mback[1][1]=m[1][0];
        allMove(p,mback,BLACK,WHITE);
            if (newScore>score) {
            score=newScore;
            bestMove=m;
            }
        }
    }
    allMove(p,bestMove,current_player,other_player);
}