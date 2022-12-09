/**
 * \file ListeDeplacement1Bille.h
 * \brief Liste les déplacements possibles pour 1 bille (provisoire)
 * \author Groupe 1
 * \version 0.1
*/

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
void FindAllPions(int joueur);

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
void AfficherCoup(Coup CoupAAfficher);

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

// Les fonctions de coup :

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
int TestCoupPossible2(Coup CoupATester);

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
int TestCoupPossible(Coup CoupATester);

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
int UneBilleUnCoup(Coup CoupATester, int compteurCoups);


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
int DeuxBillesUnCoupHorizontal(Coup CoupATester, int compteurCoups);

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
int DeuxBillesUnCoupVertical(Coup CoupATester, int compteurCoups);

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
int TroisBillesUnCoupHorizontal(Coup CoupATester, int compteurCoups);

/**
 * \fn Fonction
 * \brief Description
 * \param Paramètres
 * \return Retour
*/
int TroisBillesUnCoupVertical(Coup CoupATester, int compteurCoups);
