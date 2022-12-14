/**
 * \file evaluate.h
 * \brief Fonctions relatives à l'évaluation d'une configuration d'un plateau
 * \author Groupe 1
 * \version 0.1
*/

/**
 * \fn victory(Board board)
 * \brief Evalue si un pion adverse est dans la bordure
 * \param board Etat du plateau de jeu
 * \param other_player Caractère qui indique la couleur du joueur dont ce n'est pas le tour
 * \return Retourne 1 si c'est une victoire, rien sinon
*/
int victory(Board board, char other_player);

/**
 * \fn loss(Board board)
 * \brief Evalue si un pion allié est dans la bordure
 * \param board Etat du plateau de jeu
 * \param current_player Caractère qui indique la couleur du joueur dont c'est le tour
 * \return Retourne 1 si c'est une défaite, rien sinon
*/
int loss(Board board,char current_player);

/**
 * \fn density(Board board,char currentPlayer,int alpha)
 * \brief Evalue la condensation des pions dans les différents blocs du plateau
 * \param board Etat du plateau de jeu
 * \param currentPlayer Le joueur actuel
 * \param alpha Coefficient de grandeur
 * \return Retourne le score de la densité du joueur actuel
*/
int density(Board board,char currentPlayer,int alpha);
/**
 * \fn distanceToCenter(Board board)
 * \brief Evalue le score plateau en fonction de sa distance au centre
 * \param board Etat du plateau de jeu
 * \param current_player couleur du joueur
 * \param other_player couleur de l'adversaire
 * \return Retourne le score plateau
*/
int distanceToCenter(Board board, char current_player, char other_player);

/**
 * \fn areOpponentsNear(Board board)
 * \brief Evalue le score du plateau en fonction des adversaires proches
 * \param board Etat du plateau de jeu
* \param current_player couleur du joueur
 * \param other_player couleur de l'adversaire
 * \return Retourne le score du plateau
*/
int areOpponentsNear(Board board, char current_player, char other_player);
/**
 * \fn countNeighborsX(Board board,int i, int j,char current_player, char other_player)
 * \brief Compte le nombre de voisins blancs selon l'axe X vertical pour les blancs
 * \param board Etat du plateau de jeu
 * \param i coordonnée x
 * \param j coordonnée y
 * \param current_player couleur du joueur
 * \param other_player joueur adverse
 * \return retourne le nombre de voisins selon l'axe X vertical pour les blancs
*/
int countNeighborsX(Board board,int i, int j,char current_player);
/**
 * \fn countNeighborsY(Board board,int i, int j,char current_player, char other_player)
 * \brief Compte le nombre de voisins blancs selon l'axe Y horizontal pour les noirs
 * \param board Etatu du plateau de jeu
 * \param i coordonnée x
 * \param j coordonnée y
 * \param current_player couleur du joueur
 * \param other_player joueur adverse
 * \return retourne le nombre de voisins selon l'axe Y horizontal pour les noirs
*/
int countNeighborsY(Board board,int i, int j,char current_player);
/**
 * \fn canOpponentAttack(Board board)
 * \brief Calcule le nombre d'attaques alliées et ennemies possible et attribue un score
 * \param board Etat du plateau de jeu
 * \return retourne le score du plateau selon le nombre d'attaques possibles
*/
int canAttack(Board board, char current_player, char other_player);
/**
 * \fn canEnd(Board board, char current_player, char other_player)
 * \brief Analyse le tableau pour voir si un des deux camps est à 1 déplacement de la victoire ou de la défaite
 * \param board Etat du plateau de jeu
 * \param current_player couleur du joueur
 * \param other_player couleur de l'adversaire
 * \return retourne le score d'un plateau selon les configurations
*/
int canEnd(Board board,char current_player, char other_player);
/**
 * \fn evaluate(Board board,char currentPlayer)
 * \brief Utilise toutes les fonctions d'évaluation pour calculer un poids final pour le plateau donné
 * \param board Etat du plateau de jeu
 * \param current_player Joueur courant
 * \param other_player joueud adverse
 * \return retourne le poids final du plateau actuel
*/
int evaluate(Board board,char current_player,char other_player);


