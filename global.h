/**
 * \file global.h
 * \brief Bibliothèque contenant les define
 * \author Groupe 1
 * \version 0.1
*/

#define MAX_I 10
#define MAX_J 10
#define INFTY 147483648

#define EMPTY '0'
#define BLACK 'B'
#define WHITE 'W'

//types de mouvement
#define LINE_HOR_RIGHT 'a'
#define LINE_HOR_LEFT 'b'
#define LINE_VER_DOWN 'c'
#define LINE_VER_UP 'd'
#define LAT_2_HOR 'e'
#define LAT_2_VER 'f'
#define LAT_3_VER_X0_DOWN 'g'
#define LAT_3_VER_X0_UP 'h'
#define LAT_3_HOR_Y0_RIGHT 'i'
#define LAT_3_HOR_Y0_LEFT 'j'

//gestion d'erreurs
#define ERROR 'x'
#define SUCCESS 'l'

//définition des types
typedef char Board[10][10]; //caractères ASCII
typedef char Move[2][2]; //Mouvement {{x0,x1},{y0,y1}} valeurs numériques
typedef char Triple[2][3]; //coordonnées d'un joueur {{xj0,xj1,xj2},{yj0,yj1,yj2}} valeurs numériques

char otherPlayer(char player);