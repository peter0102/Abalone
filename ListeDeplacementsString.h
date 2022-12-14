

/**
 * \file ListeDeplacementsValides.h
 * \brief Fonctions relatives � la recherches des deplacements possibles
 * \author Groupe 1
 * \version 0.1
*/


/**
 * \brief taille de la liste des coups possibles
*/
#define tailleListeCoups 200

/**
 * \fn DisplayPion(Triple PionAAfficher, int PositionPion)
 * \brief Affiche la position d'un unique pion
 * \param PositionAAfficher Triple qui contient le pion � afficher
 * \param PositionPion int indiquant si le pion � afficher est le premier, deuxi�me ou troisi�me pion du triple
*/
void DisplayPion(Triple PionAAfficher, int PositionPion);

/**
 * \fn DisplayListOfPions()
 * \brief Affiche la liste des pions
*/
void DisplayListOfPions();

/**
 * \fn DisplayMove(Move CoupAAfficher)
 * \brief Affiche le coup demand�
 * \param CoupAAfficher Move contenant le coup � afficher
*/
void DisplayMove(Move CoupAAfficher);


/**
 * \fn DisplayListOfMove()
 * \brief Affiche la liste des coups possibles, au format [[x0,x1],[y0,y1]]
*/
void DisplayListOfMove();

/**
 * \fn DisplayListOfMoveNormalVersion()
 * \brief Affiche la liste des coups possibles, au format [[x0,y0],[x1,y1]]
*/

void DisplayListOfMoveNormalVersion();

/**
 * \fn DisplayListOfTwoPions()
 * \brief Affiche la liste des groupes de deux pions
*/
void DisplayListOfTwoPions();

/**
 * \fn DisplayListOfThreePions()
 * \brief Affiche la liste des groupes de trois pions
*/
void DisplayListOfThreePions();

/**
 * \fn FindAllPions(char Player)
 * \brief Cherche tous les pions du joueur dont c'est le tour
 * \param current_player caract�re repr�sentant le joueur dont c'est le tour
*/





void FindAllPions(char current_player);

/**
 * \fn FindAllMoves(char current_player)
 * \brief trouve tous les deplacements possibles du joueur dont c'est le tour
 * \param current_player Caract�re indiquant le joueur dont c'est le tour
 * \return un unique string contenant la liste des coups possibles, s�par�s par des ;
*/

char* FindAllMoves(char current_player);



/**
 * \fn UneBilleQuatreCoups
 * \brief Etudie les coups possibles d'une bille unique, dans les quatre directions
 * \param PionATester Triple indiquant la position du pion � tester
 * \param compteurCoups Entier indiquant le nombre de coups valides trouv�s jusqu'� maintenant
 * \param current_player Caract�re indiquant le joueur dont c'est le tour
 * \return Entier indiquant le nombre de coups valides trouv�s jusqu'� maintenant
*/
int UneBilleQuatreCoups(Triple PionATester, int compteurCoups, char current_player);

/**
 * \fn Une BilleUnCoupHautGauche(Move CoupATester, int compteurCoupschar ,char current_player)
 * \brief Etude, pour une bille, de deux mouvements : vers le haut et la gauche. Si le coup est valide, il est ajout� � la liste des coups valides.
 * \param current_player Caract�re indiquant le joueur dont c'est le tour
 * \param compteurCoups Entier indiquant le nombre de coups valides trouv�s jusqu'� maintenant
 * \param CoupATester Move indiquant le coup � tester
 * \return Entier indiquant le nombre de coups valides trouv�s jusqu'� maintenant
*/
int UneBilleUnCoupHautGauche(Move CoupATester, int compteurCoups, char current_player);

/**
 * \fn UneBilleUnCoupDroiteBas(Move CoupATester, int compteurCoupschar ,char current_player)
 * \brief Etude, pour une bille, de deux mouvements : vers le bas et la droite. Si le coup est valide, il est ajout� � la liste des coups valides. Si la bille bloquante est de la m�me couleur, on ajoute le groupe � la liste des deux billes.
 * \param current_player Caract�re indiquant le joueur dont c'est le tour
 * \param compteurCoups Entier indiquant le nombre de coups valides trouv�s jusqu'� maintenant
 * \param CoupATester Move indiquant le coup � tester
 * \return Entier indiquant le nombre de coups valides trouv�s jusqu'� maintenant
*/

int UneBilleUnCoupDroiteBas(Move CoupATester, int compteurCoups, char current_player);

