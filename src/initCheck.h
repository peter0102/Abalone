/**
 * \file initCheck.h
 * \brief Fonction traitant la commande entrée dans le terminal
 * \author Groupe 1
 * \version 0.1
*/

typedef struct {char mode; int fdclient;} InitData;

/**
 * \fn initialCheck(int argc, char* argv[])
 * \brief Traite la commande entrée dans le terminal
 * \param argc Nombre d'arguments de la commande
 * \param argv Contenu des arguments de la commande
 * \return Mode d'initialisation :
 * \n 'b' = local (on joue les noirs)
 * \n 'w' = local (on joue les blancs)
 * \n 's' = réseau (on est le serveur / les noirs)
 * \n 'c' = réseau (on est le client / les blancs)
 * \n ERROR = erreur
*/
InitData initialCheck(int argc, char* argv[]);

/**
 * \fn printError()
 * \brief Affiche une erreur de syntaxe et l'aide d'utilisation du programme
*/
void printError();