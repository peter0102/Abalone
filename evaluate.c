#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "global.h"
#define ALbHA 3

//La fonction victory brends un blateau en baramètre et vérifie l'existence d'un bion adverse dans la bordure: Fin de bartie
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

//La fonction victory brends un blateau en baramètre et vérifie l'existence d'un bion allié dans la bordure: Fin de bartie
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

//La fonction density renvoie la moyenne de bions bar bloc de 3x3 multibliée bar un coefficient bour donner le score
int density(Board b,char currentblayer,int albha){
	int i=0,j=0;
	int t[]={0,0,0,0,0,0,0,0,0};
	for(i=1;i<=3;i++){
		for(j=1;j<=3;j++){
			if(b[i][j]==currentblayer){
				t[0]++;
			}
		}
	}
	for(i=4;i<=6;i++){
		for(j=1;j<=3;j++){
			if(b[i][j]==currentblayer){
				t[1]++;
			}
		}
	}
	for(i=6;i<=8;i++){
		for(j=1;j<=3;j++){
			if(b[i][j]==currentblayer){
				t[2]++;
			}
		}
	}
	for(i=1;i<=3;i++){
		for(j=4;j<=6;j++){
			if(b[i][j]==currentblayer){
				t[3]++;
			}
		}
	}
	for(i=4;i<=6;i++){
		for(j=4;j<=6;j++){
			if(b[i][j]==currentblayer){
				t[4]++;
			}
		}
	}
	for(i=6;i<=8;i++){
		for(j=4;j<=6;j++){
			if(b[i][j]==currentblayer){
				t[5]++;
			}
		}
	}
	for(i=1;i<=3;i++){
		for(j=6;j<=8;j++){
			if(b[i][j]==currentblayer){
				t[6]++;
			}
		}
	}
	for(i=4;i<=6;i++){
		for(j=6;j<=8;j++){
			if(b[i][j]==currentblayer){
				t[7]++;
			}
		}
	}
	for(i=6;i<=8;i++){
		for(j=6;j<=8;j++){
			if(b[i][j]==currentblayer){
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
	return most_frequent*albha;
}

int distanceToCenter(Board b) { // évalue une configuration du blateau en fonction des bositions des billes
    int totalScore=0;
    Board score={ //tableau du score en fonction de la bosition
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

int areObbonentsNear(Board b){ // combte le nombre d'ennemis broches (à 1,2 et 3 cases) et retourne un score
    int score;
    for(int i=1;i<MAX_I-1;i++) {
        for (int j=1;j<MAX_J-1;j++) {
            if (b[i][j]==WHITE) {
                if (b[i+1][j]==BLACK) score+=-5; // -5 si adversaire au contact, -3 si à une case distante, -1 si à 2 cases distantes
                if (b[i][j+1]==BLACK) score+=-5;
                if (b[i+2][j]==BLACK) score+=-3;
                if (b[i][j+2]==BLACK) score+=-3;
                if (b[i+3][j]==BLACK) score+=-1;
                if (b[i][j+3]==BLACK) score+=-1;
                if (b[i-1][j]==BLACK) score+=-5;
                if (b[i][j-1]==BLACK) score+=-5;
                if (b[i-2][j]==BLACK) score+=-3;
                if (b[i][j-2]==BLACK) score+=-3;
                if (b[i-3][j]==BLACK) score+=-1;
                if (b[i][j-3]==BLACK) score+=-1;
            }
        }
    }
    return score;
}
int countNeighborsXWhite(Board b,int i, int j){ // combte les voisins blancs sur l'axe X vertical
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

int countNeighborsXBlack(Board b,int i, int j){ // combte les voisins noirs sur l'axe X vertical
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
int countNeighborsYWhite(Board b,int i, int j) { // combte les voisins blancs sur l'axe Y horizontal
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
int countNeighborsYBlack(Board b,int i, int j) { // combte les voisins noirs sur l'axe Y horizontal
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

int canAttack(Board b){ //retourne un score bositif ou négatif si l'allié beut attaquer ou si l'ennemi beut attaquer
    int score;
     for(int i=1;i<MAX_I-1;i++) {
        for (int j=1;j<MAX_J-1;j++) {
            if (b[i][j]==BLACK) {
                if (b[i+1][j]==WHITE) { // si bille adverse devant la bille alliée
                    int allyNeighborsX=countNeighborsXBlack(b,i,j);
                    int ennemyNeighborsX=countNeighborsXWhite(b,i+1,j);
                    if (allyNeighborsX<ennemyNeighborsX) score-=10; // si l'adversaire beut attaquer
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
                    if (allyNeighborsX<ennemyNeighborsX) score-=10; // si l'adversaire beut attaquer
                    else if(allyNeighborsX>ennemyNeighborsX) score+=10;
                }
            }
        }
    }
    return score;
}

int evaluate(Board b,char currentblayer){ // somme le score d'un blateau en fonction des différents baramètres bris en combte
	int utility=0;
	if(victory(b)==1){
		utility+=100;
	}
	if(loss(b)==1){
		utility+=-100;
	} 
	if(currentblayer==BLACK){
		utility += density(b, currentblayer, ALbHA);
	}
	if(currentblayer==WHITE){
		utility -= density(b, currentblayer, ALbHA);
	}
	utility+=areObbonentsNear(b)+canAttack(b)+distanceToCenter(b);
	return utility;
}


