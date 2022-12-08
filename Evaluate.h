/**
 * \file Evaluate.h
 * \brief Fonctions relatives à l'évaluation de chaque mouvement
 * \author Groupe 1
 * \version 0.1
*/


#define MAX_I 10
#define MAX_J 10

typedef char Plateau[MAX_I][MAX_J];
int victory(Plateau p);
int loss(Plateau p);
int density(Plateau p,char currentPlayer,int alpha);
/**
 * \fn distanceToCenter(Plateau p)
 * \brief Evalue le score plateau en fonction de sa distance au centre
 * \param p Etat du plateau de jeu
 * return Retourne le score plateau
*/
int distanceToCenter(Plateau p);

/**
 * \fn areOpponentsNear(Plateau p)
 * \brief Evalue le score du plateau en fonction des adversaires proches
 * \param p Etat du plateau de jeu
 * \return Retourne le score du plateau
*/
int areOpponentsNear(Plateau p);
/**
 * \fn countNeighborsXwhite(Plateau p,int i, int j)
 * \brief Compte le nombre de voisins blancs selon l'axe X vertical pour les blancs
 * \param p Etatu du plateau de jeu
 * \param i coordonnée x
 * \param j coordonnée y
 * \return retourne le nombre de voisins selon l'axe X vertical pour les blancs
*/
int countNeighborsXWhite(Plateau p,int i, int j);
/**
 * \fn countNeighborsXBlack(Plateau p,int i, int j)
 * \brief Compte le nombre de voisins blancs selon l'axe X vertical pour les noirs
 * \param p Etatu du plateau de jeu
 * \param i coordonnée x
 * \param j coordonnée y
 * \return retourne le nombre de voisins selon l'axe X vertical pour les noirs
*/
int countNeighborsXBlack(Plateau p,int i, int j);
/**
 * \fn countNeighborsYWhite(Plateau p,int i, int j)
 * \brief Compte le nombre de voisins blancs selon l'axe Y horizontal pour les blancs
 * \param p Etatu du plateau de jeu
 * \param i coordonnée x
 * \param j coordonnée y
 * \return retourne le nombre de voisins selon l'axe Y horizontal pour les blancs
*/
int countNeighborsYWhite(Plateau p,int i, int j);
/**
 * \fn countNeighborsYBlack(Plateau p,int i, int j)
 * \brief Compte le nombre de voisins blancs selon l'axe Y horizontal pour les noirs
 * \param p Etatu du plateau de jeu
 * \param i coordonnée x
 * \param j coordonnée y
 * \return retourne le nombre de voisins selon l'axe Y horizontal pour les noirs
*/
int countNeighborsYBlack(Plateau p,int i, int j);
/**
 * \fn canOpponentAttack(Plateau p)
 * \brief Calcule le nombre d'attaques alliées et ennemies possible et attribue un score
 * \param p Etat du plateau de jeu
 * \return retourne le score du plateau selon le nombre d'attaques possibles
*/
int canOpponentAttack(Plateau p);
