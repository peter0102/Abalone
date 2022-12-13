
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "global.h"

#define nombrePions 14
#define tailleListeCoups 80

char otherPlayer(char player);

char otherPlayer(char player) {
    if (player == BLACK) return WHITE;
    else if (player == WHITE) return BLACK;
    else return ERROR;
}


//fonctions

char moveChrConvertReverse (char index, char type) {
    if (index < 1 || index > 8) return ERROR;
    switch (type) {
        case 'l': return (index + '@');
        case 'n': return (index + '0');
        default: printf("%s", "Erreur de conversion : type de caractère inconnu."); return ERROR;
    }
}


char* translateMoveReverse(Move move) {
    char* str = malloc(6);

    str[0] = moveChrConvertReverse(move[0][0], 'l');
    str[1] = moveChrConvertReverse(move[1][0], 'n');
    str[2] = ':';
    str[3] = moveChrConvertReverse(move[0][1], 'l');
    str[4] = moveChrConvertReverse(move[1][1], 'n');
    str[5] = '\0';
    return str;
}

char absChar(char v){
    if(v<0){
        return(-v);
    }
    else{
        return(v);
    }
}

char checkSuicide(Move m){
    if(m[0][1]==0 || m[0][1]==9 || m[1][1]==0 || m[1][1]==9){
        return(ERROR);
    }
    return(SUCCESS);
}

