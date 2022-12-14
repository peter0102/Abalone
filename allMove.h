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
 * \fn checkBorders(Move m)
 * \brief Vérifie que le mouvement ne soit pas un suicide
 * \param m Mouvement {{x0,x1},{y0,y1}}
 * \return erreur ou succès
*/
char checkSuicide(Move m);

/**
 * \fn whatMove(Board board,Move m, char current_player)
 * \brief Donne le type de mouvement associé au mouvement m
 * \param board Plateau de jeu actuel
 * \param m Mouvement {{x0,x1},{y0,y1}}
 * \param current_player couleur du joueur à ce tour
 * \return Type de mouvement ou erreur si le mouvement est interdit
*/
char whatMove(Board board,Move m, char current_player);

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
 * \fn ennemiesLine(Board board,Triple coords_ennemies,char nb_allies, char current_player)
 * \brief Compte le nombre d'ennemis et vérifie les rapports de force et les cases de destination en ligne
 * \param board plateau de jeu
 * \param coords_ennemies coordonnées des ennemis {{xe0,xe1,xe2},{ye0,ye1,ye2}}
 * \param nb_allies nombre de pions alliés
 * \param current_player couleur du joueur à ce tour
 * \return Nombre d'ennemis ou erreur
*/
char ennemiesLine(Board board,Triple coords_ennemies,char nb_allies, char current_player);

/**
 * \fn ennemies(Board board,Triple coords_ennemies,char nb_allies)
 * \brief Compte le nombre d'ennemis et vérifie les rapports de force et les cases de destination en latéral
 * \param board plateau de jeu
 * \param coords_ennemies coordonnées des ennemis {{xe0,xe1,xe2},{ye0,ye1,ye2}}
 * \param nb_allies nombre de pions alliés
 * \return Nombre d'ennemis ou erreur
*/
char ennemiesLat(Board board,Triple coords_ennemies,char nb_allies);

/**
 * \fn ennemies(Board board,Triple coords_ennemies,char nb_allies)
 * \brief Compte le nombre d'ennemis et vérifie les rapports de force et les cases de destination
 * \param board plateau de jeu
 * \param coords_ennemies coordonnées des ennemis {{xe0,xe1,xe2},{ye0,ye1,ye2}}
 * \param nb_allies nombre de pions alliés
 * \param current_player couleur du joueur à ce tour
 * \param type_of_move Type de mouvement
 * \return Nombre d'ennemis ou erreur
*/
char ennemies(Board board,Triple coords_ennemies,char nb_allies, char current_player, char type_of_move);

/**
 * \fn checkColor(Triple coords,char color, char nb_allies, Board board)
 * \brief Vérifie que les coordonnées soient toutes de la même couleur
 * \param coords Coordonnées dont on veut vérifier la couleur {{xc0,xc1,xc2},{yc0,yc1,yc2}}
 * \param color couleur
 * \param nb_allies nombre de pions alliés
 * \param board plateau de jeu
 * \return Nombre d'ennemis ou erreur
*/
char checkColor(Triple coords,char color, char nb_allies, Board board);

/**
 * \fn checkMove(Board board, Move m,char current_player)
 * \brief Vérifie que le coup est autorisé
 * \param board plateau de jeu
 * \param m Mouvement {{x0,x1},{y0,y1}}
 * \param current_player couleur du joueur à ce tour
 * \return Erreur ou succès
*/
char checkMove(Board board, Move m,char current_player);

/**
 * \fn checkForList(Board board, Move m, char current_player,char other_player)
 * \brief Vérifie que le coup est légal sinon renvoie la couleur du pion de même couleur qui gène sinon erreur
 * \param board plateau de jeu
 * \param m Mouvement {{x0,x1},{y0,y1}}
 * \param current_player couleur du joueur à ce tour
 * \return Succès, Couleur du pion qui essaie de bouger ou Erreur
*/
char checkForList(Board board, Move m, char current_player,char other_player);

/**
 * \fn moveLine(Board board,Move m,Triple coords_ennemies,char nb_ennemies,char current_player,char other_player)
 * \brief Déplace en place sur le plateau de jeu pour un mouvement en ligne
 * \param board plateau de jeu
 * \param m Mouvement {{x0,x1},{y0,y1}}
 * \param coords_ennemies coordonnées des ennemis {{xe0,xe1,xe2},{ye0,ye1,ye2}}
 * \param nb_ennemies nombre d'ennemis à déplacer
 * \param current_player couleur du joueur à ce tour
 * \param other_player couleur de l'adversaire à ce tour
*/
void moveLine(Board board,Move m,Triple coords_ennemies,char nb_ennemies,char current_player,char other_player);

/**
 * \fn moveLateral(Board board,Triple coords_allies,Triple coords_ennemies, char nb_allies)
 * \brief Déplace en place sur le plateau de jeu pour un mouvement latéral
 * \param board plateau de jeu
 * \param coords_allies coordonnées des alliés {{xa0,xa1,xa2},{ya0,ya1,ya2}}
 * \param coords_ennemies coordonnées des ennemis {{xe0,xe1,xe2},{ye0,ye1,ye2}}
 * \param nb_allies nombre d'alliés à déplacer
*/
void moveLateral(Board board,Triple coords_allies,Triple coords_ennemies, char nb_allies,char current_player);

/**
 * \fn move(Board board,Move m,Triple coords_ennemies,char nb_ennemies,char type_of_move,Triple coords_allies,\
char nb_allies,char current_player, char other_player)
 * \brief Déplace en place sur le plateau de jeu pour le mouvement m
 * \param board plateau de jeu
 * \param m Mouvement {{x0,x1},{y0,y1}}
 * \param coords_ennemies coordonnées des ennemis {{xe0,xe1,xe2},{ye0,ye1,ye2}}
 * \param nb_ennemies nombre d'ennemis à déplacer
 * \param type_of_move type de mouvement
 * \param coords_allies coordonnées des alliés {{xa0,xa1,xa2},{ya0,ya1,ya2}}
 * \param nb_allies nombre d'alliés à déplacer
 * \param current_player couleur du joueur à ce tour
 * \param other_player couleur de l'adversaire à ce tour
*/
void move(Board board,Move m,Triple coords_ennemies,char nb_ennemies,char type_of_move,Triple coords_allies,\
char nb_allies,char current_player, char other_player);

/**
 * \fn allMove(Board board,Move m,char current_player,char other_player)
 * \brief Déplace en place sur le plateau de jeu pour le mouvement m en vérifiant que le coup est autorisé
 * \param board plateau de jeu
 * \param m Mouvement {{x0,x1},{y0,y1}}
 * \param current_player couleur du joueur à ce tour
 * \param other_player couleur de l'adversaire à ce tour
 * \return Erreur ou succès
*/
char allMove(Board board,Move m,char current_player,char other_player);
