#include <stdio.h>
#include <stdlib.h>
#define ALPHA 3
#define MAX_I 10
#define MAX_J 10
#define CASE_VIDE '0'
#define CASE_NOIRE 'N'
#define CASE_BLANCHE 'B'

typedef char Plateau[MAX_I][MAX_J];

int victory(Plateau p){
	int i=0,v=0;
	for(i=0;i<=8;i++){
		if(p[0][i]==CASE_BLANCHE || p[i][9]==CASE_BLANCHE || p[9][9-i]==CASE_BLANCHE || p[9-i][0]==CASE_BLANCHE){
			v==1;
			break;
		}
	}
	return v;
}

int loss(Plateau p){
	int i=0,l=0;
	for(i=0;i<=8;i++){
		if(p[0][i]==CASE_NOIRE || p[i][9]==CASE_NOIRE || p[9][9-i]==CASE_NOIRE || p[9-i][0]==CASE_NOIRE){
			l==1;
			break;
		}
	}
	return l;
}

int density(Plateau p,char currentPlayer,int alpha){
	int i=0,j=0;
	int t[]={0,0,0,0,0,0,0,0,0};
	for(i=1;i<=3;i++){
		for(j=1;j<=3;j++){
			if(p[i][j]==currentPlayer){
				t[0]++;
			}
		}
	}
	for(i=4;i<=6;i++){
		for(j=1;j<=3;j++){
			if(p[i][j]==currentPlayer){
				t[1]++;
			}
		}
	}
	for(i=6;i<=8;i++){
		for(j=1;j<=3;j++){
			if(p[i][j]==currentPlayer){
				t[2]++;
			}
		}
	}
	for(i=1;i<=3;i++){
		for(j=4;j<=6;j++){
			if(p[i][j]==currentPlayer){
				t[3]++;
			}
		}
	}
	for(i=4;i<=6;i++){
		for(j=4;j<=6;j++){
			if(p[i][j]==currentPlayer){
				t[4]++;
			}
		}
	}
	for(i=6;i<=8;i++){
		for(j=4;j<=6;j++){
			if(p[i][j]==currentPlayer){
				t[5]++;
			}
		}
	}
	for(i=1;i<=3;i++){
		for(j=6;j<=8;j++){
			if(p[i][j]==currentPlayer){
				t[6]++;
			}
		}
	}
	for(i=4;i<=6;i++){
		for(j=6;j<=8;j++){
			if(p[i][j]==currentPlayer){
				t[7]++;
			}
		}
	}
	for(i=6;i<=8;i++){
		for(j=6;j<=8;j++){
			if(p[i][j]==currentPlayer){
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

int distanceToCenter(Plateau p) {
    int totalScore=0;
    Plateau score={ //tableau du score en fonction de la position
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
            if (p[i][j]==CASE_BLANCHE) {
                totalScore+=score[i][j];
            }
            else if(p[i][j]==CASE_NOIRE) {
                totalScore-=score[i][j];
            }
        }

    }
    return totalScore;

}

int areOpponentsNear(Plateau p){ // compte le nombre d'ennemis proches et retourne un score
    int score;
    for(int i=1;i<MAX_I-1;i++) {
        for (int j=1;j<MAX_J-1;j++) {
            if (p[i][j]==CASE_BLANCHE) {
                if (p[i+1][j]==CASE_NOIRE) score+=-5;
                if (p[i][j+1]==CASE_NOIRE) score+=-5;
                if (p[i+2][j]==CASE_NOIRE) score+=-3;
                if (p[i][j+2]==CASE_NOIRE) score+=-3;
                if (p[i+3][j]==CASE_NOIRE) score+=-1;
                if (p[i][j+3]==CASE_NOIRE) score+=-1;
                if (p[i-1][j]==CASE_NOIRE) score+=-5;
                if (p[i][j-1]==CASE_NOIRE) score+=-5;
                if (p[i-2][j]==CASE_NOIRE) score+=-3;
                if (p[i][j-2]==CASE_NOIRE) score+=-3;
                if (p[i-3][j]==CASE_NOIRE) score+=-1;
                if (p[i][j-3]==CASE_NOIRE) score+=-1;
            }
        }
    }
    return score;
}

int countNeighborsXBlack(Plateau p,int i, int j){
    int neighbors=0;
    if (p[i][j]==CASE_NOIRE) {
        for (int x=-2;x<0;x++) {
         if (p[i+x][j]==CASE_NOIRE) neighbors++;
        }
        for (int x=1;x<3;x++) {
            if (p[i+x][j]==CASE_NOIRE) neighbors++;
        }
    }
    return neighbors;
}
int countNeighborsYWhite(Plateau p,int i, int j) {
    int neighbors=0;
    if (p[i][j]==CASE_BLANCHE) {
        for (int y=-2;y<0;y++) {
            if (p[i][j+y]==CASE_BLANCHE) neighbors++;
        }
        for (int y=1;y<3;y++) {
            if (p[i][j+y]==CASE_BLANCHE) neighbors++;
        }
    }
    return neighbors;
}
int countNeighborsYBlack(Plateau p,int i, int j) {
    int neighbors=0;
    if (p[i][j]==CASE_NOIRE) {
        for (int y=-2;y<0;y++) {
            if (p[i][j+y]==CASE_NOIRE) neighbors++;
        }
        for (int y=1;y<3;y++) {
            if (p[i][j+y]==CASE_NOIRE) neighbors++;
        }
    }
    return neighbors;
}

int canAttack(Plateau p){ //retourne un score positif ou négatif si l'allié peut attaquer ou si l'ennemi peut attaquer
    int score;
     for(int i=1;i<MAX_I-1;i++) {
        for (int j=1;j<MAX_J-1;j++) {
            if (p[i][j]==CASE_BLANCHE) {
                if (p[i+1][j]==CASE_NOIRE) { // si bille adverse devant la bille alliée
                    int allyNeighborsX=countNeighborsXWhite(p,i,j);
                    int ennemyNeighborsX=countNeighborsXBlack(p,i+1,j);
                    if (allyNeighborsX<ennemyNeighborsX) score-=10; // si l'adversaire peut attaquer
                    else if(allyNeighborsX>ennemyNeighborsX) score+=10;
                }
                if (p[i][j+1]==CASE_NOIRE) { // si bille adverse à gauche ou droite de la bille alliée
                    int allyNeighborsLine=countNeighborsYWhite(p,i,j);
                    int ennemyNeighborsLine=countNeighborsYBlack(p,i,j+1);
                    if (allyNeighborsLine<ennemyNeighborsLine) score-=10;
                    else if (allyNeighborsLine>ennemyNeighborsLine) score+=10;
                }
                if (p[i][j-1]==CASE_NOIRE) {
                    int allyNeighborsLine=countNeighborsYWhite(p,i,j);
                    int ennemyNeighborsLine=countNeighborsYBlack(p,i,j-1);
                    if (allyNeighborsLine<ennemyNeighborsLine) score-=10;
                    else if (allyNeighborsLine>ennemyNeighborsLine) score+=10;
                }
            }
        }
    }
    return score;
}


int evaluate(Plateau p,char currentPlayer){
	int utility=0;
	if(victory(p)==1){
		utility+=100;
	}
	if(loss(p)==1){
		utility+=-100;
	} 
	if(currentPlayer==CASE_NOIRE){
		utility += density(p, currentPlayer, ALPHA);
	}
	if(currentPlayer==CASE_BLANCHE){
		utility -= density(p, currentPlayer, ALPHA);
	}
	utility+=distanceToCenter(p);
	utility+=areOpponentsNear(p);
	utility+=canAttack(p);
	return utility;
}

void main(){
	Plateau plateau = {
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_VIDE, CASE_BLANCHE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_VIDE, CASE_BLANCHE, CASE_VIDE, CASE_VIDE},
    {CASE_NOIRE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE},
    {CASE_BLANCHE, CASE_VIDE, CASE_BLANCHE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_BLANCHE, CASE_VIDE, CASE_VIDE, CASE_BLANCHE},
    {CASE_VIDE, CASE_VIDE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE}
};
	printf("%i",evaluate(plateau,CASE_BLANCHE));


}


