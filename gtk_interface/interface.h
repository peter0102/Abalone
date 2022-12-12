/**
 * \file move.h
 * \brief Fonctions relatives à la structure de déplacement
 * \author Groupe 1
 * \version 0.1
*/

/**
 * \brief Nombre de pions par joueur
*/
#define PAWN_NB 14

#define MAX_I 10
#define MAX_J 10

#define CASE_VIDE '0'
#define CASE_NOIRE 'N'
#define CASE_BLANCHE 'B'

typedef char Plateau[MAX_I][MAX_J];

/**
 * \fn onDestroy(GtkWidget *widget, gpointer data)
 * \brief Fonction exécutée lors de l'appui sur le bouton "Quitter"
 * \param widget Widget auquel le signal contenant cette fonction est associé
 * \param data Donnée supplémentaire transmise lors de l'appui sur le bouton (inutilisé)
*/
void onDestroy(GtkWidget* widget, gpointer data);

/**
 * \fn onDraw(GtkWidget *widget, gpointer data)
 * \brief Fonction exécutée lors de l'appui sur le bouton "Dessiner"
 * \param widget Widget auquel le signal contenant cette fonction est associé
 * \param data Donnée supplémentaire transmise lors de l'appui sur le bouton (inutilisé)
*/
void onDraw(GtkWidget* widget, gpointer data);

/**
 * \fn onActivateEntry(GtkEntry* entry, gpointer data)
 * \brief Fonction exécutée en appuyant sur la touche "Entrée" après avoir rempli le champ
 * \param entry Champ à remplir concerné par ce signal
 * \param data Donnée supplémentaire transmise à la fonction (ici, le contenu du champ)
*/
void onActivateEntry(GtkEntry* entry, gpointer data);

/**
 * \fn setPlayerColor(char color)
 * \brief Actualise le texte de l'interface concernant la couleur du joueur client : "Vous êtes les _"
 * \param color Couleur du joueur client ('b' = black ; 'w' = white)
*/
void setPlayerColor(char color);

/**
 * \fn setTurnColor(char color)
 * \brief Actualise le texte de l'interface concernant la couleur du joueur dont c'est le tour : "Tour des _"
 * \param color Couleur du joueur dont c'est le tour ('b' = black ; 'w' = white)
*/
void setTurnColor(char color);

/**
 * \fn setTurnNumber(int turn)
 * \brief Actualise le texte de l'interface concernant le numéro du tour : "Tour _"
 * \param turn Numéro du tour
*/
void setTurnNumber(int turn);

/**
 * \fn setLastMove(int** move)
 * \brief Actualise le texte de l'interface concernant le dernier déplacement joué : "Dernier coup : __:__"
 * \param move Dernier déplacement effectué
*/
void setLastMove(int** move);

/**
 * \fn drawPawn (char color, int index, int* position)
 * \brief Place un pion sur le plateau de l'interface graphique
 * \param color Couleur du pion à placer ('b' = black ; 'w' = white)
 * \param index Index de la liste des pions noirs (ou blancs) concerné par ce déplacement (0 <= index <= PAWN_NB)
 * \param position Position où placer le pion (int[2] sous la forme {ligne, colonne})
*/
void drawPawn (char color, int index, int* position);

/**
 * \fn drawBoard(Plateau board)
 * \brief Place les pions sur le plateau de l'interface graphique d'après la disposition indiquée
 * \param board Plateau à afficher
*/
void drawBoard(Plateau board);

/**
 * \fn clearBoard()
 * \brief Efface le plateau (en pratique : rend tous les pions invisibles et les déplace en position (0, 0), soit en haut à gauche)
*/
void clearBoard();
