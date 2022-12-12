#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/// Le fichier .h

// Definitions de caract�res sp�ciaux :
#define nombrePions 14
#define tailleListeCoups 80
//joueurs
#define current_player 'W'
#define other_player 'B'
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
#define error 'k'
#define success 'l'



// Le plateau :

typedef char Plateau[10][10];

Plateau plat = {
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', 'W', 'W', '0', 'W', 'W', 'W', 'W', 'W', '0'},
{'0', '0', 'W', 'W', 'W', '0', 'W', 'W', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', 'W', 'W', '0', '0', '0', '0'},
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

// Verifications coups :

char pierre(Plateau plat, Move m);

char checkMove(Plateau plat, Move m);


// tous les coups :

void FindAllMoves();


int UneBilleQuatreCoups(Triple PionATester, int compteurCoups);

int UneBilleUnCoupHautGauche(Move CoupATester, int compteurCoups);

int UneBilleUnCoupDroiteBas(Move CoupATester, int compteurCoups);


// Deux billes :

int DeuxBillesQuatreCoupsHorizontal(Triple GroupeATester, int compteurCoups);

int DeuxBillesQuatreCoupsVertical(Triple GroupeATester, int compteurCoups);


int DeuxBillesUnCoup(Move CoupATester, int compteurCoups);

int DeuxBillesUnCoupEtPeutEtre3Billes(Move CoupATester, int compteurCoups);


// Trois billes

int TroisBillesQuatreCoupsVertical(Triple GroupeATester, int compteurCoups);

int TroisBillesQuatreCoupsHorizontal(Triple GroupeATester, int compteurCoups);

int TroisBillesUnCoup(Move CoupATester, int compteurCoups);


/// Variables globales
/*
Triple coords_allies;
Triple coords_ennemies;
*/

/// fonctions utilitaires

char absChar(char v1, char v2){
    int variable1 = v1 -'0';
    int variable2 = v2 -'0';
    int difference= variable1-variable2;
    if(difference<0){
            difference=0-difference;
    }
    char resultat=difference+'0';
    return(resultat);
}

char SommeCharEtInt(char caractere, int Changement){
    int variable = caractere -'0';

    int somme = variable + Changement;

    char resultat=somme+'0';

    return(resultat);
}


/// azedgfh
/// zqfesgfd
///q qEGSFD
/// QAZFEGG

/// Fonctions Move

char whatMove(Plateau plat,Move m) {
    //d�placement en ligne horizontal
    if (m[0][0] == m[0][1]) {
        //d�placement vers la droite
        if (m[1][0] < m[1][1]) {
            return (line_horizontal_right);
        }
        //d�placement vers la gauche
        if (m[1][0] > m[1][1]) {
            return (line_horizontal_left);
        }
    }
        //d�placement en ligne vertical
    else if (m[1][0] == m[1][1]) {
        //d�placement vers le bas
        if (m[0][0] < m[0][1]) {
            return (line_vertical_down);
        }
        //d�placement vers le haut
        if (m[0][0] > m[0][1]) {
            return (line_vertical_up);
        }
    }
        //d�placement lat�ral de taille 2
    else if ((absChar(m[0][0], m[0][1]) + absChar(m[1][0], m[1][1])) == 2) {
        //d�placement lat�ral horizontal
        if (plat[m[0][0]][m[1][1]] == current_player) {
            return (lateral_two_horizontal);
        }
            //d�placement lat�ral vertical
        else if (plat[m[0][1]][m[1][0]] == current_player) {
            return (lateral_two_vertical);
        }
    }
        //d�placement lat�ral vertical de taille 3
    else if (absChar(m[0][0], m[0][1]) == '2' && absChar(m[1][0], m[1][1]) == '1') {
        //x0 bas & x1 haut
        if (m[0][0] > m[0][1]) {
            return (lateral_three_vertical_x0_down);
        }
        //x0 haut & x1 bas
        if (m[0][0] < m[0][1]) {
            return (lateral_three_vertical_x0_up);
        }
    }
        //d�placement lat�ral horizontal de taille 3
    else if (absChar(m[0][0], m[0][1]) == '1' && absChar(m[1][0], m[1][1]) == '2') {
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
        return(absChar(m[1][0], m[1][1]));
    }
    else if(type_of_move==line_vertical_up || type_of_move==line_vertical_down) {
        return(absChar(m[0][0], m[0][1]));
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
    //initialisation alli�s
    coords_allies[0][0] = m[0][0];
    coords_allies[1][0] = m[1][0];
    //initialisation ennemis
    coords_ennemies[0][0] = m[0][1];
    coords_ennemies[1][0] = m[1][1];
    //disjonctions de cas
    int Int_nb_allies= nb_allies-'0';
    for(int i = 1;i<=Int_nb_allies;i++) {
        switch (type_of_move) {
            case line_horizontal_right: {
                coords_allies[0][i] = m[0][0];
                coords_allies[1][i] = SommeCharEtInt(m[1][0],i);
                coords_ennemies[0][i] = m[0][1];
                coords_ennemies[1][i] = SommeCharEtInt(m[1][1],i);
            }
                break;
            case line_horizontal_left: {
                coords_allies[0][i] = m[0][0];
                coords_allies[1][i] = SommeCharEtInt(m[1][0],-i);
                coords_ennemies[0][i] = m[0][1];
                coords_ennemies[1][i] = SommeCharEtInt(m[1][1],-i);
            }
                break;
            case line_vertical_down: {
                coords_allies[0][i] = SommeCharEtInt(m[0][0],i);
                coords_allies[1][i] = m[1][0];
                coords_ennemies[0][i] = SommeCharEtInt(m[0][1],i);
                coords_ennemies[1][i] = m[1][1];
            }
                break;
            case line_vertical_up: {
                coords_allies[0][i] = SommeCharEtInt(m[0][0],-i); // X1 des coordonnes allies prend la valeur de x0 du coup
                coords_allies[1][i] = m[1][0] ; // Y1 des coordonnes allies prend la valeur de y0 du coup
                coords_ennemies[0][i] = SommeCharEtInt(m[0][1],-i); // X2 des coordonnes ennemies prend la valeur de x1 du coup
                coords_ennemies[1][i] = m[1][1]; // Y2 des coordonnes prend la valeur de y0 du coup
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
                coords_allies[0][i] = SommeCharEtInt(m[0][0],-i);
                coords_allies[1][i] = m[1][0];
                coords_ennemies[0][i] = SommeCharEtInt(m[0][1],i);
                coords_ennemies[1][i] = m[1][1];
            }
                break;
            case lateral_three_vertical_x0_up: {
                coords_allies[0][i] = SommeCharEtInt(m[0][0],i);
                coords_allies[1][i] = m[1][0];
                coords_ennemies[0][i] = SommeCharEtInt(m[0][1],-i);
                coords_ennemies[1][i] = m[1][1];
            }
                break;
            case lateral_three_horizontal_y0_right:{
                coords_allies[0][i] = m[0][0];
                coords_allies[1][i] = SommeCharEtInt(m[1][0],i);
                coords_ennemies[0][i] = m[0][1];
                coords_ennemies[1][i] = SommeCharEtInt(m[1][1],-i);
            }
                break;
            case lateral_three_horizontal_y0_left:{
                coords_allies[0][i] = m[0][0];
                coords_allies[1][i] = SommeCharEtInt(m[1][0],-i);
                coords_ennemies[0][i] = m[0][1];
                coords_ennemies[1][i] = SommeCharEtInt(m[1][1],i);
            }
        }
    }
}

char ennemies(Plateau plat,Triple coords_ennemies,char nb_allies){
    char nb_ennemies='0';
    int Int_nb_allies=nb_allies-'0';
    int x;
    int y;
    for(int i=0;i<Int_nb_allies;i++) {

        x=coords_ennemies[0][i]-'0';
        y=coords_ennemies[1][i]-'0';
//        printf("\n\n Coucou d'ennemies ! x: %i / y: %i / Valeur : %c \n\n",x ,y, plat[x][y]);
        if(plat[x][y]==current_player){
            return(error);
        }
        else if(plat[x][y]==no_player){
            return(nb_ennemies);
        }
        else{
            nb_ennemies=SommeCharEtInt(nb_ennemies, 1);
        }
    }
    return(error);
}

char checkColor(Triple coords,char color, char nb_allies, Plateau plat){
//    printf("Coucou de checkColor ! %c %c", color, nb_allies);

    int Int_nb_allies=nb_allies-'0';
    int x;
    int y;
    for(int i=0;i<Int_nb_allies;i++) {

        x=coords[0][i]-'0';
        y=coords[1][i]-'0';
//        printf("Check color :: x_car : %c/ X_int : %i/ Valeur : %c / Couleur : %c\n", coords[0][i],x, plat[x][y], color);
        if(plat[x][y]!=color){
            return(error);
        }
    }
    return(success);
}

char checkMove(Plateau plat, Move m) {

    char type_of_move = whatMove(plat,m);
    char nb_allies = allies(type_of_move,m);
    //Initialisation des actifs (alli�s + ennemis)
    Triple coords_allies;
    Triple coords_ennemies;

    active(m, type_of_move, nb_allies, coords_allies, coords_ennemies);
    char nb_ennemies = ennemies(plat, coords_ennemies, nb_allies);

//    printf("\n Coucou de checkMove ! Type of move %c / nb allies %c / nb ennemies %c\n", type_of_move, nb_allies, nb_ennemies);
    if(nb_ennemies == error){
        return(error);
    }
    //v�rification des couleurs
    if(checkColor(coords_allies,current_player,nb_allies,plat)==error){
        return(error);
    }
    return(success);
}

char pierre(Plateau plat, Move m){;
    int x=m[0][1]-'0';
    int y=m[1][1]-'0';
    if(checkMove(plat,m)==error){
//        printf("%i %i", x,y);
        if(plat[x][y]==current_player){
//            printf("current player\n");
            return(current_player);
        }
        else{
//            printf("other player\n");
            return(error);
        }
    }
//    printf("succes\n");
    return(success);
}

void moveLine(Plateau plat,Move m,Triple coords_ennemies,char nb_ennemies){
    //d�placement des alli�s
    plat[m[0][0]][m[1][0]] = no_player;
    plat[coords_ennemies[0][0]][coords_ennemies[1][0]] = current_player;
    //d�placement des ennemis
    if (nb_ennemies > 0) {
        plat[coords_ennemies[0][nb_ennemies]][coords_ennemies[1][nb_ennemies]] = other_player;
    }
}

void moveLateral(Plateau plat,Triple coords_allies,Triple coords_ennemies, char nb_allies){
    for(char i=0;i<nb_allies;i++){
        plat[coords_allies[0][i]][coords_allies[1][i]]=no_player;
        plat[coords_ennemies[0][i]][coords_ennemies[1][i]]=current_player;
    }
}

void move(Plateau plat,Move m,Triple coords_ennemies,char nb_ennemies,char type_of_move,Triple coords_allies, char nb_allies){
    //d�placement en ligne
    if(type_of_move == line_vertical_down || type_of_move == line_vertical_up ||\
    type_of_move== line_horizontal_left || type_of_move == line_horizontal_right) {
        moveLine(plat,m,coords_ennemies,nb_ennemies);
    }
        //d�placement lat�ral
    else{
        moveLateral(plat,coords_allies,coords_ennemies,nb_allies);
    }
}

char allMove(Plateau plat,Move m){
    char type_of_move = whatMove(plat,m);
    char nb_allies = allies(type_of_move,m);
    if(nb_allies == error){ //si le type de mouvement est error nb_allies renvoie error
        return(error);
    }
    Triple coords_allies;
    Triple coords_ennemies;
    active(m, type_of_move, nb_allies, coords_allies, coords_ennemies);
    char nb_ennemies = ennemies(plat,coords_ennemies,nb_allies);
    char good_color = checkColor(coords_allies,current_player,nb_allies,plat);
    if(nb_ennemies == error || good_color == error){
        return(error);
    }
    move(plat,m,coords_ennemies,nb_ennemies,type_of_move,coords_allies,nb_allies);
    return(success);
}

/// Les fonctions d'affichage :

void display2() {
    printf("\n0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10|\n");
    for (int i=0; i < 10; i++) {
        printf("%i |",i);
        for (int j=0; j < 10; j++) {
            if (plat[i][j] == other_player)
                printf (" B |");
            else if (plat[i][j] == current_player)
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
            if (plat[i][j] == other_player)
                printf (" B |");
            else if (plat[i][j] == current_player)
                printf (" W |" );
            else if (plat[i][j] == '0')
                printf (" . |" );
        }
        printf("\n\n");
    }
}



void AfficherPion(Triple PionAAfficher, int PositionPion){
    printf("[ %c, %c ]", PionAAfficher[0][PositionPion], PionAAfficher[1][PositionPion]);
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
        printf("[%c,", CoupAAfficher[0][0]);
        printf("%c], ", CoupAAfficher[0][1]);
        printf("[%c,", CoupAAfficher[1][0]);
        printf("%c]", CoupAAfficher[1][1]);
}

void AfficherListeCoupsVersionHumaine(){
    for (int i=0;i<tailleListeCoups;i++){
        AfficherCoup(ListeCoups[i]);
        printf(" x1 : %c / ", ListeCoups[i][0][0]);
        printf("y1 : %c / ", ListeCoups[i][1][0]);
        printf("x2 : %c / ", ListeCoups[i][0][1]);
        printf("y2 : %c / ", ListeCoups[i][1][1]);
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
            printf("[[ %c, %c],", ListeDeuxPions[i][0][0], ListeDeuxPions[i][0][1]);
            printf("[ %c, %c]] /// ", ListeDeuxPions[i][1][0], ListeDeuxPions[i][1][1]);
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

void FindAllPions(char Player){ //Idee pour l'am�liorer : comparer avec la liste d'avant, et juste trouver les pions qui manquent

    int compteurPions=0;

    for (int i=0; i < 10; i++) {
        for (int j=0; j < 10; j++) {
                    if(plat[i][j]==Player){
                            char x = i+'0';
                            char y = j+'0';
                            ListePions[compteurPions][0][0]=x;
                            ListePions[compteurPions][0][1]='0';
                            ListePions[compteurPions][0][2]='0';
                            ListePions[compteurPions][1][0]=y;
                            ListePions[compteurPions][1][1]='0';
                            ListePions[compteurPions][1][2]='0';
                            compteurPions = compteurPions + 1;
                    }
            }
    }

    printf("Le nombre de pions est %i\n\n", compteurPions);
}


/// Find All Moves

void FindAllMoves(){

    printf("Coucou\n");

    ListeCoups[0][0][0]='X';
    ListeCoups[0][0][1]='X';
    ListeCoups[0][1][0]='X';
    ListeCoups[0][1][1]='X';

    int compteurCoups=0;

    Triple Tampon;

    for(int i=0;i<14;i++){
            compteurCoups=UneBilleQuatreCoups(ListePions[i], compteurCoups);
    }


    ListeCoups[compteurCoups][0][0]='Y';
    ListeCoups[compteurCoups][0][1]='Y';
    ListeCoups[compteurCoups][1][0]='Y';
    ListeCoups[compteurCoups][1][1]='Y';

    compteurCoups=compteurCoups+1;

    Triple TamponDeuxPions;

    for (int j=0;j<compteurDeuxPions;j++){


        TamponDeuxPions[0][0]= ListeDeuxPions[j][0][0];  //x0
        TamponDeuxPions[0][1]= ListeDeuxPions[j][1][0]; // X1
        TamponDeuxPions[0][2]= '0';                      // x2
        TamponDeuxPions[1][0]= ListeDeuxPions[j][0][1];   // y0
        TamponDeuxPions[1][1]= ListeDeuxPions[j][1][1];   //y1
        TamponDeuxPions[1][2]= '0';                     //y2

        if(ListeDeuxPions[j][0][0]!=ListeDeuxPions[j][1][0]){ // Si X different
           compteurCoups=DeuxBillesQuatreCoupsVertical(TamponDeuxPions, compteurCoups);
        }
        if(ListeDeuxPions[j][0][1]!=ListeDeuxPions[j][1][1]){ // Si Y differenet
            compteurCoups=DeuxBillesQuatreCoupsHorizontal(TamponDeuxPions, compteurCoups);
        }
    }

    ListeCoups[compteurCoups][0][0]='Z';
    ListeCoups[compteurCoups][0][1]='Z';
    ListeCoups[compteurCoups][1][0]='Z';
    ListeCoups[compteurCoups][1][1]='Z';

    compteurCoups=compteurCoups+1;

    // Partie 3 pions

    Triple TamponTroisPions;

    for (int t=0;t<compteurTroisPions;t++){


        TamponTroisPions[0][0]= ListeTroisPions[t][0][0];  //x0
        TamponTroisPions[0][1]= ListeTroisPions[t][0][1]; // X1
        TamponTroisPions[0][2]= ListeTroisPions[t][0][2]; // x2
        TamponTroisPions[1][0]= ListeTroisPions[t][1][0];   // y0
        TamponTroisPions[1][1]= ListeTroisPions[t][1][1];   //y1
        TamponTroisPions[1][2]= ListeTroisPions[t][1][2];   //y2

        printf("Le groupe teste ");
        AfficherPion(TamponTroisPions,0);
        AfficherPion(TamponTroisPions,1);
        AfficherPion(TamponTroisPions,2);

        printf("\n\n");

        if(TamponTroisPions[0][0]!=TamponTroisPions[0][1]){ // Si X different
           compteurCoups=TroisBillesQuatreCoupsVertical(TamponTroisPions, compteurCoups);
        }
        if(TamponTroisPions[1][0]!=TamponTroisPions[1][1]){ // Si Y differenet
            compteurCoups=TroisBillesQuatreCoupsHorizontal(TamponTroisPions, compteurCoups);
        }
    }

    ListeCoups[compteurCoups][0][0]='U';
    ListeCoups[compteurCoups][0][1]='U';
    ListeCoups[compteurCoups][1][0]='U';
    ListeCoups[compteurCoups][1][1]='U';

    compteurCoups=compteurCoups+1;

}


/// La partie 1 billes

int UneBilleQuatreCoups(Triple PionATester, int compteurCoups){


    char xInitial=PionATester[0][0];
    char yInitial=PionATester[1][0];

    char xFinal;
    char yFinal;

    // Coup Haut
    xFinal=xInitial;
    yFinal=yInitial;

    xFinal= SommeCharEtInt(xFinal, -1);
    Move CoupHaut={{xInitial,xFinal}, {yInitial,yFinal}};

    compteurCoups=UneBilleUnCoupHautGauche(CoupHaut, compteurCoups);

    // Coup Bas

    xFinal=xInitial;
    yFinal=yInitial;

    xFinal= SommeCharEtInt(xFinal, 1);
    Move CoupBas={{xInitial,xFinal}, {yInitial,yFinal}};

    compteurCoups=UneBilleUnCoupDroiteBas(CoupBas, compteurCoups);

    // Coup Gauche
    xFinal=xInitial;
    yFinal=yInitial;

    yFinal= SommeCharEtInt(yFinal, -1);
    Move CoupGauche={{xInitial,xFinal}, {yInitial,yFinal}};

    compteurCoups=UneBilleUnCoupHautGauche(CoupGauche, compteurCoups);

    // Coup Droite
    xFinal=xInitial;
    yFinal=yInitial;

    yFinal= SommeCharEtInt(yFinal, 1);
    Move CoupDroite={{xInitial,xFinal}, {yInitial,yFinal}};

    compteurCoups=UneBilleUnCoupDroiteBas(CoupDroite, compteurCoups);

    printf("\n");

    return(compteurCoups);

}

int UneBilleUnCoupHautGauche(Move CoupATester, int compteurCoups){

    char resultat;
    resultat = pierre(plat, CoupATester);

    if (resultat==success){ // Coup autoris�
            ListeCoups[compteurCoups][0][0]=CoupATester[0][0];
            ListeCoups[compteurCoups][0][1]=CoupATester[0][1];
            ListeCoups[compteurCoups][1][0]=CoupATester[1][0];
            ListeCoups[compteurCoups][1][1]=CoupATester[1][1];
            compteurCoups=compteurCoups+1;
    }

//    printf("Une bille un coup : %c %i %i\n\n", resultat, compteurCoups, compteurDeuxPions);

    return(compteurCoups);

    // Si bille blanche : ajouter +1 au compteur, et le groupe � la liste
}

int UneBilleUnCoupDroiteBas(Move CoupATester, int compteurCoups){

    char resultat;
    resultat = pierre(plat, CoupATester);
/*
    printf("ReCoucou de une bille, cette bille : ");
    printf("%c %c", CoupATester[0][0], CoupATester[1][0]);
    printf("\nOn va a cet endroit  : ");
    printf("%c %c\n", CoupATester[0][1], CoupATester[1][1]);
*/

    if (resultat==success){ // Coup autoris�
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

int DeuxBillesQuatreCoupsVertical(Triple GroupeATester, int compteurCoups){ // On change x, pas y

        char xInitial=GroupeATester[0][0]; // Les pions sont dans l'ordre croissant ; la reference sera le premier
        char yInitial=GroupeATester[1][0];

        char xFinal;
        char yFinal;

        xFinal=xInitial;
        yFinal=yInitial;

        // Coup Lateral 1, vers la gauche

        xFinal = SommeCharEtInt(xInitial, 1);
        yFinal = SommeCharEtInt(yInitial, -1);

        Move CoupLateral_Un={{xInitial,xFinal}, {yInitial,yFinal}};

        compteurCoups=DeuxBillesUnCoup(CoupLateral_Un, compteurCoups);

        // Coup Lateral 2, vers la droite

        xFinal = SommeCharEtInt(xInitial, 1);
        yFinal = SommeCharEtInt(yInitial, 1);

        Move CoupLateral2={{xInitial,xFinal}, {yInitial,yFinal}};

        compteurCoups=DeuxBillesUnCoup(CoupLateral2, compteurCoups);

        // Coup Ligne 1, vers le bas !!!!! ATTENTION peut etre 3 billes

        xFinal = SommeCharEtInt(xInitial, 2);
        yFinal = SommeCharEtInt(yInitial, 0);

        Move CoupLigne1={{xInitial,xFinal}, {yInitial,yFinal}};
        compteurCoups=DeuxBillesUnCoupEtPeutEtre3Billes(CoupLigne1, compteurCoups);

        // Coup Ligne 2, vers le haut !!!!ATTENTION AU POINT DE REFERENCE

 //       char x0;
//        char y0;

        char x0 = SommeCharEtInt(xInitial, 1);
        char y0 = yInitial;
        xFinal = SommeCharEtInt(x0, -2);
        yFinal = SommeCharEtInt(y0, 0);

        Move CoupLigne2={{x0,xFinal}, {y0,yFinal}};
        compteurCoups=DeuxBillesUnCoup(CoupLigne2, compteurCoups);

    return(compteurCoups);

}

// Deus billes horizontales :

int DeuxBillesQuatreCoupsHorizontal(Triple GroupeATester, int compteurCoups){

        char xInitial=GroupeATester[0][0]; // Les pions sont dans l'ordre croissant ; la reference sera le premier
        char yInitial=GroupeATester[1][0];

        char xFinal;
        char yFinal;

        xFinal=xInitial;
        yFinal=yInitial;

        // Coup Lateral 1, vers le haut

        xFinal = SommeCharEtInt(xInitial, -1);
        yFinal = SommeCharEtInt(yInitial, 1);

        Move CoupLateral_Un={{xInitial,xFinal}, {yInitial,yFinal}};

        compteurCoups=DeuxBillesUnCoup(CoupLateral_Un, compteurCoups);

        // Coup Lateral 2, vers le bas

        xFinal = SommeCharEtInt(xInitial, 1);
        yFinal = SommeCharEtInt(yInitial, 1);

        Move CoupLateral2={{xInitial,xFinal}, {yInitial,yFinal}};

        compteurCoups=DeuxBillesUnCoup(CoupLateral2, compteurCoups);

        // Coup Ligne 1, vers la droite !!! Peut etre 3 billes

        xFinal = xInitial;
        yFinal = SommeCharEtInt(yInitial, 2);

        Move CoupLigne1={{xInitial,xFinal}, {yInitial,yFinal}};
        compteurCoups=DeuxBillesUnCoupEtPeutEtre3Billes(CoupLigne1, compteurCoups);

        // Coup Ligne 2, vers la gauche !!!! ATTENTION AU POINT DE REFERENCE

        char x0;
        char y0;

        x0 = SommeCharEtInt(xInitial, 0);
        y0 = SommeCharEtInt(yInitial, 1);
        xFinal = SommeCharEtInt(x0, 0);
        yFinal = SommeCharEtInt(y0, -2);

        Move CoupLigne2={{x0,xFinal}, {y0,yFinal}};
        compteurCoups=DeuxBillesUnCoup(CoupLigne2, compteurCoups);

    return(compteurCoups);

}
// La partie 1 avec 3 billes possibles : Horizontal vers la droite, Vertical vers le bas

int DeuxBillesUnCoupEtPeutEtre3Billes(Move CoupATester, int compteurCoups) {

    char resultat;
    resultat = pierre(plat, CoupATester);

    if (resultat==success){ // Coup autoris�
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
             ListeTroisPions[compteurTroisPions][0][1]=SommeCharEtInt(CoupATester[0][0],1);
             ListeTroisPions[compteurTroisPions][1][1]=CoupATester[1][0];
        }
        if(ListeTroisPions[compteurTroisPions][1][0]!=ListeTroisPions[compteurTroisPions][1][2]){ // Y different, donc horizontal
                ListeTroisPions[compteurTroisPions][0][1]=CoupATester[0][0];
                ListeTroisPions[compteurTroisPions][1][1]=SommeCharEtInt(CoupATester[1][0],1);
        }

        compteurTroisPions=compteurTroisPions+1;
    }

    return(compteurCoups);
}


// La partie 1 coup sans 3 billes possibles

int DeuxBillesUnCoup(Move CoupATester, int compteurCoups) {

    char resultat;
    resultat = pierre(plat, CoupATester);

    if (resultat==success){
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


int TroisBillesQuatreCoupsVertical(Triple GroupeATester, int compteurCoups){ // On change x, pas y

        char xInitial=GroupeATester[0][0]; // Les pions sont dans l'ordre croissant ; la reference sera le premier
        char yInitial=GroupeATester[1][0];

        char xFinal;
        char yFinal;

        xFinal=xInitial;
        yFinal=yInitial;

        // Coup Lateral 1, vers la gauche

        xFinal = SommeCharEtInt(xInitial, 2);
        yFinal = SommeCharEtInt(yInitial, -1);

        Move CoupLateral_Un={{xInitial,xFinal}, {yInitial,yFinal}};

        compteurCoups=TroisBillesUnCoup(CoupLateral_Un, compteurCoups);

        // Coup Lateral 2, vers la droite

        xFinal = SommeCharEtInt(xInitial, 2);
        yFinal = SommeCharEtInt(yInitial, 1);

        Move CoupLateral2={{xInitial,xFinal}, {yInitial,yFinal}};

        compteurCoups=TroisBillesUnCoup(CoupLateral2, compteurCoups);

        // Coup Ligne 1, vers le bas !!!!!

        xFinal = SommeCharEtInt(xInitial, 3);
        yFinal = SommeCharEtInt(yInitial, 0);

        Move CoupLigne1={{xInitial,xFinal}, {yInitial,yFinal}};
        compteurCoups=TroisBillesUnCoup(CoupLigne1, compteurCoups);

        // Coup Ligne 2, vers le haut !!!!ATTENTION AU POINT DE REFERENCE

        char x0;
        char y0;

        x0 = SommeCharEtInt(xInitial, 2);
        y0 = yInitial;
        xFinal = SommeCharEtInt(x0, -3);
        yFinal = SommeCharEtInt(y0, 0);

        Move CoupLigne2={{x0,xFinal}, {y0,yFinal}};
        compteurCoups=TroisBillesUnCoup(CoupLigne2, compteurCoups);

}

// Trois billes horizontales

int TroisBillesQuatreCoupsHorizontal(Triple GroupeATester, int compteurCoups){// On change y, pas x

        char xInitial=GroupeATester[0][0]; // Les pions sont dans l'ordre croissant ; la reference sera le premier
        char yInitial=GroupeATester[1][0];

        char xFinal;
        char yFinal;

        xFinal=xInitial;
        yFinal=yInitial;

        // Coup Lateral 1, vers le haut

        xFinal = SommeCharEtInt(xInitial, -1);
        yFinal = SommeCharEtInt(yInitial, 2);

        Move CoupLateral_Un={{xInitial,xFinal}, {yInitial,yFinal}};

        compteurCoups=TroisBillesUnCoup(CoupLateral_Un, compteurCoups);

        // Coup Lateral 2, vers le bas

        xFinal = SommeCharEtInt(xInitial, 1);
        yFinal = SommeCharEtInt(yInitial, 2);

        Move CoupLateral2={{xInitial,xFinal}, {yInitial,yFinal}};

        compteurCoups=TroisBillesUnCoup(CoupLateral2, compteurCoups);

        // Coup Ligne 1, vers la droite !!! Peut etre 3 billes

        xFinal = xInitial;
        yFinal = SommeCharEtInt(yInitial, 3);

        Move CoupLigne1={{xInitial,xFinal}, {yInitial,yFinal}};
        compteurCoups=TroisBillesUnCoup(CoupLigne1, compteurCoups);

        // Coup Ligne 2, vers la gauche !!!! ATTENTION AU POINT DE REFERENCE

        char x0;
        char y0;

        x0 = SommeCharEtInt(xInitial, 0);
        y0 = SommeCharEtInt(yInitial, 2);
        xFinal = SommeCharEtInt(x0, 0);
        yFinal = SommeCharEtInt(y0, -3);

        Move CoupLigne2={{x0,xFinal}, {y0,yFinal}};
        compteurCoups=TroisBillesUnCoup(CoupLigne2, compteurCoups);

    return(compteurCoups);

}

// La partie 1 coup Horizontal


int TroisBillesUnCoup(Move CoupATester, int compteurCoups) {

    char resultat;
    resultat = pierre(plat, CoupATester);


    printf("Le coup demande est : ");
    AfficherCoup(CoupATester);
    printf("\nLe resultat est %c\n", resultat);

    if (resultat==success){
            ListeCoups[compteurCoups][0][0]=CoupATester[0][0];
            ListeCoups[compteurCoups][0][1]=CoupATester[0][1];
            ListeCoups[compteurCoups][1][0]=CoupATester[1][0];
            ListeCoups[compteurCoups][1][1]=CoupATester[1][1];
            compteurCoups=compteurCoups+1;
    }
    return(compteurCoups);
}




/// Le main

int main(){
    printf("\n Uwu ^^\n\n");

    display();

    FindAllPions(current_player);

    AfficherListePions();

    FindAllMoves();

    AfficherListeCoups();

    printf("\n Liste Coups Humaine :\n\n ");

    AfficherListeCoupsVersionHumaine();

    printf("\n Liste 2 pions :\n\n ");

    AfficherListeDeuxPions();

    printf("\n\n Liste 3 pions :\n\n ");

    AfficherListeTroisPions();

    return(0);
}
