
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "global.h"
#include "ListeDeplacementsString.h"



// Le plateau :


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


/// Les variables "globales"

// Pions uniques

Triple ListePions[14];

// Deux Pions

int compteurDeuxPions;

Triple ListeDeuxPions[100];

// Trois pions

int compteurTroisPions;

Triple ListeTroisPions[100];

// Liste des coups

Move ListeCoups[tailleListeCoups];


/// Les fonctions d'affichage

void display(Board board){
    for (int i=1; i<MAX_I-1; i++){
        for (int j=1; j<MAX_J-1; j++){
            if (board[i][j]==WHITE){
                printf("W | ");
            }
            if (board[i][j]==BLACK){
                printf("B | ");
            }
            if (board[i][j]==EMPTY){
                printf(". | ");
            }
        }
        printf("\n");
    }
}


void DisplayPion(Triple PionAAfficher, int PositionPion){
    printf("[ %i, %i ]", PionAAfficher[0][PositionPion], PionAAfficher[1][PositionPion]);
}

void DisplayListOfPions(){
    printf("[ ");
    for (int i=0;i<13;i++){
        DisplayPion(ListePions[i], 0);
    printf(" / ");
    if ((i+1)%2==0){ // %x pour afficher sur x colonnes
                printf("\n\n");
        }
    }
    DisplayPion(ListePions[13], 0);
    printf(" ]\n");
}

void DisplayMove(Move CoupAAfficher){
        printf("[%i,", CoupAAfficher[0][0]);
        printf("%i], ", CoupAAfficher[0][1]);
        printf("[%i,", CoupAAfficher[1][0]);
        printf("%i]", CoupAAfficher[1][1]);
}

void DisplayListOfMove(){
    for (int i=0;i<tailleListeCoups;i++){
        DisplayMove(ListeCoups[i]);
        printf(" / ");
        if ((i+1)%3==0){ // %x pour afficher sur x colonnes
                printf("\n\n");
        }
    }
}

void DisplayListOfMoveNormalVersion(){
    for (int i=0;i<tailleListeCoups;i++){
        DisplayMove(ListeCoups[i]);
        printf(" x1 : %i / ", ListeCoups[i][0][0]);
        printf("y1 : %i / ", ListeCoups[i][1][0]);
        printf("x2 : %i / ", ListeCoups[i][0][1]);
        printf("y2 : %i / ", ListeCoups[i][1][1]);
        printf(" \n");

    }
}



void DisplayListOfTwoPions(){
    for (int i=0;i<compteurDeuxPions;i++){
            printf("[[ %i, %i],", ListeDeuxPions[i][0][0], ListeDeuxPions[i][0][1]);
            printf("[ %i, %i]] /// ", ListeDeuxPions[i][1][0], ListeDeuxPions[i][1][1]);
            if ((i+1)%2==0){ // modulo X pour X colonnes
                printf("\n\n");
        }
    }
}

void DisplayListOfThreePions(){
    for (int i=0;i<compteurTroisPions;i++){
            DisplayPion(ListeTroisPions[i],0);
            printf(" , ");
            DisplayPion(ListeTroisPions[i],1);
            printf(" , ");
            DisplayPion(ListeTroisPions[i],2);
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

    FindAllPions(current_player);

    printf("Coucou\n");

    int compteurCoups=0;

    compteurDeuxPions=0;

    compteurTroisPions=0;

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


char* Traduire(int longueurListe){
    char* mTotal=malloc(longueurListe*6);
    char ChaineVide[]={';'};
    char* m=malloc(6);

    for(int i=0;i<longueurListe;i++){
        m=translateMoveReverse(ListeCoups[i]);
        mTotal = strncat(mTotal, m, 5);
        mTotal = strncat(mTotal, ChaineVide, 1);
    }

	return(mTotal);
}

