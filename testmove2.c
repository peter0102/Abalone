#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "global.h"

char* moves[]={"H1:G1","H2:F2","G2:F2","G3:F3","H3:F3","G4:F4","H4:F4","G5:G5","H5:F5","G6:F6","H6:F6","G7:F7","H7:F7","H8:G8"};

char absChar(char v){
    if(v<0){
        return(-v);
    }
    return(v);
}

char whatMove(Plateau plat,Move m, char current_player) {
    //déplacement en ligne horizontal
    if (m[0][0] == m[0][1]) {
        //déplacement vers la droite
        if (m[1][0] < m[1][1]) {
            return (LINE_HOR_RIGHT);
        }
        //déplacement vers la gauche
        if (m[1][0] > m[1][1]) {
            return (LINE_HOR_LEFT);
        }
    }
        //déplacement en ligne vertical
    else if (m[1][0] == m[1][1]) {
        //déplacement vers le bas
        if (m[0][0] < m[0][1]) {
            return (LINE_VER_DOWN);
        }
        //déplacement vers le haut
        if (m[0][0] > m[0][1]) {
            return (LINE_VER_UP);
        }
    }
        //déplacement latéral de taille 2
    else if ((absChar(m[0][0] - m[0][1]) + absChar(m[1][0] - m[1][1])) == 2) {
        //déplacement latéral horizontal
        if (plat[m[0][0]][m[1][1]] == current_player) {
            return (LAT_2_HOR);
        }
            //déplacement latéral vertical
        else if (plat[m[0][1]][m[1][0]] == current_player) {
            return (LAT_2_VER);
        }
    }
        //déplacement latéral vertical de taille 3
    else if (absChar(m[0][0] - m[0][1]) == 2 && absChar(m[1][0] - m[1][1]) == 1) {
        //x0 bas & x1 haut
        if (m[0][0] > m[0][1]) {
            return (LAT_3_VER_X0_DOWN);
        }
        //x0 haut & x1 bas
        if (m[0][0] < m[0][1]) {
            return (LAT_3_VER_X0_UP);
        }
    }
        //déplacement latéral horizontal de taille 3
    else if (absChar(m[0][0] - m[0][1]) == 1 && absChar(m[1][0] - m[1][1]) == 2) {
        //y0 droite & y1 gauche
        if (m[1][0] < m[1][1]) {
            return (LAT_3_HOR_Y0_RIGHT);
        }
        //y0 gauche & y1 droite
        if (m[1][0] > m[1][1]) {
            return (LAT_3_HOR_Y0_LEFT);
        }
    }
    return (ERROR);
}

char allies(char type_of_move,Move m){
    if(type_of_move==LINE_HOR_RIGHT || type_of_move==LINE_HOR_LEFT){
        return(absChar(m[1][0] - m[1][1]));
    }
    else if(type_of_move==LINE_VER_UP || type_of_move==LINE_VER_DOWN) {
        return(absChar(m[0][0] - m[0][1]));
    }
    else if(type_of_move==LAT_2_HOR || type_of_move==LAT_2_VER) {
        return(2);
    }
    else if(type_of_move==LAT_3_VER_X0_DOWN || type_of_move==LAT_3_VER_X0_UP ||\
    type_of_move==LAT_3_HOR_Y0_RIGHT || type_of_move==LAT_3_HOR_Y0_LEFT){
        return(3);
    }
    return(ERROR);
}

