/**
 * \file evaluate.h
 * \brief Fonctions relatives à l'évaluation d'une configuration d'un plateau
 * \author Groupe 1
 * \version 0.1
*/


#define MAX_I 10
#define MAX_J 10

typedef char Board[MAX_I][MAX_J];


/**
 * \fn victory(Board b)
 * \brief Evalue si un pion adverse est dans la bordure
 * \param b Etat du plateau de jeu
 * return Retourne 1 si c'est une victoire, rien sinon
*/
int victory(Board b);

/**
 * \fn loss(Board b)
 * \brief Evalue si un pion allié est dans la bordure
 * \param b Etat du plateau de jeu
 * return Retourne 1 si c'est une défaite, rien sinon
*/
int loss(Board b);

/**
 * \fn density(Board b,char currentPlayer,int alpha)
 * \brief Evalue la condensation des pions dans les différents blocs du plateau
 * \param b Etat du plateau de jeu
 * \param currentPlayer Le joueur actuel
 * \param alpha Coefficient de grandeur
 * return Retourne le score de la densité du joueur actuel 
*/
int density(Board b,char currentPlayer,int alpha);
/**
 * \fn distanceToCenter(Board b)
 * \brief Evalue le score plateau en fonction de sa distance au centre
 * \param b Etat du plateau de jeu
 * return Retourne le score plateau
*/
int distanceToCenter(Board b);

/**
 * \fn areOpponentsNear(Board b)
 * \brief Evalue le score du plateau en fonction des adversaires proches
 * \param b Etat du plateau de jeu
 * \return Retourne le score du plateau
*/
int areOpponentsNear(Board b);
/**
 * \fn countNeighborsXwhite(Board b,int i, int j)
 * \brief Compte le nombre de voisins blancs selon l'axe X vertical pour les blancs
 * \param b Etatu du plateau de jeu
 * \param i coordonnée x
 * \param j coordonnée y
 * \return retourne le nombre de voisins selon l'axe X vertical pour les blancs
*/
int countNeighborsXWhite(Board b,int i, int j);
/**
 * \fn countNeighborsXBlack(Board b,int i, int j)
 * \brief Compte le nombre de voisins blancs selon l'axe X vertical pour les noirs
 * \param b Etat du plateau de jeu
 * \param i coordonnée x
 * \param j coordonnée y
 * \return retourne le nombre de voisins selon l'axe X vertical pour les noirs
*/
int countNeighborsXBlack(Board b,int i, int j);
/**
 * \fn countNeighborsYWhite(Board b,int i, int j)
 * \brief Compte le nombre de voisins blancs selon l'axe Y horizontal pour les blancs
 * \param b Etatu du plateau de jeu
 * \param i coordonnée x
 * \param j coordonnée y
 * \return retourne le nombre de voisins selon l'axe Y horizontal pour les blancs
*/
int countNeighborsYWhite(Board b,int i, int j);
/**
 * \fn countNeighborsYBlack(Board b,int i, int j)
 * \brief Compte le nombre de voisins blancs selon l'axe Y horizontal pour les noirs
 * \param b Etatu du plateau de jeu
 * \param i coordonnée x
 * \param j coordonnée y
 * \return retourne le nombre de voisins selon l'axe Y horizontal pour les noirs
*/
int countNeighborsYBlack(Board b,int i, int j);
/**
 * \fn canOpponentAttack(Board b)
 * \brief Calcule le nombre d'attaques alliées et ennemies possible et attribue un score
 * \param b Etat du plateau de jeu
 * \return retourne le score du plateau selon le nombre d'attaques possibles
*/
int canOpponentAttack(Board b);

/**
 * \fn evaluate(Board b,char currentPlayer)
 * \brief Utilise toutes les fonctions d'évaluation pour calculer un poids final pour le plateau donné
 * \param b Etat du plateau de jeu
 * \param currentPlayer Joueur courant
 * \return retourne le poids final du plateau actuel
*/
int evaluate(Board b,char currentPlayer);


