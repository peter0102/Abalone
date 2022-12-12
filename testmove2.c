#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define MAX_I 10
#define MAX_J 10
#define INFTY 147483648

#define EMPTY '0'
#define BLACK 'B'
#define WHITE 'W'

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//joueurs
//#define current_player 'W'
//#define other_player 'B'
#define no_player '0'
//types de mouvement
#define line_horizontal_right 'a'
#define line_horizontal_left 'b'
#define line_vertical_down 'c'
#define line_vertical_up 'd'
#define lateral_two_horizontal 'e'
#define lateral_two_vertical 'f'
#define lateral_three_vertical_x0_down 'g'
#define lateral_three_vertical_x0_up 'h'
#define lateral_three_horizontal_y0_right 'i'
#define lateral_three_horizontal_y0_left 'j'
//gestion d'erreurs
#define error 'x'
#define success 'l'
//définition des types
typedef char Plateau[10][10];
typedef char Move[2][2];
typedef char Triple[2][3]; //x ou y puis x0 1 ou 2
//fonctions


char* moves[]={"H1:G1","H2:F2","G2:F2","G3:F3","H3:F3","G4:F4","H4:F4","G5:G5","H5:F5","G6:F6","H6:F6","G7:F7","H7:F7","H8:G8"};

char absChar(char v){
    if(v<0){
        return(-v);
    }
    else{
        return(v);
    }
}

char whatMove(Plateau plat,Move m, char current_player) {
    //déplacement en ligne horizontal
    if (m[0][0] == m[0][1]) {
        //déplacement vers la droite
        if (m[1][0] < m[1][1]) {
            return (line_horizontal_right);
        }
        //déplacement vers la gauche
        if (m[1][0] > m[1][1]) {
            return (line_horizontal_left);
        }
    }
        //déplacement en ligne vertical
    else if (m[1][0] == m[1][1]) {
        //déplacement vers le bas
        if (m[0][0] < m[0][1]) {
            return (line_vertical_down);
        }
        //déplacement vers le haut
        if (m[0][0] > m[0][1]) {
            return (line_vertical_up);
        }
    }
        //déplacement latéral de taille 2
    else if ((absChar(m[0][0] - m[0][1]) + absChar(m[1][0] - m[1][1])) == 2) {
        //déplacement latéral horizontal
        if (plat[m[0][0]][m[1][1]] == current_player) {
            return (lateral_two_horizontal);
        }
            //déplacement latéral vertical
        else if (plat[m[0][1]][m[1][0]] == current_player) {
            return (lateral_two_vertical);
        }
    }
        //déplacement latéral vertical de taille 3
    else if (absChar(m[0][0] - m[0][1]) == 2 && absChar(m[1][0] - m[1][1]) == 1) {
        //x0 bas & x1 haut
        if (m[0][0] > m[0][1]) {
            return (lateral_three_vertical_x0_down);
        }
        //x0 haut & x1 bas
        if (m[0][0] < m[0][1]) {
            return (lateral_three_vertical_x0_up);
        }
    }
        //déplacement latéral horizontal de taille 3
    else if (absChar(m[0][0] - m[0][1]) == 1 && absChar(m[1][0] - m[1][1]) == 2) {
        //y0 droite & y1 gauche
        if (m[1][0] < m[1][1]) {
            return (lateral_three_horizontal_y0_right);
        }
        //y0 gauche & y1 droite
        if (m[1][0] > m[1][1]) {
            return (lateral_three_horizontal_y0_left);
        }
    }
    return (error);
}

