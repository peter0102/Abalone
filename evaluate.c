#include "global.h"

//La fonction victory prends un plateau en paramètre et vérifie l'existence d'un pion adverse dans la bordure: Fin de partie
//Le score de cette fonction d'évaluation est attribué lors de la fonction evaluate
int victory(Board board,char other_player){
	int i;
	for(i=0;i<=8;i++){
		if(board[0][i]==other_player || board[i][9]==other_player || board[9][9-i]==other_player || board[9-i][0]==other_player){
			return(1);
		}
	}
	return(0);
}

//La fonction victory prends un plateau en paramètre et vérifie l'existence d'un pion allié dans la bordure: Fin de partie
//Le score de cette fonction d'évaluation est attribué également lors de la fonction evaluate
int loss(Board board,char current_player){
	int i;
	for(i=0;i<=8;i++){
		if(board[0][i]==current_player || board[i][9]==current_player || board[9][9-i]==current_player || board[9-i][0]==current_player){
			return(1);
		}
	}
	return(0);
}

//La fonction density renvoie la moyenne de pions bar bloc de 3x3 multipliée par un coefficient pour donner le score
int density(Board board,char currentPlayer,int alpha){
	int i=0,j=0;
	int t[]={0,0,0,0,0,0,0,0,0};
	for(i=1;i<=3;i++){
		for(j=1;j<=3;j++){
			if(board[i][j]==currentPlayer){
				t[0]++;
			}
		}
	}
	for(i=4;i<=6;i++){
		for(j=1;j<=3;j++){
			if(board[i][j]==currentPlayer){
				t[1]++;
			}
		}
	}
	for(i=6;i<=8;i++){
		for(j=1;j<=3;j++){
			if(board[i][j]==currentPlayer){
				t[2]++;
			}
		}
	}
	for(i=1;i<=3;i++){
		for(j=4;j<=6;j++){
			if(board[i][j]==currentPlayer){
				t[3]++;
			}
		}
	}
	for(i=4;i<=6;i++){
		for(j=4;j<=6;j++){
			if(board[i][j]==currentPlayer){
				t[4]++;
			}
		}
	}
	for(i=6;i<=8;i++){
		for(j=4;j<=6;j++){
			if(board[i][j]==currentPlayer){
				t[5]++;
			}
		}
	}
	for(i=1;i<=3;i++){
		for(j=6;j<=8;j++){
			if(board[i][j]==currentPlayer){
				t[6]++;
			}
		}
	}
	for(i=4;i<=6;i++){
		for(j=6;j<=8;j++){
			if(board[i][j]==currentPlayer){
				t[7]++;
			}
		}
	}
	for(i=6;i<=8;i++){
		for(j=6;j<=8;j++){
			if(board[i][j]==currentPlayer){
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
int distanceToCenter(Board board,char current_player, char other_player) { 
    int totalScore=0;
    Board score={ //tableau du score en fonction de la position
        {0,0,0,0,0,0,0,0,0,0},
        {0,1,1,1,1,1,1,1,1,0},
        {0,1,5,5,5,5,5,5,1,0},
        {0,1,5,10,10,10,10,5,1,0},
        {0,1,5,10,15,15,10,5,1,0},
        {0,1,5,10,15,15,10,5,1,0},
        {0,1,5,10,10,10,10,5,1,0},
        {0,1,5,5,5,5,5,5,1,0},
        {0,1,1,1,1,1,1,1,1,0},
        {0,0,0,0,0,0,0,0,0,0}
			};
    for(int i=1;i<MAX_I-1;i++) {
        for (int j=1;j<MAX_J-1;j++) {
            if (board[i][j]==other_player) {
                totalScore-=score[i][j];
            }
            else if(board[i][j]==current_player) {
                totalScore+=score[i][j];
            }
        }

    }
    return totalScore;

}
// compte le nombre d'ennemis proches (à 1,2 et 3 cases) et retourne un score
int areOpponentsNear(Board board, char current_player, char other_player){
    int score;
    for(int i=1;i<MAX_I-1;i++) {
        for (int j=1;j<MAX_J-1;j++) {
            if (board[i][j]==current_player) {
                if (board[i+1][j]==other_player) score+=-5; // -5 si adversaire au contact, -3 si à une case distante, -1 si à 2 cases distantes
                if (board[i][j+1]==other_player) score+=-5;
                if (board[i+2][j]==other_player) score+=-3;
                if (board[i][j+2]==other_player) score+=-3;
                if (board[i+3][j]==other_player) score+=-1;
                if (board[i][j+3]==other_player) score+=-1;
                if (board[i-1][j]==other_player) score+=-5;
                if (board[i][j-1]==other_player) score+=-5;
                if (board[i-2][j]==other_player) score+=-3;
                if (board[i][j-2]==other_player) score+=-3;
                if (board[i-3][j]==other_player) score+=-1;
                if (board[i][j-3]==other_player) score+=-1;
            }
        }
    }
    return score;
}
// compte les voisins blancs sur l'axe X vertical
int countNeighborsXWhite(Board board,int i, int j){ 
    int neighbors=0;
    if (board[i][j]==WHITE) {
        for (int x=-2;x<0;x++) {
         if (board[i+x][j]==WHITE) neighbors++;
        }
        for (int x=1;x<3;x++) {
            if (board[i+x][j]==WHITE) neighbors++;
        }
    }
    return neighbors;
}
 // compte les voisins noirs sur l'axe X vertical
int countNeighborsXBlack(Board board,int i, int j){
    int neighbors=0;
    if (board[i][j]==BLACK) {
        for (int x=-2;x<0;x++) {
         if (board[i+x][j]==BLACK) neighbors++;
        }
        for (int x=1;x<3;x++) {
            if (board[i+x][j]==BLACK) neighbors++;
        }
    }
    return neighbors;
}
// compte les voisins blancs sur l'axe Y horizontal
int countNeighborsYWhite(Board board,int i, int j) { 
    int neighbors=0;
    if (board[i][j]==WHITE) {
        for (int y=-2;y<0;y++) {
            if (board[i][j+y]==WHITE) neighbors++;
        }
        for (int y=1;y<3;y++) {
            if (board[i][j+y]==WHITE) neighbors++;
        }
    }
    return neighbors;
}
// compte les voisins noirs sur l'axe Y horizontal
int countNeighborsYBlack(Board board,int i, int j, char current_player) {
    int neighbors=0;
    if (board[i][j]==current_player) {
        for (int y=-2;y<0;y++) {
            if (board[i][j+y]==current_player) neighbors++;
        }
        for (int y=1;y<3;y++) {
            if (board[i][j+y]==current_player) neighbors++;
        }
    }
    return neighbors;
}
//retourne un score positif ou négatif si l'allié peut attaquer ou si l'ennemi peut attaquer
int canAttack(Board board,char current_player, char other_player){
    int score;
     for(int i=1;i<MAX_I-1;i++) {
        for (int j=1;j<MAX_J-1;j++) {
            if (board[i][j]==current_player) {
                if (board[i+1][j]==other_player) { // si bille adverse devant la bille alliée
                    int allyNeighborsX=countNeighborsXBlack(board,i,j);
                    int ennemyNeighborsX=countNeighborsXWhite(board,i+1,j);
                    if (allyNeighborsX<ennemyNeighborsX) score-=10; // si l'adversaire peut attaquer
                    else if(allyNeighborsX>ennemyNeighborsX) score+=10;
                }
                if (board[i][j+1]==current_player) { // si bille adverse à gauche ou droite de la bille alliée
                    int allyNeighborsLine=countNeighborsYBlack(board,i,j,current_player);
                    int ennemyNeighborsLine=countNeighborsYWhite(board,i,j+1);
                    if (allyNeighborsLine<ennemyNeighborsLine) score-=10;
                    else if (allyNeighborsLine>ennemyNeighborsLine) score+=10;
                }
                if (board[i][j-1]==current_player) {
                    int allyNeighborsLine=countNeighborsYBlack(board,i,j,current_player);
                    int ennemyNeighborsLine=countNeighborsYWhite(board,i,j-1);
                    if (allyNeighborsLine<ennemyNeighborsLine) score-=10;
                    else if (allyNeighborsLine>ennemyNeighborsLine) score+=10;
                }
                if (board[i-1][j]==other_player) { // si bille adverse devant la bille alliée
                    int allyNeighborsX=countNeighborsXBlack(board,i,j);
                    int ennemyNeighborsX=countNeighborsXWhite(board,i-1,j);
                    if (allyNeighborsX<ennemyNeighborsX) score-=10; // si l'adversaire peut attaquer
                    else if(allyNeighborsX>ennemyNeighborsX) score+=10;
                }
            }
        }
    }
    return score;
}
int canEnd(Board board,char current_player,char other_player){
    int score=0;
    for(int i=0;i<MAX_I-1;i++){
        if (board[1][i]==current_player) {
        int allyNeighborsLine=countNeighborsXBlack(board,1,i);
        int ennemyNeigborsLine=countNeighborsXWhite(board,2,i);
            if (board[2][i]==other_player) {
                if (allyNeighborsLine<ennemyNeigborsLine) score+=-10000;
                else score+=-20;
            }
        }
        if (board[1][i]==other_player) {
        int allyNeighborsLine=countNeighborsXBlack(board,2,i);
        int ennemyNeigborsLine=countNeighborsXWhite(board,1,i);
            if (board[2][i]==current_player) {
                if (allyNeighborsLine>ennemyNeigborsLine) score+=10000;
                else score+=20;
            }
        }
        if (board[8][i]==current_player) {
        int allyNeighborsLine=countNeighborsXBlack(board,8,i);
        int ennemyNeigborsLine=countNeighborsXWhite(board,7,i);
            if (board[7][i]==other_player) {
                if (allyNeighborsLine<ennemyNeigborsLine) score+=-10000;
                else score+=-20;
            }
        }
        if (board[8][i]==other_player) {
        int allyNeighborsLine=countNeighborsXBlack(board,7,i);
        int ennemyNeigborsLine=countNeighborsXWhite(board,8,i);
            if (board[7][i]==current_player) {
                if (allyNeighborsLine>ennemyNeigborsLine) score+=10000;
                else score+=-20;
            }
        }
        if (board[i][1]==current_player) {
        int allyNeighborsLine=countNeighborsXBlack(board,i,1);
        int ennemyNeigborsLine=countNeighborsXWhite(board,i,2);
            if (board[i][2]==other_player) {
                if (allyNeighborsLine<ennemyNeigborsLine) score+=-10000;
                else score+=-20;
            }
        }
        if (board[i][1]==other_player) {
        int allyNeighborsLine=countNeighborsXBlack(board,i,2);
        int ennemyNeigborsLine=countNeighborsXWhite(board,i,1);
            if (board[i][2]==current_player) {
                if (allyNeighborsLine>ennemyNeigborsLine) score+=10000;
                else score+=20;
            }
        }
        if (board[i][8]==current_player) {
        int allyNeighborsLine=countNeighborsXBlack(board,i,8);
        int ennemyNeigborsLine=countNeighborsXWhite(board,i,7);
            if (board[i][7]==other_player) {
                if (allyNeighborsLine<ennemyNeigborsLine) score+=-10000;
                else score+=-20;
            }
        }
        if (board[i][8]==current_player) {
        int allyNeighborsLine=countNeighborsXBlack(board,i,8);
        int ennemyNeigborsLine=countNeighborsXWhite(board,i,7);
            if (board[i][7]==other_player) {
                if (allyNeighborsLine<ennemyNeigborsLine) score+=-10000;
                else score+=-20;
            }
        }
        if (board[i][8]==other_player) {
        int allyNeighborsLine=countNeighborsXBlack(board,i,7);
        int ennemyNeigborsLine=countNeighborsXWhite(board,i,8);
            if (board[i][7]==current_player) {
                if (allyNeighborsLine>ennemyNeigborsLine) score+=10000;
                else score+=20;
            }
        }
    }
}    

// somme le score d'un plateau en fonction des différents paramètres pris en compte
int evaluate(Board board,char current_player,char other_player){
	int utility=0;
	if(victory(board, other_player)==1){
		utility+=100;
	}
	if(loss(board,current_player)==1){
		utility+=-100;
	}
    /*
	if(current_player==BLACK){
		utility += density(board,BLACK,1);
	}
	if(current_player==WHITE){
		utility -= density(board,BLACK,1);
	}
     */
	utility+=areOpponentsNear(board,current_player,other_player)+canAttack(board,current_player,other_player)+distanceToCenter(board,current_player,other_player)+canEnd(board,current_player,other_player);
	return utility;
}


