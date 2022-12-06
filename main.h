/**
 * \file main.h
 * \brief Fonctions principales du jeu
 * \author Groupe 1
 * \version 0.1
*/

#define MAX_I 10
#define MAX_J 10

int turn(int current_turn);

typedef char Plateau[MAX_I][MAX_J];
void display ();

int isItWin(Plateau p);