#include <stdbool.h>
#include <stdio.h>
#include "global.h"
#include "evaluate.h"
#include "move.h"
#include "allMove.h"

char* moves[]={"H1:G1","H2:F2","G2:F2","G3:F3","H3:F3","G4:F4","H4:F4","G5:G5","H5:F5","G6:F6","H6:F6","G7:F7","H7:F7","H8:G8"};

/*fonction minimax, teste toutes les possibilités de mouvement possible pour une configuration du plateau 
et simule celles de l'adversaire jusqu'à une certaine profondeur*/
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
            translateMove(m,charac);
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
            translateMove(m,charac);
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

//fonction de déplacement pour les pions de l'IA, choisissant le "meilleur" mouvement, selon les fonctions heuristiques
char aiMove(Plateau p,char current_player, char other_player){
    int lengthOfMoves=sizeof(moves)/sizeof(moves[0]); // taille de la liste de mouvements
    Move m;
    Move mback; // pour "annuler" un mouvement
    Move bestMove; // prend le meilleur mouvement
    int score=-INFTY;
    for(int i=0;i<lengthOfMoves;i++){
        char* charac=moves[i];
        translateMove(m,charac);
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
            bestMove[0][0]=m[0][0];
            bestMove[1][0]=m[1][0];
            bestMove[0][1]=m[0][1];
            bestMove[1][1]=m[1][1];
            }
    }
    }
    allMove(p,bestMove,current_player,other_player); 
}
