/**
 * \file allMove.h
 * \brief Fonctions relatives à la vérification et au déplacement effectif
 * \author Groupe 1
 * \version 0.1
*/

/**
 * \fn absChar(char v)
 * \brief Valeur absolue d'un char
 * \param v valeur dont on veut la valeur absolue
 * \return |v|
*/
char absChar(char v);

/**
 * \fn whatMove(Plateau plat,Move m)
 * \brief Donne le type de mouvement associé au mouvement m
 * \param plat Plateau de jeu actuel
 * \param m Mouvement {{x0,x1},{y0,y1}}
 * \return Type de mouvement ou erreur si le mouvement est interdit
*/
char whatMove(Plateau plat,Move m);

/**
 * \fn allies(char type_of_move,Move m)
 * \brief Compte le nombre de pions alliés sélectionnés
 * \param type_of_move Type de mouvement
 * \param m Mouvement {{x0,x1},{y0,y1}}
 * \return Nombre de pions alliés sélectionnés
*/
char allies(char type_of_move,Move m);

/**
 * \fn active(Move m,char type_of_move,char nb_allies,Triple coords_allies,Triple coords_ennemies)
 * \brief Modifie en place les coordonnées alliées et ennemies
 * \param m Mouvement {{x0,x1},{y0,y1}}
 * \param type_of_move Type de mouvement
 * \param nb_allies nombre de pions alliés
 * \param coords_allies coordonnées des alliés (vierge) {{xa0,xa1,xa2},{ya0,ya1,ya2}}
 * \param coords_ennemies coordonnées des ennemis (vierge) {{xe0,xe1,xe2},{ye0,ye1,ye2}}
*/
void active(Move m,char type_of_move,char nb_allies,Triple coords_allies,Triple coords_ennemies);

/**
 * \fn ennemies(Plateau plat,Triple coords_ennemies,char nb_allies)
 * \brief Compte le nombre d'ennemis et vérifie les rapports de force et les cases de destination
 * \param plat plateau de jeu
 * \param coords_ennemies coordonnées des ennemis {{xe0,xe1,xe2},{ye0,ye1,ye2}}
 * \param nb_allies nombre de pions alliés
 * \return Nombre d'ennemis ou erreur
*/
char ennemies(Plateau plat,Triple coords_ennemies,char nb_allies);

/**
 * \fn checkColor(Triple coords,char color, char nb_allies, Plateau plat)
 * \brief Vérifie que les coordonnées soient toutes de la même couleur
 * \param coords Coordonnées dont on veut vérifier la couleur {{xc0,xc1,xc2},{yc0,yc1,yc2}}
 * \param color couleur
 * \param nb_allies nombre de pions alliés
 * \param plat plateau de jeu
 * \return Nombre d'ennemis ou erreur
*/
char checkColor(Triple coords,char color, char nb_allies, Plateau plat);

/**
 * \fn checkMove(Plateau plat, Move m)
 * \brief Vérifie que le coup est autorisé
 * \param plat plateau de jeu
 * \param m Mouvement {{x0,x1},{y0,y1}}
 * \return Erreur ou succès
*/
char checkMove(Plateau plat, Move m);

/**
 * \fn pierre(Plateau plat, Move m)
 * \brief Vérifie que le coup est légal sinon renvoie la couleur du pion de même couleur qui gène sinon erreur
 * \param plat plateau de jeu
 * \param m Mouvement {{x0,x1},{y0,y1}}
 * \return Succès, Couleur du pion qui essaie de bouger ou Erreur
*/
char pierre(Plateau plat, Move m);

/**
 * \fn moveLine(Plateau plat,Move m,Triple coords_ennemies,char nb_ennemies)
 * \brief Déplace en place sur le plateau de jeu pour un mouvement en ligne
 * \param plat plateau de jeu
 * \param m Mouvement {{x0,x1},{y0,y1}}
 * \param coords_ennemies coordonnées des ennemis {{xe0,xe1,xe2},{ye0,ye1,ye2}}
 * \param nb_ennemies nombre d'ennemis à déplacer
*/
void moveLine(Plateau plat,Move m,Triple coords_ennemies,char nb_ennemies);

/**
 * \fn moveLateral(Plateau plat,Triple coords_allies,Triple coords_ennemies, char nb_allies)
 * \brief Déplace en place sur le plateau de jeu pour un mouvement latéral
 * \param plat plateau de jeu
 * \param coords_allies coordonnées des alliés {{xa0,xa1,xa2},{ya0,ya1,ya2}}
 * \param coords_ennemies coordonnées des ennemis {{xe0,xe1,xe2},{ye0,ye1,ye2}}
 * \param nb_allies nombre d'alliés à déplacer
*/
void moveLateral(Plateau plat,Triple coords_allies,Triple coords_ennemies, char nb_allies);

/**
 * \fn move(Plateau plat,Move m,Triple coords_ennemies,char nb_ennemies,char type_of_move,Triple coords_allies, char nb_allies)
 * \brief Déplace en place sur le plateau de jeu pour le mouvement m
 * \param plat plateau de jeu
 * \param m Mouvement {{x0,x1},{y0,y1}}
 * \param coords_ennemies coordonnées des ennemis {{xe0,xe1,xe2},{ye0,ye1,ye2}}
 * \param nb_ennemies nombre d'ennemis à déplacer
 * \param type_of_move type de mouvement
 * \param coords_allies coordonnées des alliés {{xa0,xa1,xa2},{ya0,ya1,ya2}}
 * \param nb_allies nombre d'alliés à déplacer
*/
void move(Plateau plat,Move m,Triple coords_ennemies,char nb_ennemies,char type_of_move,Triple coords_allies, char nb_allies)

/**
 * \fn allMove(Plateau plat,Move m)
 * \brief Déplace en place sur le plateau de jeu pour le mouvement m en vérifiant que le coup est autorisé
 * \param plat plateau de jeu
 * \param m Mouvement {{x0,x1},{y0,y1}}
 * \return Erreur ou succès
*/
char allMove(Plateau plat,Move m);