void active(Move m,char type_of_move,char nb_allies,Triple coords_allies,Triple coords_ennemies){
    //initialisation alliés
    coords_allies[0][0] = m[0][0];
    coords_allies[1][0] = m[1][0];
    //initialisation ennemis
    coords_ennemies[0][0] = m[0][1];
    coords_ennemies[1][0] = m[1][1];
    //disjonctions de cas
    for(char i = 1;i<nb_allies;i++) {
        switch (type_of_move) {
            case LINE_HOR_RIGHT: {
                coords_allies[0][i] = m[0][0];
                coords_allies[1][i] = m[1][0] + i;
                coords_ennemies[0][i] = m[0][1];
                coords_ennemies[1][i] = m[1][1] + i;
            }
                break;
            case LINE_HOR_LEFT: {
                coords_allies[0][i] = m[0][0];
                coords_allies[1][i] = m[1][0] - i;
                coords_ennemies[0][i] = m[0][1];
                coords_ennemies[1][i] = m[1][1] - i;
            }
                break;
            case LINE_VER_DOWN: {
                coords_allies[0][i] = m[0][0] + i;
                coords_allies[1][i] = m[1][0];
                coords_ennemies[0][i] = m[0][1] + i;
                coords_ennemies[1][i] = m[1][1];
            }
                break;
            case LINE_VER_UP: {
                coords_allies[0][i] = m[0][0] - i;
                coords_allies[1][i] = m[1][0] ;
                coords_ennemies[0][i] = m[0][1] - i;
                coords_ennemies[1][i] = m[1][1];
            }
                break;
            case LAT_2_HOR: {
                coords_allies[0][1] = m[0][0];
                coords_allies[1][1] = m[1][1];
                coords_ennemies[0][1] = m[0][1];
                coords_ennemies[1][1] = m[1][0];
            }
                break;
            case LAT_2_VER: {
                coords_allies[0][1] = m[0][1];
                coords_allies[1][1] = m[1][0];
                coords_ennemies[0][1] = m[0][0];
                coords_ennemies[1][1] = m[1][1];
            }
                break;
            case LAT_3_VER_X0_DOWN: {
                coords_allies[0][i] = m[0][0] - i;
                coords_allies[1][i] = m[1][0];
                coords_ennemies[0][i] = m[0][1] + i;
                coords_ennemies[1][i] = m[1][1];
            }
                break;
            case LAT_3_VER_X0_UP: {
                coords_allies[0][i] = m[0][0] + i;
                coords_allies[1][i] = m[1][0];
                coords_ennemies[0][i] = m[0][1] - i;
                coords_ennemies[1][i] = m[1][1];
            }
                break;
            case LAT_3_HOR_Y0_RIGHT:{
                coords_allies[0][i] = m[0][0];
                coords_allies[1][i] = m[1][0] + i;
                coords_ennemies[0][i] = m[0][1];
                coords_ennemies[1][i] = m[1][1] - i;
            }
                break;
            case LAT_3_HOR_Y0_LEFT:{
                coords_allies[0][i] = m[0][0];
                coords_allies[1][i] = m[1][0] - i;
                coords_ennemies[0][i] = m[0][1];
                coords_ennemies[1][i] = m[1][1] + i;
            }
        }
    }
}

char ennemies(Plateau plat,Triple coords_ennemies,char nb_allies, char current_player){
    char nb_ennemies=0;
    for(char i=0;i<nb_allies;i++) {
        if(plat[coords_ennemies[0][i]][coords_ennemies[1][i]]==current_player){
            return(ERROR);
        }
        else if(plat[coords_ennemies[0][i]][coords_ennemies[1][i]]==EMPTY){
            return(nb_ennemies);
        }
        else{
            nb_ennemies++;
        }
    }
    return(ERROR);
}

char checkColor(Triple coords,char color, char nb_allies, Plateau plat){
    for(char i=0;i<nb_allies;i++) {
        if(plat[coords[0][i]][coords[1][i]]!=color){
            return(ERROR);
        }
    }
    return(SUCCESS);
}

char checkMove(Plateau plat, Move m,char current_player) {
    char type_of_move = whatMove(plat,m,current_player);
    char nb_allies = allies(type_of_move,m);
    //Initialisation des actifs (alliés + ennemis)
    Triple coords_allies;
    Triple coords_ennemies;
    active(m, type_of_move, nb_allies, coords_allies, coords_ennemies);
    char nb_ennemies = ennemies(plat, coords_ennemies, nb_allies,current_player);
    if(nb_ennemies == ERROR){
        return(ERROR);
    }
    //vérification des couleurs
    if(checkColor(coords_allies,current_player,nb_allies,plat)==ERROR){
        return(ERROR);
    }
    return(SUCCESS);
}

char pierre(Plateau plat, Move m, char current_player){
    if(checkMove(plat,m,current_player)==ERROR){
        if(plat[m[1][0]][m[1][1]]==current_player){
            return(current_player);
        }
        else{
            return(ERROR);
        }
    }
    return(SUCCESS);
}

