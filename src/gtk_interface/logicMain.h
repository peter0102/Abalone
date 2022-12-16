/**
 * \file logicMain.h
 * \brief Fonctions principales du jeu avec l'interface graphique
 * \author Groupe 1
 * \version 0.1
*/

/**
 * \fn isItWin(Board board)
 * \brief Vérifie s'il y a un gagnant ou non
 * \param board Etat du plateau de jeu
 * \return ERROR s'il y a un gagnant ; SUCCESS sinon
*/
char isItWin(Board board);

/**
 * \fn init(InitData mode)
 * \brief Initialise le jeu en fonction du mode sélectionné (local / réseau, blanc / noir...)
 * \param mode Mode d'initialisation :
 * \n 'b' = local (on joue les noirs)
 * \n 'w' = local (on joue les blancs)
 * \n 's' = réseau (on est le serveur / les noirs)
 * \n 'c' = réseau (on est le client / les blancs)
 * \return Contexte initial du jeu
*/
GameData init(InitData data);

/**
 * \fn nextTurnLocal(GameData* gd, Move move)
 * \brief Joue un coup humain (à l'aide du texte entré dans le champ) et actualise le contexte du jeu
 * \param gd Contexte du jeu
 * \param move Mouvement à essayer
*/
void nextTurnLocal(GameData* gd, Move move);

/**
 * \fn nextTurnAILocal(GameData* gd)
 * \brief Joue un coup de l'IA et actualise le contexte du jeu
 * \param gd Contexte du jeu
*/
void nextTurnAILocal(GameData* gd);

/**
 * \fn nextTurnPlayerNetwork(GameData* gd, Move move)
 * \brief Joue un coup humain en réseau (à l'aide du texte du champ) et actualise le contexte du jeu
 * \param gd Contexte du jeu
*/
void nextTurnPlayerNetwork(GameData* gd);

/**
 * \fn nextTurnOpponentNetwork(GameData* gd)
 * \brief En réseau, laisse l'adversaire effectuer son coup  et actualise le contexte du jeu
 * \param gd Contexte du jeu
*/
void nextTurnOpponentNetwork(GameData* gd);