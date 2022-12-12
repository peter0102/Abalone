/**
 * \file main.h
 * \brief Fonctions principales du jeu
 * \author Groupe 1
 * \version 0.1
*/

/**
 * \fn display(Board b)
 * \brief Affiche de manière primitive le tableau
 * \param b Etat actuel du plateau de jeu
*/
void display(Board b);

/**
 * \fn isItWin(Plateau p)
 * \brief Vérifie si il y a un gagnant ou non
 * \param p Etat du plateau de jeu
 * \return 1 si il y a un gagnant
*/
int isItWin(Board b);

/**
 * \fn playerMove(Plateau p)
 * \brief Demande à l'utilisateur d'entrer des coordonnées et effectue le mouvement qui correspond
 * \param p Etat du plateau de jeu
*/
char playerMove(Plateau p);