void moveLine(Plateau plat,Move m,Triple coords_ennemies,char nb_ennemies,char current_player,char other_player){
    //déplacement des alliés
    plat[m[0][0]][m[1][0]] = EMPTY;
    plat[coords_ennemies[0][0]][coords_ennemies[1][0]] = current_player;
    //déplacement des ennemis
    if (nb_ennemies > 0) {
        plat[coords_ennemies[0][nb_ennemies]][coords_ennemies[1][nb_ennemies]] = other_player;
    }
}

void moveLateral(Plateau plat,Triple coords_allies,Triple coords_ennemies, char nb_allies,char current_player){
    for(char i=0;i<nb_allies;i++){
        plat[coords_allies[0][i]][coords_allies[1][i]]=EMPTY;
        plat[coords_ennemies[0][i]][coords_ennemies[1][i]]=current_player;
    }
}

void move(Plateau plat,Move m,Triple coords_ennemies,char nb_ennemies,char type_of_move,Triple coords_allies,\
char nb_allies,char current_player, char other_player){
    //déplacement en ligne
    if(type_of_move == LINE_VER_DOWN || type_of_move == LINE_VER_UP ||\
    type_of_move== LINE_HOR_LEFT || type_of_move == LINE_HOR_RIGHT) {
        moveLine(plat,m,coords_ennemies,nb_ennemies,current_player,other_player);
    }
        //déplacement latéral
    else{
        moveLateral(plat,coords_allies,coords_ennemies,nb_allies,current_player);
    }
}

char allMove(Plateau plat,Move m,char current_player,char other_player){
    char type_of_move = whatMove(plat,m,current_player);
    char nb_allies = allies(type_of_move,m);
    if(nb_allies == ERROR){ //si le type de mouvement est ERROR nb_allies renvoie ERROR
        return(ERROR);
    }
    Triple coords_allies;
    Triple coords_ennemies;
    active(m, type_of_move, nb_allies, coords_allies, coords_ennemies);
    char nb_ennemies = ennemies(plat,coords_ennemies,nb_allies,current_player);
    char good_color = checkColor(coords_allies,current_player,nb_allies,plat);
    if(nb_ennemies == ERROR || good_color == ERROR){
        return(ERROR);
    }
    move(plat,m,coords_ennemies,nb_ennemies,type_of_move,coords_allies,nb_allies,current_player,other_player);
    return(SUCCESS);
}

int** createMove(int x1, int y1, int x2, int y2) {
    int** move = malloc(2 * sizeof(int*));
    for(int i = 0; i < 2; i++)
        move[i] = malloc(2 * sizeof(int));
    move[0][0] = x1;
    move[0][1] = y1;
    move[1][0] = x2;
    move[1][1] = y2;
    return move;
}
int moveChrConvert (char chr, char type) {
    int index = -1;
    switch (type) {
        case 'l': index = (int)(chr-'@'); break;
        case 'n': index = (int)(chr-'0'); break;
        default: printf("%s", "Erreur de conversion : type de caractère inconnu."); return -1;
    }
    return (index > 0 && index < 9) ? index : -1;
}

char moveChrConvertReverse (int index, char type) {
    if (index < 1 || index > 8) return 'x';
    switch (type) {
        case 'l': return (char)(index + 64); //64 = @
        case 'n': return (char)(index + 48); //48 = 0
        default: printf("%s", "Erreur de conversion : type de caractère inconnu."); return 'x';
    }
}

int** translateMove(char* input) {
    int** move = createMove(-1, -1, -1, -1);

    //Si la longueur de l'entree n'est pas 5, il y a erreur
    if (strlen(input) != 5) return move;
    //Si le 3eme caractere n'est pas ':', il y a erreur
    if (input[2] != ':') return move;

    int numbers[] = {
        moveChrConvert(input[0], 'l'),
        moveChrConvert(input[1], 'n'),
        moveChrConvert(input[3], 'l'),
        moveChrConvert(input[4], 'n')
    };
    for (int i = 0; i < 4; i++) {
        if (numbers[i] == -1) return move;
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            move[i][j] = numbers[(2*i)+j];
    }
    return move;
}

