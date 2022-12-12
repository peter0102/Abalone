/**
 * \file move.h
 * \brief Fonctions relatives à la structure de déplacement
 * \author Groupe 1
 * \version 0.1
*/
#include "global.h"

/**
 * \fn moveChrConvert(char chr, char type)
 * \brief Convertit un caractère de coordonnée (entre A et H ou entre 1 et 8) en index
 * \param chr Caractère à convertir
 * \param type Type de caractère (l = lettre ; n = nombre)
 * \return Index sous forme de caractère utilisé comme un int correspondant au caractère d'entrée (-1 en cas de caractère incorrect)
*/
char moveChrConvert(char chr, char type);

/**
 * \fn moveChrConvertReverse (int index, char type)
 * \brief Convertit un index de déplacement en caractère de coordonnée (entre A et H ou entre 1 et 8)
 * \param index Index à convertir (caractère utilisé comme un int)
 * \param type Type de caractère (l = lettre ; n = nombre)
 * \return Caractère (lettre ou chiffre) correspondant à l'index d'entrée ('x' en cas d'index incorrect)
*/
char moveChrConvertReverse (char index, char type);

/**
 * \fn translateMove(char* input)
 * \brief Traduit les coordonnées entrées (comme F6:E5) en index comme {{6, 6}, {5, 5}}
 * \param input Chaîne de caractères des coordonnées (ex: A1:B2)
 * \return Coordonnées numériques des points de départ et d'arrivée ({{-1, -1}, {-1, -1}} en cas d'erreur)
*/
Move translateMove(char* input);

/**
 * \fn translateMoveReverse(char* input)
 * \brief Traduit le déplacement entré (comme {{6, 6}, {5, 5}}) en chaîne de caractères comme 'F6:E5'
 * \param move Déplacement à traduire
 * \return Chaîne de caractères correspondant au mouvement entré
*/
char* translateMoveReverse(Move move);

/**
 * \fn createMove(int x1, int y1, int x2, int y2)
 * \brief Crée un mouvement de type Move à partir des 4 coordonées x1, y1, x2 et y2
 * \param x1 Ligne de la première case
 * \param y1 Colonne de la première case
 * \param x2 Ligne de la deuxième case
 * \param y2 Colonne de la deuxième case
 * \return Mouvement en format Move
*/
Move createMove(int x1, int y1, int x2, int y2);

/**
 * \fn printMove(Coords coords)
 * \brief Affiche un déplacement
 * \param move Déplacement à afficher
*/
void printMove(Move move);