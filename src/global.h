/**
 * \file global.h
 * \brief Bibliothèque contenant les define et fonctions communes à plusieurs modules
 * \author Groupe 1
 * \version 0.1
*/

/**
 * \brief Nombre de lignes du plateau
*/
#define MAX_I 10
/**
 * \brief Nombre de colonnes du plateau
*/
#define MAX_J 10
/**
 * \brief Nombre affecté a l'infini
*/
#define INFTY 147483648


//Pions
/**
 * \brief Nombre de pions par joueurs
*/
#define PAWN_NB 14
/**
 * \brief case vide
*/
#define EMPTY '0'
/**
 * \brief case avec pions blancs
*/
#define WHITE 'W'
/**
 * \brief case avec pions noirs
*/
#define BLACK 'B'


// Types de déplacement

/**
 * \brief déplacement en ligne vers la droite
*/
#define LINE_HOR_RIGHT 'a'
/**
 * \brief déplacement en ligne vers la gauche
*/
#define LINE_HOR_LEFT 'b'
/**
 * \brief déplacement ligne vers le bas
*/
#define LINE_VER_DOWN 'c'
/**
 * \brief  déplacement en ligne vers le haut
*/
#define LINE_VER_UP 'd'

/**
 * \brief déplacement latéral d'un doublet positioné horizontalement
*/
#define LAT_2_HOR 'e'
/**
 * \brief déplacement latéral d'un doublet positioné verticalement
*/
#define LAT_2_VER 'f'

/**
 * \brief déplacement latéral vers le bas d'un triplet
*/
#define LAT_3_VER_X0_DOWN 'g'
/**
 * \brief déplacement latéral vers le haut d'un triplet
*/
#define LAT_3_VER_X0_UP 'h'
/**
 * \brief  déplacement latéral vers la droite  d'un triplet
*/
#define LAT_3_HOR_Y0_RIGHT 'i'
/**
 * \brief déplacement latéral vers la gauche d'un triplet
*/
#define LAT_3_HOR_Y0_LEFT 'j'


// Gestion d'erreur
/**
 * \brief message d'erreur
*/
#define ERROR 'x'
/**
 * \brief message de succès
*/
#define SUCCESS 'l'

//Définition des types
typedef char Board[MAX_I][MAX_J]; //caractères ASCII
typedef char Move[2][2]; //Mouvement {{x0,x1},{y0,y1}} valeurs numériques
typedef char Triple[2][3]; //coordonnées d'un joueur {{xj0,xj1,xj2},{yj0,yj1,yj2}} valeurs numériques

/**
* \fn otherPlayer(char player)
* \brief Sélectionne et renvoie l'autre joueur (par rapport au joueur 'player')
* \param player Joueur dont on souhaite connaître l'adversaire
* \return WHITE si player = BLACK et vice-versa (ERROR si player est incorrect)
*/
char otherPlayer(char player);
