#include "global.h"
/**
 * \fn minimax(Board b, int depth, int alpha, int beta, bool isMaximizingPlayer)
 * \brief Algorithme MiniMax, qui retourne le score du meilleur mouvement, l'IA maximise son utilité, le joueur minimise l'utilité de l'IA
 * \param p Etat du plateau de jeu
 * \param depth Profondeur voulue de l'arbre
 * \param alpha plus grande valeur pour MAX parmi les successeurs
 * \param beta plus petite valeur pour MIN parmi les successeurs
 * \param isMaximizingPlayer booléen true si on cherche à maximiser l'utilité, false sinon
 * \return Retourne le score le plus haut correspondant au "meilleur" mouvemement
*/
int miniMax(Board b,int depth,int alpha,int beta,bool isMaximizingPlayer);
/**
 * \fn aiMove(Board b)
 * \brief L'IA effectue un mouvement
 * \param p Etat du plateau de jeu
*/
char aiMove(Board b,char current_player, char other_player);
