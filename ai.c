#include <stdbool.h>
#include <stdio.h>
#include "global.h"
#include "evaluate.h"
#include "move.h"
#include "allMove.h"
#include "ai.h"
#include "lmove.h"
#include "main.h"

char* moves[]={"H1:G1","H2:F2","G2:F2","G3:F3","H3:F3","G4:F4","H4:F4","G5:G5","H5:F5","G6:F6","H6:F6","G7:F7","H7:F7","H8:G8"};

/*fonction minimax, teste toutes les possibilités de mouvement possible pour une configuration du plateau pour un joueur,
et simule celles de l'adversaire jusqu'à une certaine profondeur, 1 pour l'instant*/
int miniMax(Board board,int depth,int alpha,int beta,bool isMaximizingPlayer, char current_player, char other_player){
    alpha=-INFTY;
    beta=INFTY;
    Move m;
    Move mback;
    Move list[56];
	if(depth==0 || isItWin(board)==SUCCESS){ //S'arrête lorsque la profondeur souhaitée est atteinte ou si un mouvement fait gagner la partie
		return evaluate(board,current_player,other_player);
	}
	    if(isMaximizingPlayer){
        int score=-INFTY;
        lmove(board,current_player,list);
        for (int i=0;i<56;i++) {
            allMove(board,list[i],current_player,other_player); // effectue un mouvement
			int newScore=miniMax(board,depth-1,alpha,beta,false, current_player, other_player); // simule le tour de l'adversaire
            mback[0][0]=list[i][0][1];
            mback[1][0]=list[i][1][1];
            mback[0][1]=list[i][0][0];
            mback[1][1]=list[i][1][0];
            allMove(board,mback,current_player,other_player); // on annule le mouvement joué
			if (newScore>score) score=newScore; // on choisit le mouvement donnant le plateau au meilleur score
			if (alpha>newScore) alpha=newScore;
            if (alpha>=beta) break; // elagage
        }
		return score;

	}
	else {
        int score=INFTY;
        lmove(board,other_player,list);
        for (int i=0;i<56;i++) {
            allMove(board,list[i],other_player,current_player);
			int newScore=miniMax(board,depth-1,alpha,beta,true, current_player, other_player); // simule le tour de l'adversaire
            mback[0][0]=list[i][0][1];
            mback[1][0]=list[i][1][1];
            mback[0][1]=list[i][0][0];
            mback[1][1]=list[i][1][0];
            allMove(board,mback,other_player, current_player);
			if (newScore<score) score=newScore; // on prend le moins bon score
			if (beta<newScore) alpha=newScore;
            if (beta<=alpha) break; // elagage
        }
		return score;
	}
}

//fonction de déplacement pour les pions de l'IA, choisissant le "meilleur" mouvement, selon les fonctions heuristiques
void aiBestMove(Move move, Board board, char current_player, char other_player){
    Move m;
    Move mback; // pour "annuler" un mouvement
    Move bestMove; // prend le meilleur mouvement
    int score=-INFTY;
    Move list[56];
    lmove(board,current_player,list);
    for(int i=0;i<56;i++){
        allMove(board,list[i],current_player,other_player);
        display(board);
        int newScore=miniMax(board,1,-INFTY,INFTY,false, current_player, other_player);
        mback[0][0]=list[i][0][1];
        mback[1][0]=list[i][1][1];
        mback[0][1]=list[i][0][0];
        mback[1][1]=list[i][1][0];
        allMove(board,mback,current_player,other_player);
        if (newScore>score) {
            score=newScore;
            bestMove[0][0]=list[i][0][0];
            bestMove[1][0]=list[i][1][0];
            bestMove[0][1]=list[i][0][1];
            bestMove[1][1]=list[i][1][1];
        }
    }
    move[0][0] = bestMove[0][0]; move[0][1] = bestMove[0][1];
    move[1][0] = bestMove[1][0]; move[1][1] = bestMove[1][1];
    return;
}