char* translateMoveReverse(int** move) {
    char* str = malloc(5);

    str[0] = moveChrConvertReverse(move[0][0], 'l');
    str[1] = moveChrConvertReverse(move[0][1], 'n');
    str[2] = ':';
    str[3] = moveChrConvertReverse(move[1][0], 'l');
    str[4] = moveChrConvertReverse(move[1][1], 'n');
    return str;
}



void printMove(int** move) {
    printf("%i, %i\n%i, %i\n\n", move[0][0], move[0][1], move[1][0], move[1][1]);
}



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

//La fonction victory prends un plateau en paramètre et vérifie l'existence d'un pion adverse dans la bordure: Fin de partie
//Le score de cette fonction d'évaluation est attribué lors de la fonction evaluate
int victory(Plateau p){
	int i=0,v=0;
	for(i=0;i<=8;i++){
		if(p[0][i]==WHITE || p[i][9]==WHITE || p[9][9-i]==WHITE || p[9-i][0]==WHITE){
			v==1;
			break;
		}
	}
	return v;
}

//La fonction victory prends un plateau en paramètre et vérifie l'existence d'un pion allié dans la bordure: Fin de partie
//Le score de cette fonction d'évaluation est attribué également lors de la fonction evaluate
int loss(Plateau p){
	int i=0,l=0;
	for(i=0;i<=8;i++){
		if(p[0][i]==BLACK || p[i][9]==BLACK || p[9][9-i]==BLACK || p[9-i][0]==BLACK){
			l==1;
			break;
		}
	}
	return l;
}

//La fonction density renvoie la moyenne de pions par bloc de 3x3 multipliée par un coefficient pour donner le score
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

int distanceToCenter(Plateau p) { // évalue une configuration du plateau en fonction des positions des billes
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
            if (p[i][j]==WHITE) {
                totalScore-=score[i][j];
            }
            else if(p[i][j]==BLACK) {
                totalScore+=score[i][j];
            }
        }

    }
    return totalScore;

}

int areOpponentsNear(Plateau p){ // compte le nombre d'ennemis proches (à 1,2 et 3 cases) et retourne un score
    int score;
    for(int i=1;i<MAX_I-1;i++) {
        for (int j=1;j<MAX_J-1;j++) {
            if (p[i][j]==BLACK) {
                if (p[i+1][j]==WHITE) score+=-5; // -5 si adversaire au contact, -3 si à une case distante, -1 si à 2 cases distantes
                if (p[i][j+1]==WHITE) score+=-5;
                if (p[i+2][j]==WHITE) score+=-3;
                if (p[i][j+2]==WHITE) score+=-3;
                if (p[i+3][j]==WHITE) score+=-1;
                if (p[i][j+3]==WHITE) score+=-1;
                if (p[i-1][j]==WHITE) score+=-5;
                if (p[i][j-1]==WHITE) score+=-5;
                if (p[i-2][j]==WHITE) score+=-3;
                if (p[i][j-2]==WHITE) score+=-3;
                if (p[i-3][j]==WHITE) score+=-1;
                if (p[i][j-3]==WHITE) score+=-1;
            }
        }
    }
    return score;
}
int countNeighborsXWhite(Plateau p,int i, int j){ // compte les voisins blancs sur l'axe X vertical
    int neighbors=0;
    if (p[i][j]==WHITE) {
        for (int x=-2;x<0;x++) {
         if (p[i+x][j]==WHITE) neighbors++;
        }
        for (int x=1;x<3;x++) {
            if (p[i+x][j]==WHITE) neighbors++;
        }
    }
    return neighbors;
}

int countNeighborsXBlack(Plateau p,int i, int j){ // compte les voisins noirs sur l'axe X vertical
    int neighbors=0;
    if (p[i][j]==BLACK) {
        for (int x=-2;x<0;x++) {
         if (p[i+x][j]==BLACK) neighbors++;
        }
        for (int x=1;x<3;x++) {
            if (p[i+x][j]==BLACK) neighbors++;
        }
    }
    return neighbors;
}
int countNeighborsYWhite(Plateau p,int i, int j) { // compte les voisins blancs sur l'axe Y horizontal
    int neighbors=0;
    if (p[i][j]==WHITE) {
        for (int y=-2;y<0;y++) {
            if (p[i][j+y]==WHITE) neighbors++;
        }
        for (int y=1;y<3;y++) {
            if (p[i][j+y]==WHITE) neighbors++;
        }
    }
    return neighbors;
}
int countNeighborsYBlack(Plateau p,int i, int j) { // compte les voisins noirs sur l'axe Y horizontal
    int neighbors=0;
    if (p[i][j]==BLACK) {
        for (int y=-2;y<0;y++) {
            if (p[i][j+y]==BLACK) neighbors++;
        }
        for (int y=1;y<3;y++) {
            if (p[i][j+y]==BLACK) neighbors++;
        }
    }
    return neighbors;
}

