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
 * \brief Vérifie s'il y a un gagnant ou non
 * \param board Etat du plateau de jeu
 * \return ERROR s'il y a un gagnant, SUCCESS sinon
*/
char isItWin(Board board);

/**
 * \fn playerMove(Board board,char current_player, char other_player)
 * \brief Demande à l'utilisateur d'entrer des coordonnées et effectue le mouvement qui correspond
 * \param board Etat du plateau de jeu
 * \param current_player couleur du joueur
 * \param other_player joueur adverse
*/
void playerMove(Board board,char current_player, char other_player);