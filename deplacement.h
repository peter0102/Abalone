/**
 * \file move.h
 * \brief Fonctions relatives à la structure de déplacement
 * \author Groupe 1
 * \version 0.1
*/

/**
 * \struct Move move.h move.c
 * \brief Binôme point de départ / point d'arrivée d'un déplacement (16 octets)
*/
typedef struct {
    /*! Ligne du point de départ (lettre) */
    int x1;
    /*! Colonne du point de départ (chiffre) */
    int y1;
    /*! Ligne du point d'arrivée (lettre) */
    int x2;
    /*! Colonne du point d'arrivée (chiffre) */
    int y2;
} Move;

/**
 * \fn move_chr_convert(char chr, char type)
 * \brief Convertit un caractère de coordonnée (entre A et H ou entre 1 et 8)
 * \param chr Caractère à convertir
 * \param type Type de caractère (l = lettre ; n = nombre)
 * \return Index numérique correspondant au caractère d'entrée (-1 en cas de caractère incorrect)
*/
int move_chr_convert(char chr, char type);

/**
 * \fn move_change_all(Coords* coords, int new_coords[4])
 * \brief Réaffecte de valeur pour toutes les coordonnées d'un déplacement
 * \param move Déplacement dont on souhaite modifier les valeurs
 * \param new_coords Nouvelles coordonnées à affecter
*/
void move_change_all(Move* move, int new_coords[4]);

/**
 * \fn translate_move(char* input)
 * \brief Traduit les coordonnées entrées (comme F6:E5) en index comme {x1=6, y1=6, x2=5, y2=5}
 * \param input Chaîne de caractères des coordonnées (ex: A1:B2)
 * \return Coordonnées numériques des points de départ et d'arrivée ({-1, -1, -1, -1} en cas d'erreur)
*/
Move translate_move(char* input);

/**
 * \fn print_coords(Coords coords)
 * \brief Affiche un déplacement
 * \param move Déplacement à afficher
*/
void print_move(Move move);