int canAttack(Plateau p){ //retourne un score positif ou négatif si l'allié peut attaquer ou si l'ennemi peut attaquer
    int score;
     for(int i=1;i<MAX_I-1;i++) {
        for (int j=1;j<MAX_J-1;j++) {
            if (p[i][j]==WHITE) {
                if (p[i+1][j]==BLACK) { // si bille adverse devant la bille alliée
                    int allyNeighborsX=countNeighborsXWhite(p,i,j);
                    int ennemyNeighborsX=countNeighborsXBlack(p,i+1,j);
                    if (allyNeighborsX<ennemyNeighborsX) score-=10; // si l'adversaire peut attaquer
                    else if(allyNeighborsX>ennemyNeighborsX) score+=10;
                }
                if (p[i][j+1]==BLACK) { // si bille adverse à gauche ou droite de la bille alliée
                    int allyNeighborsLine=countNeighborsYWhite(p,i,j);
                    int ennemyNeighborsLine=countNeighborsYBlack(p,i,j+1);
                    if (allyNeighborsLine<ennemyNeighborsLine) score-=10;
                    else if (allyNeighborsLine>ennemyNeighborsLine) score+=10;
                }
                if (p[i][j-1]==BLACK) {
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

int evaluate(Plateau p,char currentPlayer){ // somme le score d'un plateau en fonction des différents paramètres pris en compte
	int utility=0;
	if(victory(p)==1){
		utility+=100;
	}
	if(loss(p)==1){
		utility+=-100;
	} 
    utility = utility + areOpponentsNear(p) + canAttack(p)+distanceToCenter(p);
	return utility;
}






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
            printf("Premier score donnée %i\n",newScore);
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
        printf("Obtention du meilleur score %i\n",score);
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
            printf("Premier score donnée %i\n",newScore);
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
        printf("Obtention du meilleur score %i\n",score);
	}
}


char aiMove(Plateau p){
    printf("Plateau au début de aiMove\n");
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
        printf("Premier score donnée par l'IA dans aiMove %i\n",newScore);
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
        printf("Score temporaire : %i \n",score);
    }
    printf("Meilleur score : %i\n",score);
    printf("Coordonnées du mouvement %i %i %i %i \n",bestMove[0][0],bestMove[0][1],bestMove[1][0],bestMove[1][1]);
    printf("Tableau avant le bestMove \n");
    display(p);
    allMove(p,bestMove,BLACK,WHITE);
    printf("Tableau après le bestMove\n");
    display(p);

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
    printf("Plateau avant le coup du joueur \n");
    display(p);
    char a=allMove(p,m,WHITE,BLACK);
    printf("Tableau après le coup du joueur \n");
    display(p);
    printf("\n\nRetour de la fonction allMove : %c\n",a);
}

int main(int argc, char *argv[]) {
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
    char current_player;
    char other_player;
    int end=0;
    int turn_count=1;
    printf("Début du jeu\n");
    display(plateau);
    while (end!=1) {
		if(turn_count%2==1) { //turn_count = 1 --> current_player = 'B'
            current_player = 'B';
            other_player = 'W';
            printf("Avant aiMove\n");
            display(plateau);
            printf("Tour %i\n",turn_count);
		    printf("C'est au tour des noirs (IA) de jouer\n");
		    aiMove(plateau);
            printf("Après aiMove\n");
            display(plateau);
            printf("\n*************************************\n");
		}
		else { //turn_count = 2 --> current_player = 'W'
            current_player = 'W';
            other_player = 'B';
            printf("Tour %i\n",turn_count);
	    	printf("C'est à votre tour de jouer\n");
		    playerMove(plateau);
            display(plateau);
            printf("\n*************************************\n");
		}
		turn_count++;
	}
}