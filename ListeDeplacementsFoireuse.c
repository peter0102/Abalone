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
//définition des types
typedef char Plateau[10][10];
typedef char Move[2][2];
typedef char Triple[2][3];
typedef int Coup[2][2]; //x ou y puis x0 1 ou 2
//fonctions

char absChar(char v){
    if(v<0){
        return(-v);
    }
    else{
        return(v);
    }
}

char whatMove(Plateau plat,Move m) {
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

char ennemies(Plateau plat,Triple coords_ennemies,char nb_allies){
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

int checkMove(Plateau plat, Coup m) {
    char type_of_move = whatMove(plat,m);
    char nb_allies = allies(type_of_move,m);
    //Initialisation des actifs (alliés + ennemis)
    Triple coords_allies;
    Triple coords_ennemies;
    active(m, type_of_move, nb_allies, coords_allies, coords_ennemies);
    char nb_ennemies = ennemies(plat, coords_ennemies, nb_allies);
    if(nb_ennemies == error){
        return(1);
    }
    //vérification des couleurs
    if(checkColor(coords_allies,current_player,nb_allies,plat)==error){
        return(1);
    }
    return(2);
}


int pierre(Plateau plat, Coup m){
    if(checkMove(plat,m)==1){
        if(plat[m[1][0]][m[1][1]]==1){
            return(2); // Si la bille est de même couleur : renvoie 2
        }
        else{
            return(3); // Si la bille est de couleur différente : renvoie 3
        }
    }
    return(1); // Si le coup est autorisé : renvoie 1
}

void moveLine(Plateau plat,Move m,Triple coords_ennemies,char nb_ennemies){
    //déplacement des alliés
    plat[m[0][0]][m[1][0]] = no_player;
    plat[coords_ennemies[0][0]][coords_ennemies[1][0]] = current_player;
    //déplacement des ennemis
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
    //déplacement en ligne
    if(type_of_move == line_vertical_down || type_of_move == line_vertical_up ||\
    type_of_move== line_horizontal_left || type_of_move == line_horizontal_right) {
        moveLine(plat,m,coords_ennemies,nb_ennemies);
    }
        //déplacement latéral
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





/// Zeéyj"hrptngo


/// aegzlrerb,nf


///azefogrtn,k

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct {
    /*! Ligne du point de départ (lettre) */
    int x1;
    /*! Colonne du point de départ (chiffre) */
    int y1;
    /*! Ligne du point d'arrivée (lettre) */
    int x2;
    /*! Colonne du point d'arrivée (chiffre) */
    int y2;} coords;

struct coordPion {
    int x;
    int y;
} ;


#define MAX_I 10
#define MAX_J 10
#define tailleTableau 10
#define nombrePions 14
#define tailleListeCoups 80

void FindAllPions(int joueur);


typedef int Tableau[MAX_I][MAX_J];



// typedef int Coup[2][2];

typedef char Move[2][2];

Coup ListeCoups[tailleListeCoups];

// Def des types coups

typedef int Pion[2];

Pion ListePions[14];


typedef Pion DeuxPions[2];

DeuxPions ListeDeuxPions[100];

int compteurDeuxPions;


typedef Pion TroisPions[3];

int compteurTroisPions;

TroisPions ListeTroisPions[100];


// Les affichages

void display();

void AfficherEssaiPion(int taille, Pion PionAAfficher);

void AfficherListePions();

void AfficherCoup(Coup CoupAAfficher);

void AfficherListeCoups();

void AfficherListeDeuxPions();

// Les fonctions de coup :

int TestCoupPossible2(Coup CoupATester);

int TestCoupPossible(Coup CoupATester);

void FindAllMoves();



int UneBilleQuatreCoups(Pion PionATester, int compteurCoups);

int UneBilleUnCoup(Coup CoupATester, int compteurCoups);


// Deux villes :

int DeuxBillesQuatreCoupsHorizontal(DeuxPions GroupeATester, int compteurCoups);

int DeuxBillesQuatreCoupsVertical(DeuxPions GroupeATester, int compteurCoups);


int DeuxBillesUnCoupHorizontal(Coup CoupATester, int compteurCoups);

int DeuxBillesUnCoupVertical(Coup CoupATester, int compteurCoups);


// Trois billes

int TroisBillesQuatreCoupsVertical(TroisPions GroupeATester, int compteurCoups);

int TroisBillesQuatreCoupsHorizontal(TroisPions GroupeATester, int compteurCoups);

int TroisBillesUnCoupHorizontal(Coup CoupATester, int compteurCoups);

int TroisBillesUnCoupVertical(Coup CoupATester, int compteurCoups);

// Le Tableau

Tableau plat = {
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 1, 1, 0, 1, 1, 1, 1, 1, 0},
{0, 0, 1, 1, 1, 0, 1, 1, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 2, 2, 2, 2, 2, 2, 0, 0},
{0, 2, 2, 2, 2, 2, 2, 2, 2, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };


int pierre(Plateau plat, Coup m);

int checkMove(Plateau plat, Coup m);

// Afficher le tableau, les Pions, la listePion

void display() {
    printf("\n");
    for (int i=0; i < MAX_I; i++) {
        for (int j=0; j < MAX_J; j++) {
            if (plat[i][j] == 2)
                printf (" B | ");
            else if (plat[i][j] == 1)
                printf (" W | " );
            else if (plat[i][j] == 0)
                printf (" . | " );
        }
        printf("\n\n");
    }
}


void AfficherEssaiPion(int taille, Pion PionAAfficher){
    for (int i=0;i<taille;i++){
            printf("%i ", PionAAfficher[i]);
    }
}

void AfficherListePions(){
    for (int i=0;i<14;i++){
        for (int j=0;j<2;j++){
            printf("%i ", ListePions[i][j]);
        }
    printf(" / ");
    }
}

void AfficherCoup(Coup CoupAAfficher){
            printf("[%i,", CoupAAfficher[0][0]);
            printf("%i], ", CoupAAfficher[0][1]);
            printf("[%i,", CoupAAfficher[1][0]);
            printf("%i]", CoupAAfficher[1][1]);
}

void AfficherListeCoups(){
    for (int i=0;i<tailleListeCoups;i++){
        AfficherCoup(ListeCoups[i]);
        printf(" / ");
        if ((i+1)%3==0){
                printf("\n\n");
        }
    }
}

void AfficherListeDeuxPions(){
    for (int i=0;i<compteurDeuxPions;i++){
        AfficherCoup(ListeDeuxPions[i]);
        printf(" / ");
        if ((i+1)%5==0){
                printf("\n\n");
        }
    }
}

// Trouver tous les pions d'un joueur


void FindAllPions(int joueur){ //Idee pour l'améliorer : comparer avec la liste d'avant, et juste trouver les pions qui manquent

    int compteurPions=0;

    for (int i=0; i < MAX_I; i++) {
        for (int j=0; j < MAX_J; j++) {
                    if(plat[i][j]==joueur){
                            ListePions[compteurPions][0]=i;
                            ListePions[compteurPions][1]=j;
                            compteurPions = compteurPions + 1;
                    }
            }
    }

    printf("Le nombre de pions est %i\n\n", compteurPions);
}


/// Trouver tous les moves
/// -----------------------



void FindAllMoves(){

    int compteurCoups=0;
    for (int i=0;i<14;i++){
            compteurCoups=UneBilleQuatreCoups(ListePions[i], compteurCoups);
    }

    ListeCoups[compteurCoups][0][0]=1000;
    ListeCoups[compteurCoups][0][1]=1000;
    ListeCoups[compteurCoups][1][0]=1000;
    ListeCoups[compteurCoups][1][1]=1000;

    compteurCoups=compteurCoups+1;

    DeuxPions TamponDeuxPions;

    for (int j=0;j<compteurDeuxPions;j++){

        TamponDeuxPions[0][0]= ListeDeuxPions[j][0][0];
        TamponDeuxPions[0][1]= ListeDeuxPions[j][0][1];
        TamponDeuxPions[1][0]= ListeDeuxPions[j][1][0];
        TamponDeuxPions[1][1]= ListeDeuxPions[j][1][1];

        if(ListeDeuxPions[j][0][0]!=ListeDeuxPions[j][1][0]){
           compteurCoups=DeuxBillesQuatreCoupsVertical(TamponDeuxPions, compteurCoups);
        }
        else{
            compteurCoups=DeuxBillesQuatreCoupsHorizontal(TamponDeuxPions, compteurCoups);
        }
    }

}

// Une bille

int UneBilleQuatreCoups(Pion PionATester, int compteurCoups){
    // Coup Haut

    Coup CoupHaut={{PionATester[0],PionATester[1]}, {(PionATester[0]-1),PionATester[1]}};
    compteurCoups=UneBilleUnCoup(CoupHaut, compteurCoups);

    // Coup Bas

    Coup CoupBas={{PionATester[0],PionATester[1]}, {(PionATester[0]+1),PionATester[1]}};
    compteurCoups=UneBilleUnCoup(CoupBas, compteurCoups);

    // Coup Gauche

    Coup CoupGauche={{PionATester[0],PionATester[1]}, {(PionATester[0]),PionATester[1]-1}};
    compteurCoups=UneBilleUnCoup(CoupGauche, compteurCoups);

    // Coup Droite

    Coup CoupDroite={{PionATester[0],PionATester[1]}, {(PionATester[0]),PionATester[1]+1}};
    compteurCoups=UneBilleUnCoup(CoupDroite, compteurCoups);

    return(compteurCoups);

}

// La partie 1 coup


int UneBilleUnCoup(Coup CoupATester, int compteurCoups){

    int resultat= 0;
    resultat = pierre(plat, CoupATester);

    if (resultat==1){ // Coup autorisé
            ListeCoups[compteurCoups][0][0]=CoupATester[0][0];
            ListeCoups[compteurCoups][0][1]=CoupATester[0][1];
            ListeCoups[compteurCoups][1][0]=CoupATester[1][0];
            ListeCoups[compteurCoups][1][1]=CoupATester[1][1];
            compteurCoups=compteurCoups+1;
    }

    if (resultat==2){ // Bille de même couleur
        ListeDeuxPions[compteurDeuxPions][0][0]=CoupATester[0][0];
        ListeDeuxPions[compteurDeuxPions][0][1]=CoupATester[0][1];
        ListeDeuxPions[compteurDeuxPions][1][0]=CoupATester[1][0];
        ListeDeuxPions[compteurDeuxPions][1][1]=CoupATester[1][1];
        compteurDeuxPions=compteurDeuxPions+1;


    }
    return(compteurCoups);

    // Si bille blanche : ajouter +1 au compteur, et le groupe à la liste
}

/// La partie 2 billes


// Deus billes verticales :

int DeuxBillesQuatreCoupsVertical(DeuxPions GroupeATester, int compteurCoups){

        Pion PionReference;
        if(GroupeATester[0][0]<GroupeATester[1][0]){
            PionReference[0]=GroupeATester[0][0];
            PionReference[1]=GroupeATester[0][1];
        }
        else{
            PionReference[0]=GroupeATester[1][0];
            PionReference[1]=GroupeATester[1][1];
        }

        // Coup Lateral 1

        Coup CoupLateral_Un={{PionReference[0],PionReference[1]}, {(PionReference[0]+1),PionReference[1]-1}};
        compteurCoups=DeuxBillesUnCoupVertical(CoupLateral_Un, compteurCoups);

        // Coup Lateral 2

        Coup CoupLateral2={{PionReference[0],PionReference[1]}, {(PionReference[0]+1),PionReference[1]+1}};
        compteurCoups=DeuxBillesUnCoupVertical(CoupLateral2, compteurCoups);

        // Coup Ligne 1

        Coup CoupLigne1={{PionReference[0],PionReference[1]}, {(PionReference[0]-1),PionReference[1]}};
        compteurCoups=DeuxBillesUnCoupVertical(CoupLigne1, compteurCoups);

        // Coup Ligne 2

        Coup CoupLigne2={{PionReference[0],PionReference[1]}, {(PionReference[0]+2),PionReference[1]}};
        compteurCoups=DeuxBillesUnCoupVertical(CoupLigne2, compteurCoups);

    return(compteurCoups);

}

// Deus billes horizontales :

int DeuxBillesQuatreCoupsHorizontal(DeuxPions GroupeATester, int compteurCoups){

        Pion PionReference;

        if(GroupeATester[0][1]<GroupeATester[1][1]){
            PionReference[0]=GroupeATester[0][0];
            PionReference[1]=GroupeATester[0][1];
        }
        else{
            PionReference[0]=GroupeATester[1][0];
            PionReference[1]=GroupeATester[1][1];
        }

        // Coup Lateral 1

        Coup CoupLateral_Un={{PionReference[0],PionReference[1]}, {(PionReference[0]-1),(PionReference[1]+1)}};
        compteurCoups=DeuxBillesUnCoupHorizontal(CoupLateral_Un, compteurCoups);

        // Coup Lateral 2

        Coup CoupLateral2={{PionReference[0],PionReference[1]}, {(PionReference[0]+1),(PionReference[1]+1)}};
        compteurCoups=DeuxBillesUnCoupHorizontal(CoupLateral2, compteurCoups);

        // Coup Ligne 1

        Coup CoupLigne1={{PionReference[0],PionReference[1]}, {(PionReference[0]),(PionReference[1]-1)}};
        compteurCoups=DeuxBillesUnCoupHorizontal(CoupLigne1, compteurCoups);

        // Coup Ligne 2

        Coup CoupLigne2={{PionReference[0],PionReference[1]}, {(PionReference[0]),(PionReference[1]+22)}};
        compteurCoups=DeuxBillesUnCoupHorizontal(CoupLigne2, compteurCoups);

    return(compteurCoups);

}
// La partie 1 coup Horizontal


int DeuxBillesUnCoupHorizontal(Coup CoupATester, int compteurCoups) {

    int resultat= 0;
    resultat = TestCoupPossible(CoupATester);

    if (resultat==1){ // Coup autorisé
            ListeCoups[compteurCoups][0][0]=CoupATester[0][0];
            ListeCoups[compteurCoups][0][1]=CoupATester[0][1];
            ListeCoups[compteurCoups][1][0]=CoupATester[1][0];
            ListeCoups[compteurCoups][1][1]=CoupATester[1][1];
            compteurCoups=compteurCoups+1;
    }
    if (resultat==2){ // Bille de même couleur
        ListeTroisPions[compteurTroisPions][0][0]=CoupATester[0][0];
        ListeTroisPions[compteurTroisPions][0][1]=CoupATester[0][1];
        ListeTroisPions[compteurTroisPions][1][0]=CoupATester[1][0];
        ListeTroisPions[compteurTroisPions][1][1]=CoupATester[1][1];
        compteurTroisPions=compteurTroisPions+1;
    }

    return(compteurCoups);
}


// La partie 1 coup Vertical

int DeuxBillesUnCoupVertical(Coup CoupATester, int compteurCoups) {

    int resultat= 0;
    resultat = TestCoupPossible(CoupATester);

    if (resultat==1){
            ListeCoups[compteurCoups][0][0]=CoupATester[0][0];
            ListeCoups[compteurCoups][0][1]=CoupATester[0][1];
            ListeCoups[compteurCoups][1][0]=CoupATester[1][0];
            ListeCoups[compteurCoups][1][1]=CoupATester[1][1];
            compteurCoups=compteurCoups+1;
    }
    if (resultat==2){
        ListeTroisPions[compteurTroisPions][0][0]=CoupATester[0][0];
        ListeTroisPions[compteurTroisPions][0][1]=CoupATester[0][1];
        ListeTroisPions[compteurTroisPions][1][0]=CoupATester[1][0];
        ListeTroisPions[compteurTroisPions][1][1]=CoupATester[1][1];
        compteurTroisPions=compteurTroisPions+1;
    }
    return(compteurCoups);
}


/// La partie 3 billes

// 3 Billes 4 Coups Vertical


int TroisBillesQuatreCoupsVertical(TroisPions GroupeATester, int compteurCoups){

// Trouver le pion référence

        Pion PionReference;
        if(GroupeATester[0][0]<GroupeATester[1][0]){
                if(GroupeATester[0][0]<GroupeATester[2][0]){
                        PionReference[0]=GroupeATester[0][0];
                        PionReference[1]=GroupeATester[0][1];
                }
                else{
                        PionReference[0]=GroupeATester[2][0];
                        PionReference[1]=GroupeATester[2][1];
                }
        }
        else{
            if(GroupeATester[1][0]<GroupeATester[2][0]){
                        PionReference[0]=GroupeATester[1][0];
                        PionReference[1]=GroupeATester[1][1];
            }
                else{
                        PionReference[0]=GroupeATester[2][0];
                        PionReference[1]=GroupeATester[2][1];
                }
        }

        // Coup Lateral 1

        Coup CoupLateral_Un={{PionReference[0],PionReference[1]}, {(PionReference[0]+2),PionReference[1]-1}};
        compteurCoups=TroisBillesUnCoupVertical(CoupLateral_Un, compteurCoups);

        // Coup Lateral 2

        Coup CoupLateral2={{PionReference[0],PionReference[1]}, {(PionReference[0]+2),PionReference[1]+1}};
        compteurCoups=TroisBillesUnCoupVertical(CoupLateral2, compteurCoups);

        // Coup Ligne 1

        Coup CoupLigne1={{PionReference[0],PionReference[1]}, {(PionReference[0]-1),PionReference[1]}};
        compteurCoups=TroisBillesUnCoupVertical(CoupLigne1, compteurCoups);

        // Coup Ligne 2

        Coup CoupLigne2={{PionReference[0],PionReference[1]}, {(PionReference[0]+3),PionReference[1]}};
        compteurCoups=TroisBillesUnCoupVertical(CoupLigne2, compteurCoups);

    return(compteurCoups);

}

// Trois billes latérales

int TroisBillesQuatreCoupsHorizontal(TroisPions GroupeATester, int compteurCoups){

        Pion PionReference;
        if(GroupeATester[0][1]<GroupeATester[1][1]){
                if(GroupeATester[0][1]<GroupeATester[2][1]){
                        PionReference[0]=GroupeATester[0][0];
                        PionReference[1]=GroupeATester[0][1];
                }
                else{
                        PionReference[0]=GroupeATester[2][0];
                        PionReference[1]=GroupeATester[2][1];
                }
        }
        else{
            if(GroupeATester[1][1]<GroupeATester[2][1]){
                        PionReference[0]=GroupeATester[1][0];
                        PionReference[1]=GroupeATester[1][1];
            }
                else{
                        PionReference[0]=GroupeATester[2][0];
                        PionReference[1]=GroupeATester[2][1];
                }
        }


        // Coup Lateral 1

        Coup CoupLateral_Un={{PionReference[0],PionReference[1]}, {(PionReference[0]-1),(PionReference[1]+2)}};
        compteurCoups=TroisBillesUnCoupHorizontal(CoupLateral_Un, compteurCoups);

        // Coup Lateral 2

        Coup CoupLateral2={{PionReference[0],PionReference[1]}, {(PionReference[0]+1),(PionReference[1]+2)}};
        compteurCoups=TroisBillesUnCoupHorizontal(CoupLateral2, compteurCoups);

        // Coup Ligne 1

        Coup CoupLigne1={{PionReference[0],PionReference[1]}, {(PionReference[0]),(PionReference[1]-1)}};
        compteurCoups=TroisBillesUnCoupHorizontal(CoupLigne1, compteurCoups);

        // Coup Ligne 2

        Coup CoupLigne2={{PionReference[0],PionReference[1]}, {(PionReference[0]),(PionReference[1]+3)}};
        compteurCoups=TroisBillesUnCoupHorizontal(CoupLigne2, compteurCoups);

    return(compteurCoups);

}
// La partie 1 coup Horizontal


int TroisBillesUnCoupHorizontal(Coup CoupATester, int compteurCoups) {

    int resultat= 0;
    resultat = TestCoupPossible(CoupATester);

    if (resultat==3){
            ListeCoups[compteurCoups][0][0]=CoupATester[0][0];
            ListeCoups[compteurCoups][0][1]=CoupATester[0][1];
            ListeCoups[compteurCoups][1][0]=CoupATester[1][0];
            ListeCoups[compteurCoups][1][1]=CoupATester[1][1];
            compteurCoups=compteurCoups+1;
    }
    return(compteurCoups);
}

// La partie 1 coup Vertical

int TroisBillesUnCoupVertical(Coup CoupATester, int compteurCoups) {

    int resultat= 0;
    resultat = TestCoupPossible(CoupATester);

    if (resultat==3){
            ListeCoups[compteurCoups][0][0]=CoupATester[0][0];
            ListeCoups[compteurCoups][0][1]=CoupATester[0][1];
            ListeCoups[compteurCoups][1][0]=CoupATester[1][0];
            ListeCoups[compteurCoups][1][1]=CoupATester[1][1];
            compteurCoups=compteurCoups+1;
    }
    return(compteurCoups);
}








/// Test coup possible

int TestCoupPossible2(Coup CoupATester){

    if(CoupATester[0][1]<CoupATester[1][1]){

        return(1);
    }
    else{

        return(3);
    }
};


/// Coups possibles


/*
int TestCoupPossible2(Coup CoupATester){
    int x=CoupATester[1][0];
    int y=CoupATester[1][1];

    if (plat[x][y]==1){
            return(1);
    }
    else{
            return(3);
    }
}
*/

int TestCoupPossible(Coup CoupATester){

    return(3);

}


// Le main


int main(){

    display();

    FindAllPions(1);

//    AfficherListePions();

    printf("\n\n");


    FindAllMoves();

    printf("\n\n");

//    AfficherListeCoups();

    printf("\n\n");

    printf("Uwu \n\n");

    AfficherListeDeuxPions();

    printf("\n\n\n\n ");

    printf("Dylan trop cute ^^\n\n");

    AfficherListeCoups();

    printf("\n\n");

}





/*
    Coup TamponCoup={{2,2},{2,3}};

    AfficherCoup(TamponCoup);

    printf("\n\n");
*/
