#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "global.h"

//La fonction victory prends un plateau en paramètre et vérifie l'existence d'un pion adverse dans la bordure: Fin de partie
//Le score de cette fonction d'évaluation est attribué lors de la fonction evaluate
int victory(Board b){
	int i=0,v=0;
	for(i=0;i<=8;i++){
		if(b[0][i]==WHITE || b[i][9]==WHITE || b[9][9-i]==WHITE || b[9-i][0]==WHITE){
			v==1;
			break;
		}
	}
	return v;
}

//La fonction victory prends un plateau en paramètre et vérifie l'existence d'un pion allié dans la bordure: Fin de partie
//Le score de cette fonction d'évaluation est attribué également lors de la fonction evaluate
int loss(Board b){
	int i=0,l=0;
	for(i=0;i<=8;i++){
		if(b[0][i]==BLACK || b[i][9]==BLACK || b[9][9-i]==BLACK || b[9-i][0]==BLACK){
			l==1;
			break;
		}
	}
	return l;
}

//La fonction density renvoie la moyenne de pions bar bloc de 3x3 multipliée bar un coefficient pour donner le score
int density(Board b,char currentPlayer,int alpha){
	int i=0,j=0;
	int t[]={0,0,0,0,0,0,0,0,0};
	for(i=1;i<=3;i++){
		for(j=1;j<=3;j++){
			if(b[i][j]==currentPlayer){
				t[0]++;
			}
		}
	}
	for(i=4;i<=6;i++){
		for(j=1;j<=3;j++){
			if(b[i][j]==currentPlayer){
				t[1]++;
			}
		}
	}
	for(i=6;i<=8;i++){
		for(j=1;j<=3;j++){
			if(b[i][j]==currentPlayer){
				t[2]++;
			}
		}
	}
	for(i=1;i<=3;i++){
		for(j=4;j<=6;j++){
			if(b[i][j]==currentPlayer){
				t[3]++;
			}
		}
	}
	for(i=4;i<=6;i++){
		for(j=4;j<=6;j++){
			if(b[i][j]==currentPlayer){
				t[4]++;
			}
		}
	}
	for(i=6;i<=8;i++){
		for(j=4;j<=6;j++){
			if(b[i][j]==currentPlayer){
				t[5]++;
			}
		}
	}
	for(i=1;i<=3;i++){
		for(j=6;j<=8;j++){
			if(b[i][j]==currentPlayer){
				t[6]++;
			}
		}
	}
	for(i=4;i<=6;i++){
		for(j=6;j<=8;j++){
			if(b[i][j]==currentPlayer){
				t[7]++;
			}
		}
	}
	for(i=6;i<=8;i++){
		for(j=6;j<=8;j++){
			if(b[i][j]==currentPlayer){
				t[8]++;
			}
		}
	}
	int max_count=0,most_frequent=0;
	for(i=0;i<9;i++){
		int count=0;
		for(j=0;j<9;j++){
			if(t[i]==t[j]){
				count++;
			}
		}
		
		if(count > max_count){
			max_count=count;
			most_frequent=t[i];
		}
	}
	return most_frequent*alpha;
}
// évalue la configuration du plateau en fonction des positions des billes
int distanceToCenter(Board b) { 
    int totalScore=0;
    Board score={ //tableau du score en fonction de la position
        {0,0,0,0,0,0,0,0,0,0},
        {0,-25,-25,-25,-25,-25,-25,-25,-25,0},
        {0,-25,2,2,2,2,2,2,-25,0},
        {0,-25,2,3,3,3,3,2,-25,0},
        {0,-25,2,3,4,4,3,2,-25,0},
        {0,-25,2,3,4,4,3,2,-25,0},
        {0,-25,2,3,3,3,3,2,-25,0},
        {0,-25,2,2,2,2,2,2,-25,0},
        {0,-25,-25,-25,-25,-25,-25,-25,-25,0},
        {0,0,0,0,0,0,0,0,0,0}
			};
    for(int i=1;i<MAX_I-1;i++) {
        for (int j=1;j<MAX_J-1;j++) {
            if (b[i][j]==WHITE) {
                totalScore+=score[i][j];
            }
            else if(b[i][j]==BLACK) {
                totalScore-=score[i][j];
            }
        }

    }
    return totalScore;

}
// compte le nombre d'ennemis proches (à 1,2 et 3 cases) et retourne un score
int areOpponentsNear(Board b){ 
    int score;
    for(int i=1;i<MAX_I-1;i++) {
        for (int j=1;j<MAX_J-1;j++) {
            if (b[i][j]==BLACK) {
                if (b[i+1][j]==WHITE) score+=-5; // -5 si adversaire au contact, -3 si à une case distante, -1 si à 2 cases distantes
                if (b[i][j+1]==WHITE) score+=-5;
                if (b[i+2][j]==WHITE) score+=-3;
                if (b[i][j+2]==WHITE) score+=-3;
                if (b[i+3][j]==WHITE) score+=-1;
                if (b[i][j+3]==WHITE) score+=-1;
                if (b[i-1][j]==WHITE) score+=-5;
                if (b[i][j-1]==WHITE) score+=-5;
                if (b[i-2][j]==WHITE) score+=-3;
                if (b[i][j-2]==WHITE) score+=-3;
                if (b[i-3][j]==WHITE) score+=-1;
                if (b[i][j-3]==WHITE) score+=-1;
            }
        }
    }
    return score;
}
// compte les voisins blancs sur l'axe X vertical
int countNeighborsXWhite(Board b,int i, int j){ 
    int neighbors=0;
    if (b[i][j]==WHITE) {
        for (int x=-2;x<0;x++) {
         if (b[i+x][j]==WHITE) neighbors++;
        }
        for (int x=1;x<3;x++) {
            if (b[i+x][j]==WHITE) neighbors++;
        }
    }
    return neighbors;
}
 // compte les voisins noirs sur l'axe X vertical
