#include "global.h"
#include <stdbool.h>


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
            translateMove(charac);
			m[0][0]=charac[0]-'@';
        	m[1][0]=charac[1]-'0';
        	m[0][1]=charac[3]-'@';
        	m[1][1]=charac[4]-'0';
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
    display(p);
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
            bestMove[0][1]=m[0][1];
            bestMove[1][0]=m[1][0];
            bestMove[1][1]=m[1][1];
            }
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
    display(p);
    char a=allMove(p,m,WHITE,BLACK);
    display(p);
}