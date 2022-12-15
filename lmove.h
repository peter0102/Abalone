/**
 * \file lmove.h
 * \brief Fonctions relatives à la vérification et au déplacement effectif
 * \author Groupe 1
 * \version 0.1
*/

/**
 * \fn movecopy(Move* to, Move from)
 * \brief Copie les valeurs d'un Move dans un autre
 * \param to pointeur vers le Move dont on veut modifier les valeurs
 * \param from Move dont on veut copier les valeurs
*/
void movecopy(Move* to, Move from);

/**
 * \fn checkColor(Triple coords,char color, char nb_allies, Board board)
 * \brief Vérifie que les coordonnées soient toutes de la même couleur
 * \param board plateau de jeu
 * \param current_player couleur du joueur à ce tour
 * \param nb_alist_possible_moves liste des moves possibles (les valeurs seront écrasées)
 * \return Nombre de coups possibles
*/
char lmove(Board board, char current_player, Move list_possible_moves[56]);