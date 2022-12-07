#include <stdio.h>
#define MAX_I 10
#define MAX_J 10
#include <stdbool.h>
#define INFINITY 147483648 

#define CASE_VIDE '0'
#define CASE_NOIRE 'N'
#define CASE_BLANCHE 'B'

typedef char Plateau[MAX_I][MAX_J];

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
    for (int i=0; i<MAX_I; i++){
        for (int j=0; j<MAX_J; j++){
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


int minimax(Plateau p,int depth,int alpha,int beta,bool isMaximizingPlayer){
	if(depth==0){
		return 1;
	}
	
	if(isMaximizingPlayer){ //ai qui joue le meilleur move
		int score=-INFINITY;
		for(int i=1;i<MAX_I-1;i++) {
			for(int j=1;j<MAX_J-1;j++) {// on parcourt tous les move possibles
			if (movePossible) { // si le move est possible
				p[i][j]=ai; //ai = valeur pour l'ia
				int newScore=minimax(p,depth+1,alpha,beta,false); // simule le tour de l'adversaire
				p[i][j]=0;
				if (newScore>score) {
					score=newScore; // on prend le meilleur score
					if (score>=beta) { // elagage
					return score;
					}
					else if (alpha>score) {
						alpha=score;
						}
					}
				}
			}
		}
		return score;
	}
	else {
		int score=INFINITY;
		for(int i=1;i<MAX_I-1;i++) {
			for(int j=1;j<MAX_J-1;j++) {// on parcourt tous les move possibles
			if (movePossible) { // si le move est possible
				p[i][j]=ai; //ai = valeur pour l'ia
				int newScore=minimax(p,depth+1,alpha,beta,true); // simule le tour de l'adversaire
				p[i][j]=0;
				if (newScore<score) {
					score=newScore; // on prend le meilleur score
					if (score>=alpha) { // elagage
					return score;
					}
					else if (beta>score) {
						beta=score;
						}
					}
				}
			}
		}
		return score;
	}
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
                m.x2=i+1;
                m.y2=j;
                move(p,m);
		int scoreMove=minimax(p,5,1,1,false);
		resetBoard(p);
		if (scoreMove>score) { // choisit le meilleur move en fonction du score
			score=scoreMove;
                    m.x1=i; // temporaire, fait jouer le prochain mouvement possible a l'ia
                    m.y1=j;
                    m.x2=i+1;
                    m.y2=j+1;
				}
			}
		}
	}
    move(p,m);
}

char playerMove(Plateau p){ // mouvement joueur
    Move m;
    printf("Quel mouvement ? ");
    scanf("%c %c %c %c",&m.x1,&m.y1,&m.x2,&m.y2);
    move(p,m);
}
