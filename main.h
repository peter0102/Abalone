/**
 * \file main.h
 * \brief Fonctions principales du jeu
 * \author Groupe 1
 * \version 0.1
*/

int turn(int current_turn);

typedef int Tableau[MAX_I][MAX_J];
void display ();

/**
 * Dictionnaire numérique pour les mouvements
*/
int coords_nbs_dictionary (char chr);
/**
 * Dictionnaire alphabéthique pour les mouvements
*/
int coords_ltr_dictionary (char chr);
/**
 * \struct Coords main.h main.c
 * \brief Binôme point de départ/point d'arrivée d'un mouvement (16 octets)
*/
typedef struct {
    /*! Ligne du point de départ (lettre) */
    int x1;
    /*! Colonne du point de départ (chiffre) */
    int y1;
    /*! Ligne du point d'arrivée (lettre) */
    int x2;
    /*! Colonne du point d'arrivée (chiffre) */
    int y2;} Coords;
/**
 * \fn translate_coords(char* input)
 * \brief traduction
 * \param input chaîne de caractères des coordonnées (ex: A1:B2)
 * \return coordonnées numériques des points de départ et d'arrivée
*/
Coords translate_coords(char* input);
/**
 * \fn print_coords(Coords coords)
 * \brief affichage des coordonnées
 * \param coords coordonées numériques à afficher
 * \return Nothing
*/
void print_coords(Coords coords);

int isItWin();
