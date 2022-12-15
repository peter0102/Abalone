/**
 * \file lmove.h
 * \brief Fonctions relatives à la vérification et au déplacement effectif
 * \author Groupe 1
 * \version 0.1
*/

void movecopy(Move* to, Move from);
char lmove(Board board, char current_player, Move list_possible_moves[56]);