/**
 * \fn DeuxBillesQuatreCoupVertical(Move CoupATester, int compteurCoupschar ,char current_player)
 * \brief Prend en param�tre un unique groupe de deux billes orient� verticalement, et �tudie les coups possibles dans les quatre directions
 * \param GroupeATester Triple indiquant la position des deux pions � tester
 * \param compteurCoups Entier indiquant le nombre de coups valides trouv�s jusqu'� maintenant
 * \param current_player Caract�re indiquant le joueur dont c'est le tour
 * \return Entier indiquant le nombre de coups valides trouv�s jusqu'� maintenant
*/
int DeuxBillesQuatreCoupsVertical(Triple GroupeATester, int compteurCoups, char current_player);


/**
 * \fn DeuxBillesQuatreCoupHorizontal(Move CoupATester, int compteurCoupschar ,char current_player)
 * \brief Prend en param�tre un unique groupe de deux billes orient� horizontalement, et �tudie les coups possibles dans les quatre directions
 * \param GroupeATester Triple indiquant la position des deux pions � tester
 * \param compteurCoups Entier indiquant le nombre de coups valides trouv�s jusqu'� maintenant
 * \param current_player Caract�re indiquant le joueur dont c'est le tour
 * \return Entier indiquant le nombre de coups valides trouv�s jusqu'� maintenant
*/
int DeuxBillesQuatreCoupsHorizontal(Triple GroupeATester, int compteurCoups, char current_player);


/**
 * \fn DeuxBillesUnCoup(Move CoupATester, int compteurCoupschar ,char current_player)
 * \brief Verifie, pour un groupe de deux billes, si un coup est possible
 * \param GroupeATester Triple indiquant la position des deux pions � tester
 * \param compteurCoups Entier indiquant le nombre de coups valides trouv�s jusqu'� maintenant
 * \param current_player Caract�re indiquant le joueur dont c'est le tour
 * \return Entier indiquant le nombre de coups valides trouv�s jusqu'� maintenant
*/
int DeuxBillesUnCoup(Move CoupATester, int compteurCoups, char current_player);

/**
 * \fn DeuxBillesUnCoupEtPeutEtre3Billes(Move CoupATester, int compteurCoups, char current_player)
 * \brief Verifie, pour un groupe de deux billes, si un coup est possible. Dans certains cas particuliers (en ligne vertical vers le bas, en ligne horizontal vers la droite), verifie egalement si il y a une bille de meme couleur, pour cr�er un groupe de 3 billes.
 * \param GroupeATester Triple indiquant la position des deux pions � tester
 * \param compteurCoups Entier indiquant le nombre de coups valides trouv�s jusqu'� maintenant
 * \param current_player Caract�re indiquant le joueur dont c'est le tour
 * \return Entier indiquant le nombre de coups valides trouv�s jusqu'� maintenant
*/
int DeuxBillesUnCoupEtPeutEtre3Billes(Move CoupATester, int compteurCoups, char current_player);



/**
 * \fn TroisBillesQuatreCoupsVertical(Triple GroupeATester, int compteurCoups ,char current_player)
 * \brief recherche les deplacements possibles en haut en gauche d'un pion lorsque le joueur  joue
 * \param current_player valeur qui represente le joueur qui joue
 * \param compteurCoups represente le nombre de coups valid�s
 * \param GroupeATester represente le triplet a tester
 * \return nombre de coups valides
*/

int TroisBillesQuatreCoupsVertical(Triple GroupeATester, int compteurCoups, char current_player);


/**
 * \fn TroisBillesQuatresCoupsHorizontal(Triple GroupeATester, int compteurCoupschar ,char current_player)
 * \brief Prend en param�tre un unique groupe de deux billes orient� horizontalement, et �tudie les coups possibles dans les quatre directions
 * \param GroupeATester Triple indiquant la position des deux pions � tester
 * \param compteurCoups Entier indiquant le nombre de coups valides trouv�s jusqu'� maintenant
 * \param current_player Caract�re indiquant le joueur dont c'est le tour
 * \return Entier indiquant le nombre de coups valides trouv�s jusqu'� maintenant
*/

int TroisBillesQuatreCoupsHorizontal(Triple GroupeATester, int compteurCoups, char current_player);


/**
 * \fn TroisBillesUnCoup(Move CoupATester, int compteurCoups ,char current_player)
 * \brief Verifie, pour un groupe de trois billes, si un coup est possible
 * \param GroupeATester Triple indiquant la position des trois pions � tester
 * \param compteurCoups Entier indiquant le nombre de coups valides trouv�s jusqu'� maintenant
 * \param current_player Caract�re indiquant le joueur dont c'est le tour
 * \return Entier indiquant le nombre de coups valides trouv�s jusqu'� maintenant
*/

int TroisBillesUnCoup(Move CoupATester, int compteurCoups, char current_player);


/**
 * \fn Traduire(int longueurListe)
 * \brief Traduit la liste de coups au format move en un unique string
 * \param longueurListe longueur de la liste des coups possibles, donc le nombre de coups possibles
 * \return un string contenant la liste des coups possibles, s�par�s par des ;
*/
char* Traduire(int longueurListe);
