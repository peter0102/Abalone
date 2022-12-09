/**
 * \file main.h
 * \brief Fonctions principales du jeu
 * \author Groupe 1
 * \version 0.1
*/

#define MAX_I 10
#define MAX_J 10


typedef char Plateau[MAX_I][MAX_J];
/**
 * \fn display(Plateau p)
 * \brief Affiche l'état actuel du plateau
 * \param p Etat du plateau de jeu
*/
void display(Plateau p);
/**
 * \fn isItWin(Plateau p)
 * \brief Vérifie si il y a un gagnant ou non
 * \param p Etat du plateau de jeu
 * \return 1 si il y a un gagnant
*/
int isItWin(Plateau p);
/**
 * \fn minimax(Plateau p, int depth, int alpha, int beta, bool isMaximizingPlayer)
 * \brief Algorithme MiniMax, qui retourne le score du meilleur mouvement, l'IA maximise son utilité, le joueur minimise l'utilité de l'IA
 * \param p Etat du plateau de jeu
 * \param depth Profondeur voulue de l'arbre
 * \param alpha plus grande valeur pour MAX parmi les successeurs
 * \param beta plus petite valeur pour MIN parmi les successeurs
 * \param isMaximizingPlayer booléen true si on cherche à maximiser l'utilité, false sinon
 * \return Retourne le score le plus haut correspondant au "meilleur" mouvemement
*/
int miniMax(Plateau p,int depth,int alpha,int beta,bool isMaximizingPlayer);
/**
 * \fn aiMove(Plateau p)
 * \brief L'IA effectue un mouvement
 * \param p Etat du plateau de jeu
*/
char aiMove(Plateau p);
/**
 * \fn playerMove(Plateau p)
 * \brief Demande à l'utilisateur d'entrer des coordonnées et effectue le mouvement qui correspond
 * \param p Etat du plateau de jeu
*/
char playerMove(Plateau p);