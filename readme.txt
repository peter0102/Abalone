========================================

		A B A L O N E
		
		Par le groupe 1

========================================

Nous vous remercions de jouer à notre version simplifiée de l'Abalone.
Ce jeu a été développé en 11 jours durant l'immersion des étudiants en première année d'ingénierie informatique à l'ENSISA.

== COMMANDES ==
	make
		> Compilation du jeu
	make docs
		> Génération de la documentation

== EXECUTION (une fois la compilation effectuée) ==
	./abalone -l noir
		> Démarrage d'une partie en local ; vous incarnez les noirs et jouez en premier
	./abalone -l blanc
		> Démarrage d'une partie en local ; vous incarnez les blancs et jouez en deuxième
	./abalone -c *port*
		> Démarrage d'une partie en réseau, hébergée sur VOTRE port *port* ; vous incarnez les noirs et jouez en premier
	./abalone -s xx.xx.xx.xx:*port*
		> Démarrage d'une partie en réseau, hébergée sur un client EXTERNE ; vous incarnez les blancs et jouez en deuxième

== DEROULEMENT DU JEU ==
	Chaque joueur commence avec 14 pions disposés sur le plateau carré de 8 cases de côté.
	A tour de rôle, et jusqu'à la fin de la partie, les deux adversaires effectuent des déplacements d'une case dans la direction de leur choix.
	Un joueur peut simultanément déplacer un groupe composé de 1 à 3 pions adjacents et alignés dans la direction de son choix, tant que le déplacement est valide (plus de détails dans le paragraphe suivant).
	Lorsqu'un groupe de 2 ou 3 pions se déplace, on distingue les déplacements "en ligne" (sur l'axe de l'alignement des pions) et les déplacements "latéraux" (perpendiculaires à l'axe d'alignement des pions).
	
	Un joueur peut attaquer son adversaire en poussant des pions adverses à l'aide d'un déplacement en ligne. Cette attaque est conditionnée par un rapport de force : il faut déplacer au moins 2 pions pour pousser 1 pion adverse et 3 pions pour pousser 2 pions adverses en même temps.
	La partie se termine lorsqu'un joueur pousse l'un des pions de son adversaire en dehors du plateau.

== MOUVEMENTS INVALIDES ==
	Il est impossible de pousser un pion adverse avec un déplacement lattéral.
	Il est également impossible de pousser des pions adverses si le rapport de force expliqué précédemment n'est pas respecté.
	Il est impossible de pousser ses propres pions.
	Il est impossible de déplacer un pion de plusieurs cases à la fois.
	Il est impossible de déplacer un groupe de plus de 3 pions.
	Il est également impossible de déplacer un groupe de pions si ces derniers ne sont pas alignés.
	D'autres mouvements impossibles existent, mais ils sont liés à une mauvaise manipulation d'un utilisateur (exemple : un mouvement dont le point de départ n'est pas un pion lui appartenant)

== JOUER EN LOCAL ==
	Si l'utilisateur choisit de jouer en local, il fera face à l'intelligence artificielle (IA).
	Pour effectuer un mouvement, il doit inscrire, dans le champ situé dans la partie droite de l'interface, les coordonnées du plateau correspondant au point de départ et d'arrivée de son mouvement avec la syntaxe suivante :		A1:B2
	Si une erreur de syntaxe est détectée, le déplacement n'est pas pris en compte et le joueur peut réécrire son coup.
	Si la syntaxe est bonne, mais que le mouvement est invalide, la mention "Déplacement invalide" apparaîtra et le joueur perdra son tour.
	
	Après avoir joué, l'IA réfléchira et jouera un déplacement qu'elle considère adéquat. Durant le temps de réflexion, le jeu se fige, et il est impossible de rentrer un nouveau déplacement.
	Une fois le déplacement de l'IA effectué, la main revient à l'utilisateur et il peut jouer un nouveau déplacement.

== JOUER EN RESEAU ==
	Si l'utilisateur choisit de jouer en réseau, il utilisera l'IA pour défier un autre joueur.
	Dans ce cas, il suffit d'appuyer sur la touche 'Entrée' après avoir sélectionné le champ d'entrée. Ce dernier n'a pas besoin d'être rempli, et tout contenu qui y aurait été inscrit sera ignoré car l'IA joue son propre déplacement.
	Comme pour le jeu en local, le jeu est figé pendant le temps de réflexion de l'adversaire.
	Si un mouvement invalide est envoyé par l'IA ou par l'adversaire, l'auteur de ce déplacement sera disqualifié et perdra instantanément la partie.