char allies(char type_of_move,Move m){
    if(type_of_move==line_horizontal_right || type_of_move==line_horizontal_left){
        return(absChar(m[1][0] - m[1][1]));
    }
    else if(type_of_move==line_vertical_up || type_of_move==line_vertical_down) {
        return(absChar(m[0][0] - m[0][1]));
    }
    else if(type_of_move==lateral_two_horizontal || type_of_move==lateral_two_vertical) {
        return(2);
    }
    else if(type_of_move==lateral_three_vertical_x0_down || type_of_move==lateral_three_vertical_x0_up ||\
    type_of_move==lateral_three_horizontal_y0_right || type_of_move==lateral_three_horizontal_y0_left){
        return(3);
    }
    return(error);
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
            case line_horizontal_right: {
                coords_allies[0][i] = m[0][0];
                coords_allies[1][i] = m[1][0] + i;
                coords_ennemies[0][i] = m[0][1];
                coords_ennemies[1][i] = m[1][1] + i;
            }
                break;
            case line_horizontal_left: {
                coords_allies[0][i] = m[0][0];
                coords_allies[1][i] = m[1][0] - i;
                coords_ennemies[0][i] = m[0][1];
                coords_ennemies[1][i] = m[1][1] - i;
            }
                break;
            case line_vertical_down: {
                coords_allies[0][i] = m[0][0] + i;
                coords_allies[1][i] = m[1][0];
                coords_ennemies[0][i] = m[0][1] + i;
                coords_ennemies[1][i] = m[1][1];
            }
                break;
            case line_vertical_up: {
                coords_allies[0][i] = m[0][0] - i;
                coords_allies[1][i] = m[1][0] ;
                coords_ennemies[0][i] = m[0][1] - i;
                coords_ennemies[1][i] = m[1][1];
            }
                break;
            case lateral_two_horizontal: {
                coords_allies[0][1] = m[0][0];
                coords_allies[1][1] = m[1][1];
                coords_ennemies[0][1] = m[0][1];
                coords_ennemies[1][1] = m[1][0];
            }
                break;
            case lateral_two_vertical: {
                coords_allies[0][1] = m[0][1];
                coords_allies[1][1] = m[1][0];
                coords_ennemies[0][1] = m[0][0];
                coords_ennemies[1][1] = m[1][1];
            }
                break;
            case lateral_three_vertical_x0_down: {
                coords_allies[0][i] = m[0][0] - i;
                coords_allies[1][i] = m[1][0];
                coords_ennemies[0][i] = m[0][1] + i;
                coords_ennemies[1][i] = m[1][1];
            }
                break;
            case lateral_three_vertical_x0_up: {
                coords_allies[0][i] = m[0][0] + i;
                coords_allies[1][i] = m[1][0];
                coords_ennemies[0][i] = m[0][1] - i;
                coords_ennemies[1][i] = m[1][1];
            }
                break;
            case lateral_three_horizontal_y0_right:{
                coords_allies[0][i] = m[0][0];
                coords_allies[1][i] = m[1][0] + i;
                coords_ennemies[0][i] = m[0][1];
                coords_ennemies[1][i] = m[1][1] - i;
            }
                break;
            case lateral_three_horizontal_y0_left:{
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
            return(error);
        }
        else if(plat[coords_ennemies[0][i]][coords_ennemies[1][i]]==no_player){
            return(nb_ennemies);
        }
        else{
            nb_ennemies++;
        }
    }
    return(error);
}

char checkColor(Triple coords,char color, char nb_allies, Plateau plat){
    for(char i=0;i<nb_allies;i++) {
        if(plat[coords[0][i]][coords[1][i]]!=color){
            return(error);
        }
    }
    return(success);
}

char checkMove(Plateau plat, Move m,char current_player) {
    char type_of_move = whatMove(plat,m,current_player);
    char nb_allies = allies(type_of_move,m);
    //Initialisation des actifs (alliés + ennemis)
    Triple coords_allies;
    Triple coords_ennemies;
    active(m, type_of_move, nb_allies, coords_allies, coords_ennemies);
    char nb_ennemies = ennemies(plat, coords_ennemies, nb_allies,current_player);
    if(nb_ennemies == error){
        return(error);
    }
    //vérification des couleurs
    if(checkColor(coords_allies,current_player,nb_allies,plat)==error){
        return(error);
    }
    return(success);
}

char pierre(Plateau plat, Move m, char current_player){
    if(checkMove(plat,m,current_player)==error){
        if(plat[m[1][0]][m[1][1]]==current_player){
            return(current_player);
        }
        else{
            return(error);
        }
    }
    return(success);
}

