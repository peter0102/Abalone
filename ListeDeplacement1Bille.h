/**
 * \file ListeDeplacement1Bille.h
 * \brief Liste les déplacements possibles pour 1 bille (provisoire)
 * \author Groupe 1
 * \version 0.1
*/

typedef int Pion[2];
typedef Pion DeuxPions[2];
typedef Pion TroisPions[3];

/**
 * \fn FindAllPions(int joueur, Pion ListePions[14])
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
void FindAllPions(int joueur, Pion ListePions[14]);

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
void display();

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
void AfficherEssaiPion(int taille, Pion PionAAfficher);

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
void AfficherListePions();

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
void AfficherCoup(Move CoupAAfficher);

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
void AfficherListeCoups();

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
void AfficherListeDeuxPions();

// Les fonctions de Move :

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
int TestCoupPossible2(Move CoupATester);

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
int TestCoupPossible(Move CoupATester);

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
void FindAllMoves(Pion ListePions[14]);


/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
int UneBilleQuatreCoups(Pion PionATester, int compteurCoups);

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
int UneBilleUnCoup(Move CoupATester, int compteurCoups);


// Deux billes :

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
int DeuxBillesQuatreCoupsHorizontal(DeuxPions GroupeATester, int compteurCoups);

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
int DeuxBillesQuatreCoupsVertical(DeuxPions GroupeATester, int compteurCoups);

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
int DeuxBillesUnCoupHorizontal(Move CoupATester, int compteurCoups);

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
int DeuxBillesUnCoupVertical(Move CoupATester, int compteurCoups);

// Trois billes

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
int TroisBillesQuatreCoupsVertical(TroisPions GroupeATester, int compteurCoups);

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
int TroisBillesQuatreCoupsHorizontal(TroisPions GroupeATester, int compteurCoups);

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
int TroisBillesUnCoupHorizontal(Move CoupATester, int compteurCoups);

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
int TroisBillesUnCoupVertical(Move CoupATester, int compteurCoups);
