/**
 * \file main.h
 * \brief Fonctions principales du jeu
 * \author Groupe 1
 * \version 0.1
*/

/**
 * \fn display(Board board)
 * \brief Affiche de manière primitive le tableau
 * \param board Etat actuel du plateau de jeu
*/
void display(Board board);

/**
 * \fn isItWin(Board board)
 * \brief Vérifie si il y a un gagnant ou non
 * \param board Etat du plateau de jeu
 * \return 1 si il y a un gagnant
*/
char isItWin(Board board);

/**
 * \fn playerMove(Board board)
 * \brief Demande à l'utilisateur d'entrer des coordonnées et effectue le mouvement qui correspond
 * \param board Etat du plateau de jeu
*/
char playerMove(Board board);

void nextTurn(GameData* gd, Move move);