void moveLine(Plateau plat,Move m,Triple coords_ennemies,char nb_ennemies,char current_player,char other_player){
    //déplacement des alliés
    plat[m[0][0]][m[1][0]] = no_player;
    plat[coords_ennemies[0][0]][coords_ennemies[1][0]] = current_player;
    //déplacement des ennemis
    if (nb_ennemies > 0) {
        plat[coords_ennemies[0][nb_ennemies]][coords_ennemies[1][nb_ennemies]] = other_player;
    }
}

void moveLateral(Plateau plat,Triple coords_allies,Triple coords_ennemies, char nb_allies,char current_player){
    for(char i=0;i<nb_allies;i++){
        plat[coords_allies[0][i]][coords_allies[1][i]]=no_player;
        plat[coords_ennemies[0][i]][coords_ennemies[1][i]]=current_player;
    }
}

void move(Plateau plat,Move m,Triple coords_ennemies,char nb_ennemies,char type_of_move,Triple coords_allies,\
char nb_allies,char current_player, char other_player){
    //déplacement en ligne
    if(type_of_move == line_vertical_down || type_of_move == line_vertical_up ||\
    type_of_move== line_horizontal_left || type_of_move == line_horizontal_right) {
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
    if(nb_allies == error){ //si le type de mouvement est error nb_allies renvoie error
        return(error);
    }
    Triple coords_allies;
    Triple coords_ennemies;
    active(m, type_of_move, nb_allies, coords_allies, coords_ennemies);
    char nb_ennemies = ennemies(plat,coords_ennemies,nb_allies,current_player);
    char good_color = checkColor(coords_allies,current_player,nb_allies,plat);
    if(nb_ennemies == error || good_color == error){
        return(error);
    }
    move(plat,m,coords_ennemies,nb_ennemies,type_of_move,coords_allies,nb_allies,current_player,other_player);
    return(success);
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
            if (p[i][j]==BLACK) {
                if (p[i+1][j]==WHITE) { // si bille adverse devant la bille alliée
                    int ennemyNeighborsX=countNeighborsXWhite(p,i,j);
                    int allyNeighborsX=countNeighborsXBlack(p,i+1,j);
                    if (allyNeighborsX<ennemyNeighborsX) score-=10; // si l'adversaire peut attaquer
                    else if(allyNeighborsX>ennemyNeighborsX) score+=10;
                }
                if (p[i][j+1]==WHITE) { // si bille adverse à gauche ou droite de la bille alliée
                    int ennemyNeighborsLine=countNeighborsYWhite(p,i,j);
                    int allyNeighborsLine=countNeighborsYBlack(p,i,j+1);
                    if (allyNeighborsLine<ennemyNeighborsLine) score-=10;
                    else if (allyNeighborsLine>ennemyNeighborsLine) score+=10;
                }
                if (p[i][j-1]==WHITE) {
                    int ennemyNeighborsLine=countNeighborsYWhite(p,i,j);
                    int allyNeighborsLine=countNeighborsYBlack(p,i,j-1);
                    if (allyNeighborsLine<ennemyNeighborsLine) score-=10;
                    else if (allyNeighborsLine>ennemyNeighborsLine) score+=10;
                }
            }
        }
    }
    return score;
}

int evaluate(Plateau p,char currentPlayer){ // somme le score d'un plateau en fonction des différents paramètres pris en compte
    int alpha=1;
	int utility=0;
	if(victory(p)==1){
		utility+=100;
	}
	if(loss(p)==1){
		utility+=-100;  
	} 
	if(currentPlayer==BLACK){
		utility += density(p, currentPlayer, alpha);
	}
	if(currentPlayer==WHITE){
		utility -= density(p, currentPlayer, alpha);
	}
utility=utility+canAttack(p)+distanceToCenter(p)+areOpponentsNear(p)+density(p,BLACK,1);
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
        allMove(p,m,BLACK,WHITE);
        int newScore=miniMax(p,2,-INFTY,INFTY,false);
        printf("Premier score donnée par l'IA dans aiMove %i, au tour : %i \n",newScore,i);
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