char whatMove(Board board,Move m, char current_player) {
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
        if (board[m[0][0]][m[1][1]] == current_player) {
            return (LAT_2_HOR);
        }
            //déplacement latéral vertical
        else if (board[m[0][1]][m[1][0]] == current_player) {
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

char ennemiesLine(Board board,Triple coords_ennemies,char nb_allies, char current_player){
    char nb_ennemies=0;
    for(char i=0;i<nb_allies;i++) {
        if(board[coords_ennemies[0][i]][coords_ennemies[1][i]]==current_player){
            return(ERROR);
        }
        else if(board[coords_ennemies[0][i]][coords_ennemies[1][i]]==EMPTY){
            return(nb_ennemies);
        }
        else{
            nb_ennemies++;
        }
    }
    return(ERROR);
}

char ennemiesLat(Board board,Triple coords_ennemies,char nb_allies){
    for(char i=0;i<nb_allies;i++) {
        if(board[coords_ennemies[0][i]][coords_ennemies[1][i]]!=EMPTY){
            return(ERROR);
        }
    }
    return(0);
}

char ennemies(Board board,Triple coords_ennemies,char nb_allies, char current_player, char type_of_move){
    if(type_of_move == LINE_VER_DOWN || type_of_move == LINE_VER_UP ||\
    type_of_move== LINE_HOR_LEFT || type_of_move == LINE_HOR_RIGHT) {
        return(ennemiesLine(board,coords_ennemies,nb_allies,current_player));
    }
        //déplacement latéral
    else{
        return(ennemiesLat(board,coords_ennemies,nb_allies));
    }
}

char checkColor(Triple coords,char color, char nb_allies, Board board){
    for(char i=0;i<nb_allies;i++) {
        if(board[coords[0][i]][coords[1][i]]!=color){
            return(ERROR);
        }
    }
    return(SUCCESS);
}

char checkMove(Board board, Move m,char current_player, char other_player) {
    if(checkSuicide(m)==ERROR){
        return(ERROR);
    }
    char type_of_move = whatMove(board,m,current_player);
    char nb_allies = allies(type_of_move,m);
    //Initialisation des actifs (alliés + ennemis)
    Triple coords_allies;
    Triple coords_ennemies;
    active(m, type_of_move, nb_allies, coords_allies, coords_ennemies);
    char nb_ennemies = ennemies(board, coords_ennemies, nb_allies, current_player, other_player);
    if(nb_ennemies == ERROR){
        return(ERROR);
    }
    //vérification des couleurs
    if(checkColor(coords_allies,current_player,nb_allies,board)==ERROR){
        return(ERROR);
    }
    return(SUCCESS);
}

char checkForList(Board board, Move m, char current_player,char other_player){
    if(checkMove(board,m,current_player,other_player)==ERROR){
        if(board[m[0][1]][m[1][1]]==current_player){
            return(current_player);
        }
        else{
            return(ERROR);
        }
    }
    return(SUCCESS);
}

void moveLine(Board board,Move m,Triple coords_ennemies,char nb_ennemies,char current_player,char other_player){
    //déplacement des alliés
    board[m[0][0]][m[1][0]] = EMPTY;
    board[coords_ennemies[0][0]][coords_ennemies[1][0]] = current_player;
    //déplacement des ennemis
    if (nb_ennemies > 0) {
        board[coords_ennemies[0][nb_ennemies]][coords_ennemies[1][nb_ennemies]] = other_player;
    }
}

void moveLateral(Board board,Triple coords_allies,Triple coords_ennemies, char nb_allies, char current_player){
    for(char i=0;i<nb_allies;i++){
        board[coords_allies[0][i]][coords_allies[1][i]]=EMPTY;
        board[coords_ennemies[0][i]][coords_ennemies[1][i]]=current_player;
    }
}

void move(Board board,Move m,Triple coords_ennemies,char nb_ennemies,char type_of_move,Triple coords_allies,\
char nb_allies,char current_player, char other_player){
    //déplacement en ligne
    if(type_of_move == LINE_VER_DOWN || type_of_move == LINE_VER_UP ||\
    type_of_move== LINE_HOR_LEFT || type_of_move == LINE_HOR_RIGHT) {
        moveLine(board,m,coords_ennemies,nb_ennemies,current_player,other_player);
    }
        //déplacement latéral
    else{
        moveLateral(board,coords_allies,coords_ennemies,nb_allies, current_player);
    }
}

char allMove(Board board,Move m,char current_player,char other_player){
    if(checkSuicide(m)==ERROR){
        return(ERROR);
    }
    char type_of_move = whatMove(board,m,current_player);
    char nb_allies = allies(type_of_move,m);
    if(nb_allies == ERROR){ //si le type de mouvement est ERROR nb_allies renvoie ERROR
        return(ERROR);
    }
    Triple coords_allies;
    Triple coords_ennemies;
    active(m, type_of_move, nb_allies, coords_allies, coords_ennemies);
    char nb_ennemies = ennemies(board,coords_ennemies,nb_allies, current_player, other_player);
    char good_color = checkColor(coords_allies,current_player,nb_allies,board);
    if(nb_ennemies == ERROR ||nb_ennemies>=nb_allies||good_color == ERROR){
        return(ERROR);
    }
    move(board,m,coords_ennemies,nb_ennemies,type_of_move,coords_allies,nb_allies,current_player,other_player);
    return(SUCCESS);
}




// Le plateau :

char* Traduire(int compteur);

Board plat = {
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', '0'},
{'0', '0', 'W', 'W', 'W', 'W', 'W', 'W', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', 'B', 'B', 'B', 'B', 'B', 'B', '0', '0'},
{'0', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'} };

/// Les typedef :

typedef char Triple[2][3]; //x ou y puis x0 1 ou 2

void FindAllPions(char Player);

Triple ListePions[14];

// Deux Pions

Triple ListeDeuxPions[100];

int compteurDeuxPions;

// Trois pions

int compteurTroisPions;

Triple ListeTroisPions[100];

// Def des types coups

typedef char Move[2][2];

Move ListeCoups[tailleListeCoups];

/// Les fonctions

// Les affichages

void display();

void AfficherPion(Triple PionAAfficher, int PositionPion);

void AfficherListePions();

void AfficherCoup(Move CoupAAfficher);

void AfficherListeCoups();

void AfficherListeDeuxPions();

void AfficherListeTroisPions();

/// Les fonctions de coup :

// tous les coups :

char* FindAllMoves(char current_player);


int UneBilleQuatreCoups(Triple PionATester, int compteurCoups, char current_player);

int UneBilleUnCoupHautGauche(Move CoupATester, int compteurCoups, char current_player);

int UneBilleUnCoupDroiteBas(Move CoupATester, int compteurCoups, char current_player);


// Deux billes :

int DeuxBillesQuatreCoupsHorizontal(Triple GroupeATester, int compteurCoups, char current_player);

int DeuxBillesQuatreCoupsVertical(Triple GroupeATester, int compteurCoups, char current_player);


int DeuxBillesUnCoup(Move CoupATester, int compteurCoups, char current_player);

int DeuxBillesUnCoupEtPeutEtre3Billes(Move CoupATester, int compteurCoups, char current_player);


// Trois billes

int TroisBillesQuatreCoupsVertical(Triple GroupeATester, int compteurCoups, char current_player);

int TroisBillesQuatreCoupsHorizontal(Triple GroupeATester, int compteurCoups, char current_player);

int TroisBillesUnCoup(Move CoupATester, int compteurCoups, char current_player);


/// Variables globales
/*
Triple coords_allies;
Triple coords_ennemies;
*/


/// azedgfh
/// zqfesgfd
///q qEGSFD
/// QAZFEGG


/// les fonctions Move






/// Les fonctions d'affichage :

void display2() {
    printf("\n0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10|\n");
    for (int i=0; i < 10; i++) {
        printf("%i |",i);
        for (int j=0; j < 10; j++) {
            if (plat[i][j] == BLACK)
                printf (" B |");
            else if (plat[i][j] == WHITE)
                printf (" W |" );
            else if (plat[i][j] == '0')
                printf (" . |" );
        }
        printf("\n\n");
    }
}

void display() {
    printf("\nX | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |\n\n");
    for (int i=1; i < 9; i++) {
        printf("%i |",i);
        for (int j=1; j < 9; j++) {
            if (plat[i][j] == BLACK)
                printf (" B |");
            else if (plat[i][j] == WHITE)
                printf (" W |" );
            else if (plat[i][j] == '0')
                printf (" . |" );
        }
        printf("\n\n");
    }
}



void AfficherPion(Triple PionAAfficher, int PositionPion){
    printf("[ %i, %i ]", PionAAfficher[0][PositionPion], PionAAfficher[1][PositionPion]);
}

void AfficherListePions(){
    printf("[ ");
    for (int i=0;i<13;i++){
        AfficherPion(ListePions[i], 0);
    printf(" / ");
    if ((i+1)%2==0){ // %x pour afficher sur x colonnes
                printf("\n\n");
        }
    }
    AfficherPion(ListePions[13], 0);
    printf(" ]\n");
}

void AfficherCoup(Move CoupAAfficher){
        printf("[%i,", CoupAAfficher[0][0]);
        printf("%i], ", CoupAAfficher[0][1]);
        printf("[%i,", CoupAAfficher[1][0]);
        printf("%i]", CoupAAfficher[1][1]);
}

void AfficherListeCoupsVersionHumaine(){
    for (int i=0;i<tailleListeCoups;i++){
        AfficherCoup(ListeCoups[i]);
        printf(" x1 : %i / ", ListeCoups[i][0][0]);
        printf("y1 : %i / ", ListeCoups[i][1][0]);
        printf("x2 : %i / ", ListeCoups[i][0][1]);
        printf("y2 : %i / ", ListeCoups[i][1][1]);
        printf(" \n");

    }
}

void AfficherListeCoups(){
    for (int i=0;i<tailleListeCoups;i++){
        AfficherCoup(ListeCoups[i]);
        printf(" / ");
        if ((i+1)%3==0){ // %x pour afficher sur x colonnes
                printf("\n\n");
        }
    }
}

void AfficherListeDeuxPions(){
    for (int i=0;i<compteurDeuxPions;i++){
            printf("[[ %i, %i],", ListeDeuxPions[i][0][0], ListeDeuxPions[i][0][1]);
            printf("[ %i, %i]] /// ", ListeDeuxPions[i][1][0], ListeDeuxPions[i][1][1]);
            if ((i+1)%2==0){ // modulo X pour X colonnes
                printf("\n\n");
        }
    }
}

void AfficherListeTroisPions(){
    for (int i=0;i<compteurTroisPions;i++){
            AfficherPion(ListeTroisPions[i],0);
            printf(" , ");
            AfficherPion(ListeTroisPions[i],1);
            printf(" , ");
            AfficherPion(ListeTroisPions[i],2);
            printf(" / ");
            if ((i+1)%2==0){ // modulo X pour X colonnes
                    printf("\n\n");
        }
    }
}



/// Find All Pions

void FindAllPions(char current_player){ //Idee pour l'am�liorer : comparer avec la liste d'avant, et juste trouver les pions qui manquent

    int compteurPions=0;

    for (char i=0; i < 10; i++) {
        for (char j=0; j < 10; j++) {
                    if(plat[i][j]==current_player){
                            ListePions[compteurPions][0][0]=i;
                            ListePions[compteurPions][0][1]=0;
                            ListePions[compteurPions][0][2]=0;
                            ListePions[compteurPions][1][0]=j;
                            ListePions[compteurPions][1][1]=0;
                            ListePions[compteurPions][1][2]=0;
                            compteurPions = compteurPions + 1;
                    }
            }
    }

    printf("Le nombre de pions est %i\n\n", compteurPions);
}


/// Find All Moves

char* FindAllMoves(char current_player){

    printf("Coucou\n");

    int compteurCoups=0;

    Triple Tampon;

    for(int i=0;i<14;i++){
            compteurCoups=UneBilleQuatreCoups(ListePions[i], compteurCoups, current_player);
    }

/*
    ListeCoups[compteurCoups][0][0]=2500;
    ListeCoups[compteurCoups][0][1]=2500;
    ListeCoups[compteurCoups][1][0]=2500;
    ListeCoups[compteurCoups][1][1]=2500;

    compteurCoups=compteurCoups+1;
*/
    Triple TamponDeuxPions;

    for (int j=0;j<compteurDeuxPions;j++){


        TamponDeuxPions[0][0]= ListeDeuxPions[j][0][0];  //x0
        TamponDeuxPions[0][1]= ListeDeuxPions[j][1][0]; // X1
        TamponDeuxPions[0][2]= 0;                      // x2
        TamponDeuxPions[1][0]= ListeDeuxPions[j][0][1];   // y0
        TamponDeuxPions[1][1]= ListeDeuxPions[j][1][1];   //y1
        TamponDeuxPions[1][2]= 0;                     //y2

        if(ListeDeuxPions[j][0][0]!=ListeDeuxPions[j][1][0]){ // Si X different
           compteurCoups=DeuxBillesQuatreCoupsVertical(TamponDeuxPions, compteurCoups, current_player);
        }
        if(ListeDeuxPions[j][0][1]!=ListeDeuxPions[j][1][1]){ // Si Y differenet
            compteurCoups=DeuxBillesQuatreCoupsHorizontal(TamponDeuxPions, compteurCoups, current_player);
        }
    }
/*
    ListeCoups[compteurCoups][0][0]=4400;
    ListeCoups[compteurCoups][0][1]=4400;
    ListeCoups[compteurCoups][1][0]=4400;
    ListeCoups[compteurCoups][1][1]=4400;

    compteurCoups=compteurCoups+1;
*/
    // Partie 3 pions

    Triple TamponTroisPions;

    for (int t=0;t<compteurTroisPions;t++){


        TamponTroisPions[0][0]= ListeTroisPions[t][0][0];  //x0
        TamponTroisPions[0][1]= ListeTroisPions[t][0][1]; // X1
        TamponTroisPions[0][2]= ListeTroisPions[t][0][2]; // x2
        TamponTroisPions[1][0]= ListeTroisPions[t][1][0];   // y0
        TamponTroisPions[1][1]= ListeTroisPions[t][1][1];   //y1
        TamponTroisPions[1][2]= ListeTroisPions[t][1][2];   //y2
/*
        printf("Le groupe teste ");
        AfficherPion(TamponTroisPions,0);
        AfficherPion(TamponTroisPions,1);
        AfficherPion(TamponTroisPions,2);

        printf("\n\n");
*/
        if(TamponTroisPions[0][0]!=TamponTroisPions[0][1]){ // Si X different
           compteurCoups=TroisBillesQuatreCoupsVertical(TamponTroisPions, compteurCoups, current_player);
        }
        if(TamponTroisPions[1][0]!=TamponTroisPions[1][1]){ // Si Y differenet
            compteurCoups=TroisBillesQuatreCoupsHorizontal(TamponTroisPions, compteurCoups, current_player);
        }
    }
/*
    ListeCoups[compteurCoups][0][0]='U';
    ListeCoups[compteurCoups][0][1]='U';
    ListeCoups[compteurCoups][1][0]='U';
    ListeCoups[compteurCoups][1][1]='U';

    compteurCoups=compteurCoups+1;
*/
    printf("CompteurCoups = %i\n", compteurCoups);

    char* resultat;
    resultat=Traduire(compteurCoups);
	return(resultat);

}


/// La partie 1 billes

int UneBilleQuatreCoups(Triple PionATester, int compteurCoups, char current_player){


    char xInitial=PionATester[0][0];
    char yInitial=PionATester[1][0];

    char xFinal;
    char yFinal;

    // Coup Haut
    xFinal=xInitial;
    yFinal=yInitial;

    xFinal= xFinal-1;
    Move CoupHaut={{xInitial,xFinal}, {yInitial,yFinal}};

    compteurCoups=UneBilleUnCoupHautGauche(CoupHaut, compteurCoups, current_player);

    // Coup Bas

    xFinal=xInitial;
    yFinal=yInitial;

    xFinal= xFinal+1;
    Move CoupBas={{xInitial,xFinal}, {yInitial,yFinal}};

    compteurCoups=UneBilleUnCoupDroiteBas(CoupBas, compteurCoups, current_player);

    // Coup Gauche
    xFinal=xInitial;
    yFinal=yInitial;

    yFinal= yFinal-1;
    Move CoupGauche={{xInitial,xFinal}, {yInitial,yFinal}};

    compteurCoups=UneBilleUnCoupHautGauche(CoupGauche, compteurCoups, current_player);

    // Coup Droite
    xFinal=xInitial;
    yFinal=yInitial;

    yFinal= yFinal+1;
    Move CoupDroite={{xInitial,xFinal}, {yInitial,yFinal}};

    compteurCoups=UneBilleUnCoupDroiteBas(CoupDroite, compteurCoups, current_player);

    return(compteurCoups);

}

int UneBilleUnCoupHautGauche(Move CoupATester, int compteurCoups, char current_player){

    char resultat;
    resultat =checkForList(plat, CoupATester, current_player, otherPlayer(current_player));

    if (resultat==SUCCESS){ // Coup autoris�
            ListeCoups[compteurCoups][0][0]=CoupATester[0][0];
            ListeCoups[compteurCoups][0][1]=CoupATester[0][1];
            ListeCoups[compteurCoups][1][0]=CoupATester[1][0];
            ListeCoups[compteurCoups][1][1]=CoupATester[1][1];
            compteurCoups=compteurCoups+1;
    }

//    printf("Une bille un coup : %c %i %i\n\n", resultat, compteurCoups, compteurDeuxPions);

    return(compteurCoups);
}

int UneBilleUnCoupDroiteBas(Move CoupATester, int compteurCoups, char current_player){

    char resultat;
    resultat =checkForList(plat, CoupATester, current_player, otherPlayer(current_player));
/*
    printf("ReCoucou de une bille, cette bille : ");
    printf("%i %o", CoupATester[0][0], CoupATester[1][0]);
    printf("\nOn va a cet endroit  : ");
    printf("%i %i\n", CoupATester[0][1], CoupATester[1][1]);
    printf("Resultat : %c\n", resultat);
*/

    if (resultat==SUCCESS){ // Coup autoris�
            ListeCoups[compteurCoups][0][0]=CoupATester[0][0];
            ListeCoups[compteurCoups][0][1]=CoupATester[0][1];
            ListeCoups[compteurCoups][1][0]=CoupATester[1][0];
            ListeCoups[compteurCoups][1][1]=CoupATester[1][1];
            compteurCoups=compteurCoups+1;
    }

    if (resultat==current_player){ // Bille de m�me couleur
        ListeDeuxPions[compteurDeuxPions][0][0]=CoupATester[0][0]; // X1
        ListeDeuxPions[compteurDeuxPions][0][1]=CoupATester[1][0]; // Y1
        ListeDeuxPions[compteurDeuxPions][1][0]=CoupATester[0][1]; // X2
        ListeDeuxPions[compteurDeuxPions][1][1]=CoupATester[1][1]; // Y2
        compteurDeuxPions=compteurDeuxPions+1;
    }

//    printf("Une bille un coup : %c %i %i\n\n", resultat, compteurCoups, compteurDeuxPions);

    return(compteurCoups);

    // Si bille blanche : ajouter +1 au compteur, et le groupe � la liste
}


/// La partie 2 billes


// Deus billes verticales :

int DeuxBillesQuatreCoupsVertical(Triple GroupeATester, int compteurCoups, char current_player){ // On change x, pas y

        char xInitial=GroupeATester[0][0]; // Les pions sont dans l'ordre croissant ; la reference sera le premier
        char yInitial=GroupeATester[1][0];

        char xFinal;
        char yFinal;

        xFinal=xInitial;
        yFinal=yInitial;

        // Coup Lateral 1, vers la gauche

        xFinal = xInitial+1;
        yFinal = yInitial-1;

        Move CoupLateral_Un={{xInitial,xFinal}, {yInitial,yFinal}};

        compteurCoups=DeuxBillesUnCoup(CoupLateral_Un, compteurCoups, current_player);

        // Coup Lateral 2, vers la droite

        xFinal = xInitial+1;
        yFinal = yInitial+1;

        Move CoupLateral2={{xInitial,xFinal}, {yInitial,yFinal}};

        compteurCoups=DeuxBillesUnCoup(CoupLateral2, compteurCoups, current_player);

        // Coup Ligne 1, vers le bas !!!!! ATTENTION peut etre 3 billes

        xFinal = xInitial+2;
        yFinal = yInitial;

        Move CoupLigne1={{xInitial,xFinal}, {yInitial,yFinal}};
        compteurCoups=DeuxBillesUnCoupEtPeutEtre3Billes(CoupLigne1, compteurCoups, current_player);

        // Coup Ligne 2, vers le haut !!!!ATTENTION AU POINT DE REFERENCE

 //       char x0;
//        char y0;

        char x0 = xInitial+1;
        char y0 = yInitial;
        xFinal = x0-2;
        yFinal = y0;

        Move CoupLigne2={{x0,xFinal}, {y0,yFinal}};
        compteurCoups=DeuxBillesUnCoup(CoupLigne2, compteurCoups, current_player);

    return(compteurCoups);

}

// Deus billes horizontales :

int DeuxBillesQuatreCoupsHorizontal(Triple GroupeATester, int compteurCoups, char current_player){

        char xInitial=GroupeATester[0][0]; // Les pions sont dans l'ordre croissant ; la reference sera le premier
        char yInitial=GroupeATester[1][0];

        char xFinal;
        char yFinal;

        xFinal=xInitial;
        yFinal=yInitial;

        // Coup Lateral 1, vers le haut

        xFinal = xInitial-1;
        yFinal = yInitial+1;

        Move CoupLateral_Un={{xInitial,xFinal}, {yInitial,yFinal}};

        compteurCoups=DeuxBillesUnCoup(CoupLateral_Un, compteurCoups, current_player);

        // Coup Lateral 2, vers le bas

        xFinal = xInitial+1;
        yFinal = yInitial+1;

        Move CoupLateral2={{xInitial,xFinal}, {yInitial,yFinal}};

        compteurCoups=DeuxBillesUnCoup(CoupLateral2, compteurCoups, current_player);

        // Coup Ligne 1, vers la droite !!! Peut etre 3 billes

        xFinal = xInitial;
        yFinal = yInitial+2;

        Move CoupLigne1={{xInitial,xFinal}, {yInitial,yFinal}};
        compteurCoups=DeuxBillesUnCoupEtPeutEtre3Billes(CoupLigne1, compteurCoups, current_player);

        // Coup Ligne 2, vers la gauche !!!! ATTENTION AU POINT DE REFERENCE

        char x0;
        char y0;

        x0 = xInitial;
        y0 = yInitial+1;
        xFinal = x0;
        yFinal = y0-2;

        Move CoupLigne2={{x0,xFinal}, {y0,yFinal}};
        compteurCoups=DeuxBillesUnCoup(CoupLigne2, compteurCoups,current_player);

    return(compteurCoups);

}
// La partie 1 avec 3 billes possibles : Horizontal vers la droite, Vertical vers le bas

int DeuxBillesUnCoupEtPeutEtre3Billes(Move CoupATester, int compteurCoups, char current_player) {

    char resultat;
    resultat =checkForList(plat, CoupATester, current_player, otherPlayer(current_player));

    if (resultat==SUCCESS){ // Coup autoris�
            ListeCoups[compteurCoups][0][0]=CoupATester[0][0];
            ListeCoups[compteurCoups][0][1]=CoupATester[0][1];
            ListeCoups[compteurCoups][1][0]=CoupATester[1][0];
            ListeCoups[compteurCoups][1][1]=CoupATester[1][1];
            compteurCoups=compteurCoups+1;
    }
    if (resultat==current_player){ // Bille de m�me couleur

        ListeTroisPions[compteurTroisPions][0][0]=CoupATester[0][0];
        ListeTroisPions[compteurTroisPions][0][2]=CoupATester[0][1];

        ListeTroisPions[compteurTroisPions][1][0]=CoupATester[1][0];
        ListeTroisPions[compteurTroisPions][1][2]=CoupATester[1][1];

        if(ListeTroisPions[compteurTroisPions][0][0]!=ListeTroisPions[compteurTroisPions][0][2]){ // X different, donc vertical
             ListeTroisPions[compteurTroisPions][0][1]=(CoupATester[0][0]+1);
             ListeTroisPions[compteurTroisPions][1][1]=CoupATester[1][0];
        }
        if(ListeTroisPions[compteurTroisPions][1][0]!=ListeTroisPions[compteurTroisPions][1][2]){ // Y different, donc horizontal
                ListeTroisPions[compteurTroisPions][0][1]=CoupATester[0][0];
                ListeTroisPions[compteurTroisPions][1][1]=(CoupATester[1][0]+1);
        }

        compteurTroisPions=compteurTroisPions+1;
    }

    return(compteurCoups);
}


// La partie 1 coup sans 3 billes possibles

int DeuxBillesUnCoup(Move CoupATester, int compteurCoups, char current_player) {

    char resultat;
    resultat =checkForList(plat, CoupATester, current_player, otherPlayer(current_player));

    if (resultat==SUCCESS){
            ListeCoups[compteurCoups][0][0]=CoupATester[0][0];
            ListeCoups[compteurCoups][0][1]=CoupATester[0][1];
            ListeCoups[compteurCoups][1][0]=CoupATester[1][0];
            ListeCoups[compteurCoups][1][1]=CoupATester[1][1];
            compteurCoups=compteurCoups+1;
    }

    return(compteurCoups);
}



/// La partie 3 billes

// 3 Billes 4 Coups Vertical


int TroisBillesQuatreCoupsVertical(Triple GroupeATester, int compteurCoups, char current_player){ // On change x, pas y

        char xInitial=GroupeATester[0][0]; // Les pions sont dans l'ordre croissant ; la reference sera le premier
        char yInitial=GroupeATester[1][0];

        char xFinal;
        char yFinal;

        xFinal=xInitial;
        yFinal=yInitial;

        // Coup Lateral 1, vers la gauche

        xFinal = xInitial+2;
        yFinal = yInitial-1;

        Move CoupLateral_Un={{xInitial,xFinal}, {yInitial,yFinal}};

        compteurCoups=TroisBillesUnCoup(CoupLateral_Un, compteurCoups, current_player);

        // Coup Lateral 2, vers la droite

        xFinal = xInitial+2;
        yFinal = yInitial+1;

        Move CoupLateral2={{xInitial,xFinal}, {yInitial,yFinal}};

        compteurCoups=TroisBillesUnCoup(CoupLateral2, compteurCoups, current_player);

        // Coup Ligne 1, vers le bas !!!!!

        xFinal = xInitial+3;
        yFinal = yInitial;

        Move CoupLigne1={{xInitial,xFinal}, {yInitial,yFinal}};
        compteurCoups=TroisBillesUnCoup(CoupLigne1, compteurCoups, current_player);

        // Coup Ligne 2, vers le haut !!!!ATTENTION AU POINT DE REFERENCE

        char x0;
        char y0;

        x0 = xInitial+2;
        y0 = yInitial;
        xFinal = x0-3;
        yFinal = y0;

        Move CoupLigne2={{x0,xFinal}, {y0,yFinal}};
        compteurCoups=TroisBillesUnCoup(CoupLigne2, compteurCoups, current_player);

        return(compteurCoups);
}

// Trois billes horizontales

int TroisBillesQuatreCoupsHorizontal(Triple GroupeATester, int compteurCoups, char current_player){// On change y, pas x

        char xInitial=GroupeATester[0][0]; // Les pions sont dans l'ordre croissant ; la reference sera le premier
        char yInitial=GroupeATester[1][0];

        char xFinal;
        char yFinal;

        xFinal=xInitial;
        yFinal=yInitial;
/*
        printf("\nLe groupe de billes est :");
        AfficherPion(GroupeATester,0);
        AfficherPion(GroupeATester,1);
        AfficherPion(GroupeATester,2);
*/
        // Coup Lateral 1, vers le haut

        xFinal = xInitial-1;
        yFinal = yInitial+2;

        Move CoupLateral_Un={{xInitial,xFinal}, {yInitial,yFinal}};

        compteurCoups=TroisBillesUnCoup(CoupLateral_Un, compteurCoups, current_player);

        // Coup Lateral 2, vers le bas

        xFinal = xInitial+1;
        yFinal = yInitial+2;

        Move CoupLateral2={{xInitial,xFinal}, {yInitial,yFinal}};

        compteurCoups=TroisBillesUnCoup(CoupLateral2, compteurCoups, current_player);

        // Coup Ligne 1, vers la droite !!! Peut etre 3 billes

        xFinal = xInitial;
        yFinal = yInitial+3;

        Move CoupLigne1={{xInitial,xFinal}, {yInitial,yFinal}};
        compteurCoups=TroisBillesUnCoup(CoupLigne1, compteurCoups, current_player);

        // Coup Ligne 2, vers la gauche !!!! ATTENTION AU POINT DE REFERENCE

        char x0;
        char y0;

        x0 = xInitial+0;
        y0 = yInitial+2;
        xFinal = x0;
        yFinal = y0-3;

        Move CoupLigne2={{x0,xFinal}, {y0,yFinal}};
        compteurCoups=TroisBillesUnCoup(CoupLigne2, compteurCoups, current_player);

        return(compteurCoups);

}

// La partie 1 coup Horizontal


int TroisBillesUnCoup(Move CoupATester, int compteurCoups, char current_player) {

    char resultat;
    resultat =checkForList(plat, CoupATester, current_player, otherPlayer(current_player));
/*
    printf("\nLe coup demande est : ");
    AfficherCoup(CoupATester);
    printf("\nLe resultat est %c\n", resultat);
*/
    if (resultat==SUCCESS){
            ListeCoups[compteurCoups][0][0]=CoupATester[0][0];
            ListeCoups[compteurCoups][0][1]=CoupATester[0][1];
            ListeCoups[compteurCoups][1][0]=CoupATester[1][0];
            ListeCoups[compteurCoups][1][1]=CoupATester[1][1];
            compteurCoups=compteurCoups+1;
    }
    return(compteurCoups);
}

/// La fonction traduction


char* Traduire(int compteur){
    char* mTotal=malloc(compteur*6);
    char ChaineVide[]={';'};
    char* m=malloc(6);

    for(int i=0;i<compteur;i++){
        m=translateMoveReverse(ListeCoups[i]);
        mTotal = strncat(mTotal, m, 6);
        mTotal = strncat(mTotal, ChaineVide, 1);
    }

	return(mTotal);
}



/// Le main

int main(){

    char current_player;

    current_player=WHITE;


    printf("\n Uwu ^^\n\n");

    display();

    FindAllPions(current_player);

    AfficherListePions();

    /// Find all Moves

    char* resultat;

    resultat = FindAllMoves(current_player);



    AfficherListeCoups();

    printf("\n\n\n");

    AfficherListeCoupsVersionHumaine();

    printf("\n Liste 2 pions :\n\n ");

    AfficherListeDeuxPions();

    printf("\n\n Liste 3 pions :\n\n ");

    AfficherListeTroisPions();


    printf(" Le resultat est %s", resultat);

/*
    for (int i=0;i<29;i++){;
            printf("resultat %i : %s\n", i, resultat[i]);
    }
*/

    return(0);
}
