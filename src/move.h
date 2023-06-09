/**
 * \file move.h
 * \brief Fonctions relatives à la structure de déplacement
 * \author Groupe 1
 * \version 0.1
*/

/**
 * \fn moveChrConvert(char chr, char type)
 * \brief Convertit un caractère de coordonnée (entre A et H ou entre 1 et 8) en index
 * \param chr Caractère à convertir
 * \param type Type de caractère (l = lettre ; n = nombre)
 * \return Index sous forme de caractère utilisé comme un int correspondant au caractère d'entrée (-1 en cas de caractère incorrect)
*/
char moveChrConvert(char chr, char type);

/**
 * \fn moveChrConvertReverse (char index, char type)
 * \brief Convertit un index de déplacement en caractère de coordonnée (entre A et H ou entre 1 et 8)
 * \param index Index à convertir (caractère utilisé comme un int)
 * \param type Type de caractère (l = lettre ; n = nombre)
 * \return Caractère (lettre ou chiffre) correspondant à l'index d'entrée ('x' en cas d'index incorrect)
*/
char moveChrConvertReverse (char index, char type);

/**
 * \fn translateMove(Move move,char* input)
 * \brief Traduit les coordonnées entrées (comme F6:E5) en index comme {{6, 6}, {5, 5}}
 * \param move Déplacement dont on souhaite actualiser les valeurs
 * \param input Chaîne de caractères des coordonnées (ex: A1:B2)
*/
void translateMove(Move move,char* input);

/**
 * \fn translateMoveReverse(Move move)
 * \brief Traduit le déplacement entré (comme {{6, 6}, {5, 5}}) en chaîne de caractères comme 'F6:E5'
 * \param move Déplacement à traduire
 * \return Chaîne de caractères correspondant au mouvement entré
*/
char* translateMoveReverse(Move move);
/**
 * \fn printMove(Move move)
 * \brief Affiche un déplacement
 * \param move Mouvement à afficher
*/
void printMove(Move move);