/**
 * \file interface.h
 * \brief Fonctions relatives à l'interface graphique et aux signaux qu'elle envoie
 * \author Groupe 1
 * \version 0.1
*/

#include <gtk/gtk.h>

/**
* \struct GameData interface.h interface.c
* \brief Contexte de la partie transmis à chaque tour
*/
typedef struct {
    /*! Disposition actuelle des pions */
    Board board;
    /*! Couleur que je joue */
    char me;
    /*! Joueur (couleur) dont c'est le tour */
    char current_player;
    /*! Numéro du tour */
    int nb_turn;
    /*! Index de la conexion(-1 = jeu en local)*/
    int fdclient;
    } GameData;

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
 * \param data Donnée supplémentaire transmise à la fonction (ici, le contexte du signal)
*/
void onActivateEntry(GtkEntry* entry, GameData* gd);

/**
 * \fn setPlayerColor(char color)
 * \brief Actualise le texte de l'interface concernant la couleur du joueur client : "Vous êtes les _"
 * \param color Couleur du joueur client (BLACK ou WHITE)
*/
void setPlayerColor(char color);

/**
 * \fn setTurnColor(char color)
 * \brief Actualise le texte de l'interface concernant la couleur du joueur dont c'est le tour : "Tour des _"
 * \param color Couleur du joueur dont c'est le tour (BLACK ou WHITE)
*/
void setTurnColor(char color);

/**
 * \fn setTurnNumber(int turn)
 * \brief Actualise le texte de l'interface concernant le numéro du tour : "Tour _"
 * \param turn Numéro du tour
*/
void setTurnNumber(int turn);

/**
 * \fn setLastMove(Move move)
 * \brief Actualise le texte de l'interface concernant le dernier déplacement joué : "Dernier coup : __:__"
 * \param move Dernier déplacement effectué
 * \param color Couleur du joueur ayant efectué le déplacement
*/
void setLastMove(Move move, char color);

/**
 * \fn setNotification(char* notification)
 * \brief Affiche une notification sur l'interface, en-dessous du dernier déplacement
 * \param notificaiton Notification à afficher
*/
void setNotification(char* notification);

/**
 * \fn drawPawn (char color, int index, int* position)
 * \brief Place un pion sur le plateau de l'interface graphique
 * \param color Couleur du pion à placer (BLACK ou WHITE)
 * \param index Index de la liste des pions noirs (ou blancs) concerné par ce déplacement (0 <= index <= PAWN_NB)
 * \param position Position où placer le pion (int[2] sous la forme {ligne, colonne})
*/
void drawPawn (char color, int index, int* position);

/**
 * \fn drawBoard(Board board)
 * \brief Place et affiche les pions sur le plateau de l'interface graphique d'après la disposition indiquée
 * \param board Plateau à afficher
*/
void drawBoard(Board board);

/**
 * \fn clearBoard()
 * \brief Efface le plateau (en pratique : rend tous les pions invisibles et les déplace en position (0, 0), soit en haut à gauche)
*/
void clearBoard();