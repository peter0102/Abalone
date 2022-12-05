Main : 
-Lancement du jeu 
-Initialisation
-Nombre de tours (boucle principale)
-Lecture
-Traduction + Vérification
-Déplacement + Vérification
-Affichage
-Fin de jeu
	
		
	
	
Répartition
	
1 (Mame) : 
-définir la grille : Structure/Tableau + Dictionnaire
-Initialiser (cases vides 0 | blancs 1 | noirs 2)


2 (Salma) : 
-Gestion d’erreurs au lancement du jeu
-Commande help : afficher les commandes

3 (Isaac) : 
-Fonction “lecture” : Prendre les arguments sur le terminal “A1:B1”
-Gestion d’erreur (syntaxe invalide)

4 (Peter) : 
-Nombre de tours + savoir qui doit jouer 
	=> Solution : Nb tours initialisé à 1
	-Joueur = Nbtours%2 +1 | 2 → Noir | 1→Blanc |

5 (Romaissae) : 
-Affichage du jeu

6 (Pierre) : 
-Gestion des bords / Fin de partie

7 (Mahmoud & Alexandre) Déplacement : 
-7A Traduction 
	-Vérification coups demandés : couleurs + tous les endroits
	-Déplacement en ligne ou latéral
	=> Solution : 
		Créer Structure avec : 
			Nombre de pions
			Type de mouvement (en ligne ou latéral)
			Position de départ en numérique
			Position d’arrivée en numérique

				Nb pions | Ligne / Latéral | C1 | C2


-7B Déplacement : 
	-Déplacement en ligne :
		-Vérification du coup (case vide ou avec un adversaire et nombre de pions du joueur supérieur à celui de l’adversaire)

	-Déplacement latéral :
		-Vérification du coup (toutes les cases d’arrivées sont vides)




Plus tard : 
Timer
Intelligence artificielle
Communication serveur/réseau
