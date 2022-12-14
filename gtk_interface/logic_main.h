/**
 * \file logic_main.h
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
 * \fn init(char mode)
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
 * \fn nextTurn(GameData* gd, Move move)
 * \brief Joue un coup en fonction du joueur (humain ou IA) et actualise le contexte du jeu
 * \param gd Contexte du jeu
 * \param move Mouvement à essayer (uniquement pour un joueur humain ; l'IA n'utilise pas ce coup mais choisit son coup optimal à la place)
*/
void nextTurnLocal(GameData* gd, Move move);

void nextTurnAILocal(GameData* gd);
void nextTurnNetwork(GameData* gd, Move move);