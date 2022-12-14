#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_I 10
#define MAX_J 10
#define tailleTableau 10
#define nombrePions 14
#define tailleListeCoups 60

#include "allMove.h"

void FindAllPions(int joueur);

Move ListeCoups[tailleListeCoups];

// Def des types coups

typedef int Pion[2];

//Pion ListePions[14];

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

void AfficherCoup(Move CoupAAfficher);

void AfficherListeCoups();

void AfficherListeDeuxPions();

// Les fonctions de Move :

int TestCoupPossible2(Move CoupATester);

int TestCoupPossible(Move CoupATester);

void FindAllMoves();



int UneBilleQuatreCoups(Pion PionATester, int compteurCoups, char current_player, Plateau plat);

int UneBilleUnCoup(Move CoupATester, int compteurCoups,char current_player,Plateau plat);


// Deux villes :

int DeuxBillesQuatreCoupsHorizontal(DeuxPions GroupeATester, int compteurCoups);

int DeuxBillesQuatreCoupsVertical(DeuxPions GroupeATester, int compteurCoups);


int DeuxBillesUnCoupHorizontal(Move CoupATester, int compteurCoups);

int DeuxBillesUnCoupVertical(Move CoupATester, int compteurCoups);


// Trois billes

int TroisBillesQuatreCoupsVertical(TroisPions GroupeATester, int compteurCoups);

int TroisBillesQuatreCoupsHorizontal(TroisPions GroupeATester, int compteurCoups);

int TroisBillesUnCoupHorizontal(Move CoupATester, int compteurCoups);

int TroisBillesUnCoupVertical(Move CoupATester, int compteurCoups);

// Le Tableau

/*
Plateau plat = {
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
*/

/// Partie affichage

// Afficher le Plateau

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

// Afficher Un Pion

void AfficherEssaiPion(int taille, Pion PionAAfficher){
    for (int i=0;i<taille;i++){
            printf("%i ", PionAAfficher[i]);
    }
}

// Afficher la liste des Pions

void AfficherListePions(Pion ListePions[14]){
    for (int i=0;i<14;i++){
        for (int j=0;j<2;j++){
            printf("%i ", ListePions[i][j]);
        }
    printf(" / ");
    }
}

// Afficher un Move

void AfficherCoup(Move CoupAAfficher){
            printf("[%i,", CoupAAfficher[0][0]);
            printf("%i], ", CoupAAfficher[0][1]);
            printf("[%i,", CoupAAfficher[1][0]);
            printf("%i]", CoupAAfficher[1][1]);
}

// Afficher la liste des Coups

void AfficherListeCoups(){
    for (int i=0;i<tailleListeCoups;i++){
        AfficherCoup(ListeCoups[i]);
        printf(" / ");
        if ((i+1)%3==0){
                printf("\n\n");
        }
    }
}

// AfficherListeDesDeuxPions

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


void FindAllPions(int joueur, Pion ListePions[14]){ //Idee pour l'améliorer : comparer avec la liste d'avant, et juste trouver les pions qui manquent

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



void FindAllMoves(Pion ListePions[14]){

    int compteurCoups=0;
    for (int i=0;i<14;i++){
            compteurCoups=UneBilleQuatreCoups(ListePions[i], compteurCoups, current_player, plat);
    }

}

// Une bille

int UneBilleQuatreCoups(Pion PionATester, int compteurCoups, char current_player, Plateau plat){
    // Move Haut

    Move CoupHaut={{PionATester[0],PionATester[1]}, {(PionATester[0]-1),PionATester[1]}};
    compteurCoups=UneBilleUnCoup(CoupHaut, compteurCoups, current_player, plat);

    // Move Bas

    Move CoupBas={{PionATester[0],PionATester[1]}, {(PionATester[0]+1),PionATester[1]}};
    compteurCoups=UneBilleUnCoup(CoupHaut, compteurCoups, current_player, plat);

    // Move Gauche

    Move CoupGauche={{PionATester[0],PionATester[1]}, {(PionATester[0]),PionATester[1]-1}};
    compteurCoups=UneBilleUnCoup(CoupHaut, compteurCoups, current_player, plat);

    // Move Droite

    Move CoupDroite={{PionATester[0],PionATester[1]}, {(PionATester[0]),PionATester[1]+1}};
    compteurCoups=UneBilleUnCoup(CoupHaut, compteurCoups, current_player, plat);

    return(compteurCoups);

}

// La partie 1 Move


int UneBilleUnCoup(Move CoupATester, int compteurCoups,char current_player,Plateau plat){

    char resultat;
    resultat = pierre(plat,CoupATester,current_player); //pierre abc pierre(Plateau plat, Move m, char current_player)

    if (resultat==success){ //succès def
            ListeCoups[compteurCoups][0][0]=CoupATester[0][0];
            ListeCoups[compteurCoups][0][1]=CoupATester[0][1];
            ListeCoups[compteurCoups][1][0]=CoupATester[1][0];
            ListeCoups[compteurCoups][1][1]=CoupATester[1][1];
            compteurCoups=compteurCoups+1;
    }

    if (resultat==current_player){ //echec bille blanche ghi
        ListeDeuxPions[compteurDeuxPions][0][0]=CoupATester[0][0];
        ListeDeuxPions[compteurDeuxPions][0][1]=CoupATester[0][1];
        ListeDeuxPions[compteurDeuxPions][1][0]=CoupATester[1][0];
        ListeDeuxPions[compteurDeuxPions][1][1]=CoupATester[1][1];
        compteurDeuxPions=compteurDeuxPions+1;


    }
    return(compteurCoups);

    // Si bille blanche : ajouter +1 au compteur, et le groupe à la liste
}




/// Test Move possible

int TestCoupPossible2(Move CoupATester){

    if(CoupATester[0][1]<CoupATester[1][1]){

        return(1);
    }
    else{

        return(3);
    }
};



int TestCoupPossible(Move CoupATester){

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

    AfficherListeCoups();

    printf("\n\n");

}
