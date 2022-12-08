/**
 * \file Evaluate.h
 * \brief Fonctions relatives à l'évaluation de chaque mouvement
 * \author Groupe 1
 * \version 0.1
*/


#define MAX_I 10
#define MAX_J 10

typedef char Plateau[MAX_I][MAX_J];
int victory(Plateau p);
int loss(Plateau p);
int density(Plateau p,char currentPlayer,int alpha);
/**
 * \fn distanceToCenter(Plateau p)
 * \brief Evalue le score d'un mouvement en fonction de sa distance au centre
 * \param p Etat du plateau de jeu
 * return Le score du meilleur mouvement possible (en fonction de la distance au centre)
*/
int distanceToCenter(Plateau p);