int countNeighborsXBlack(Board b,int i, int j){
    int neighbors=0;
    if (b[i][j]==BLACK) {
        for (int x=-2;x<0;x++) {
         if (b[i+x][j]==BLACK) neighbors++;
        }
        for (int x=1;x<3;x++) {
            if (b[i+x][j]==BLACK) neighbors++;
        }
    }
    return neighbors;
}
// compte les voisins blancs sur l'axe Y horizontal
int countNeighborsYWhite(Board b,int i, int j) { 
    int neighbors=0;
    if (b[i][j]==WHITE) {
        for (int y=-2;y<0;y++) {
            if (b[i][j+y]==WHITE) neighbors++;
        }
        for (int y=1;y<3;y++) {
            if (b[i][j+y]==WHITE) neighbors++;
        }
    }
    return neighbors;
}
// compte les voisins noirs sur l'axe Y horizontal
int countNeighborsYBlack(Board b,int i, int j) { 
    int neighbors=0;
    if (b[i][j]==BLACK) {
        for (int y=-2;y<0;y++) {
            if (b[i][j+y]==BLACK) neighbors++;
        }
        for (int y=1;y<3;y++) {
            if (b[i][j+y]==BLACK) neighbors++;
        }
    }
    return neighbors;
}
//retourne un score positif ou négatif si l'allié peut attaquer ou si l'ennemi peut attaquer
int canAttack(Board b){ 
    int score;
     for(int i=1;i<MAX_I-1;i++) {
        for (int j=1;j<MAX_J-1;j++) {
            if (b[i][j]==BLACK) {
                if (b[i+1][j]==WHITE) { // si bille adverse devant la bille alliée
                    int allyNeighborsX=countNeighborsXBlack(b,i,j);
                    int ennemyNeighborsX=countNeighborsXWhite(b,i+1,j);
                    if (allyNeighborsX<ennemyNeighborsX) score-=10; // si l'adversaire peut attaquer
                    else if(allyNeighborsX>ennemyNeighborsX) score+=10;
                }
                if (b[i][j+1]==BLACK) { // si bille adverse à gauche ou droite de la bille alliée
                    int allyNeighborsLine=countNeighborsYBlack(b,i,j);
                    int ennemyNeighborsLine=countNeighborsYWhite(b,i,j+1);
                    if (allyNeighborsLine<ennemyNeighborsLine) score-=10;
                    else if (allyNeighborsLine>ennemyNeighborsLine) score+=10;
                }
                if (b[i][j-1]==BLACK) {
                    int allyNeighborsLine=countNeighborsYBlack(b,i,j);
                    int ennemyNeighborsLine=countNeighborsYWhite(b,i,j-1);
                    if (allyNeighborsLine<ennemyNeighborsLine) score-=10;
                    else if (allyNeighborsLine>ennemyNeighborsLine) score+=10;
                }
                if (b[i-1][j]==WHITE) { // si bille adverse devant la bille alliée
                    int allyNeighborsX=countNeighborsXBlack(b,i,j);
                    int ennemyNeighborsX=countNeighborsXWhite(b,i-1,j);
                    if (allyNeighborsX<ennemyNeighborsX) score-=10; // si l'adversaire peut attaquer
                    else if(allyNeighborsX>ennemyNeighborsX) score+=10;
                }
            }
        }
    }
    return score;
}
// somme le score d'un plateau en fonction des différents paramètres pris en compte
int evaluate(Board b,char currentplayer){ 
	int utility=0;
	if(victory(b)==1){
		utility+=100;
	}
	if(loss(b)==1){
		utility+=-100;
	} 
	if(currentplayer==BLACK){
		utility += density(b,BLACK,1);
	}
	if(currentplayer==WHITE){
		utility -= density(b,BLACK,1);
	}
	utility+=areOpponentsNear(b)+canAttack(b)+distanceToCenter(b);
	return utility;
}


