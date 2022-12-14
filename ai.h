/**
 * \file ai.h
 * \brief Fonctions relatives à à l'IA
 * \author Groupe 1
 * \version 0.1
*/
/**
 * \fn miniMax(Board board, int depth, int alpha, int beta, bool isMaximizingPlayer)
 * \brief Algorithme MiniMax, qui retourne le score du meilleur mouvement, l'IA maximise son utilité, le joueur minimise l'utilité de l'IA
 * \param board Etat du plateau de jeu
 * \param depth Profondeur voulue de l'arbre
 * \param alpha plus grande valeur pour MAX parmi les successeurs
 * \param beta plus petite valeur pour MIN parmi les successeurs
 * \param isMaximizingPlayer booléen true si on cherche à maximiser l'utilité, false sinon
 * \return Retourne le score le plus haut correspondant au "meilleur" mouvemement
*/
int miniMax(Board board,int depth,int alpha,int beta,bool isMaximizingPlayer);
/**
 * \fn aiBestMove(Move move, Board board,char current_player, char other_player)
 * \brief Retourne le meilleur déplacement de l'IA à travers move
 * \param move Déplacement à écrire
 * \param board Etat du plateau de jeu
 * \param current_player Quel couleur effectue le mouvement
 * \param other_player Couleur adverse
*/
void aiBestMove(Move move, Board board,char current_player, char other_player);
