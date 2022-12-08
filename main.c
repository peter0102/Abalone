#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "deplacement.h"


#define MAX_I 10
#define MAX_J 10
#define INFINITY 147483648

#define CASE_VIDE '0'
#define CASE_NOIRE 'N'
#define CASE_BLANCHE 'B'

Plateau plateau = {
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_BLANCHE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_VIDE, CASE_VIDE},
    {CASE_VIDE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_NOIRE, CASE_VIDE},
    {CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE, CASE_VIDE}
};

void display(Plateau p){
    for (int i=0; i<MAX_I; i++){
        for (int j=0; j<MAX_J; j++){
            if (p[i][j]==CASE_BLANCHE){
                printf("W | ");
            }
            if (p[i][j]==CASE_NOIRE){
                printf("B | ");
            }
            if (p[i][j]==CASE_VIDE){
                printf(". | ");
            }
        }
        printf("\n");
    }
}


int isItWin(Plateau p){
    int victory = 0;
        for (int i=0; i<=8; i++){
            if (p[0][i]!=0) {victory = 1;}
            if (p[i][9]!=0) {victory = 1;}
            if (p[9][(9-i)]!=0) {victory = 1;}
            if (p[(9-i)][0]!=0) {victory = 1;}
        }
    if (victory==1){
        printf("The game is won !\n\n");
    }
    return victory;
}

char abs_c(char v){
    if(v<0){
        return(-v);
    }
    else{
        return(v);
    }
}


char move(Plateau plat,Move m){

    /*
     * Fonction move provisoire
     * -> elle est trop grosse et mal optimisée
     * -> il y a beaucoup de rustines
     * -> provisoire car une autre fonction arrive : plusieurs fonctions pour chaque étape
     */

    // current_player = 1 ou 2 suivant le joueur actuel
    char current_player=CASE_BLANCHE; //Les blancs commencent dans l'exemple

    // other_player = 1 ou 2 suivant l'autre joueur
    char other_player = CASE_NOIRE;

    // no_player = 0 il n'y a pas de pions
    char no_player = CASE_VIDE;

    //erreur = 1
    char error = 1;

    //success = 0
    char success = 0;

    //nombre de pions
    char nb_pions;

    //test couleur position initiale
    if(plat[m.x1][m.y1] != current_player){
        return(error);
    }


    //test position finale
    char opponents = 0;
    if(plat[m.x2][m.y2] == current_player){
        return(error);
    }
    else if(plat[m.x2][m.y2] ==(other_player)){
        opponents++;
    }


//** 1) Déplacement en ligne horizontal **************************************************************
    //déplacement en ligne horizontal
    if(m.x1 == m.x2) {
        nb_pions = abs_c(m.y1 - m.y2);

        //nombre de pions doit être <= 3
        if(nb_pions > 3){
            return(error);
        }

// 1.1 déplacement vers la droite
        if (m.y1 < m.y2) {
            //verification de la couleur de la selection
            for (char i = m.y1 + 1; i < m.y2; i++) {
                if (plat[m.x1][i] != current_player) {
                    return (error);
                }
            }

            //comptage du nombre d'adversaires
            if (opponents == 1) {
                if (plat[m.x1][m.y1 + 1] == other_player) {
                    opponents++;
                    if (plat[m.x1][m.y1 + 2] == (other_player)) {
                        opponents++;
                    } else if (plat[m.x1][m.y1 + 2] == current_player) {
                        return (error);
                    }
                } else if (plat[m.x1][m.y1 + 1] == current_player) {
                    return (error);
                }
            }


            //verification des rapports de force
            if (nb_pions <= opponents) {
                return (error);
            }


            //déplacement effectif
            //On ne déplace que le premier pion pour économiser des ressources
            plat[m.x1][m.y1] = no_player;
            plat[m.x2][m.y2] = current_player;
            if (opponents >= 1) {
                plat[m.x2][m.y2 + opponents] = other_player;
            }
        }

// 1.2 déplacement vers la gauche
        if (m.y1 > m.y2) {
            //verification de la couleur de la selection
            for (char i = m.y1 - 1; i > m.y2; i--) {
                if (plat[m.x1][i] != current_player) {
                    return (error);
                }
            }

            //comptage du nombre d'adversaires
            if (opponents == 1) {
                if (plat[m.x1][m.y1 - 1] == other_player) {
                    opponents++;
                    if (plat[m.x1][m.y1 - 2] == (other_player)) {
                        opponents++;
                    } else if (plat[m.x1][m.y1 - 2] == current_player) {
                        return (error);
                    }
                } else if (plat[m.x1][m.y1 - 1] == current_player) {
                    return (error);
                }
            }


            //verification des rapports de force
            if (nb_pions <= opponents) {
                return (error);
            }


            //déplacement effectif
            //On ne déplace que le premier pion pour économiser des ressources
            //premier à la position du dernier
            plat[m.x1][m.y1] = no_player;
            plat[m.x2][m.y2] = current_player;
            if (opponents >= 1) {
                plat[m.x2][m.y2 - opponents] = other_player;
            }
        }
    }

//****** 2) Déplacement en ligne vertical ****************************************************************************

        //déplacement en ligne vertical
    else if(m.y1 == m.y2) {

        nb_pions = abs_c(m.x1 - m.x2);

        //nombre de pions doit être <= 3
        if(nb_pions > 3){
            return(error);
        }

// 2.1 déplacement vers le bas
        if (m.x1 < m.x2) {
            //verification de la couleur de la selection
            for (char i = m.x1 + 1; i < m.x2; i++) {
                if (plat[i][m.y1] != current_player) {
                    return (error);
                }
            }

            //comptage du nombre d'adversaires
            if (opponents == 1) {
                if (plat[m.x1 + 1][m.y1] == other_player) {
                    opponents++;
                    if (plat[m.x1 + 2][m.y1] == (other_player)) {
                        opponents++;
                    } else if (plat[m.x1 + 2][m.y1] == current_player) {
                        return (error);
                    }
                } else if (plat[m.x1 + 1][m.y1] == current_player) {
                    return (error);
                }
            }



            //verification des rapports de force
            if (nb_pions <= opponents) {
                return (error);
            }



            //déplacement effectif
            //On ne déplace que le premier pion pour économiser des ressources
            plat[m.x1][m.y1] = no_player;
            plat[m.x2][m.y2] = current_player;
            if (opponents >= 1) {
                plat[m.x2 + opponents][m.y2] = other_player;
            }
        }

        //***********************************************

// 2.2 déplacement vers le haut
        if (m.x1 > m.x2) {
            //verification de la couleur de la selection
            for (char i = m.x1 - 1; i > m.x2; i--) {
                if (plat[i][m.y1] != current_player) {
                    return (error);
                }
            }

            //comptage du nombre d'adversaires
            if (opponents == 1) {
                if (plat[m.x1 - 1][m.y1] == other_player) {
                    opponents++;
                    if (plat[m.x1 - 2][m.y1] == (other_player)) {
                        opponents++;
                    }
                        //Cas 2 other_player suivi de current_player
                    else if (plat[m.x1 - 2][m.y1] == current_player) {
                        return (error);
                    }
                }
                    //Cas other_player suivi de current_player
                else if (plat[m.x1 - 1][m.y1] == current_player) {
                    return (error);
                }
            }


            //verification des rapports de force
            if (nb_pions <= opponents) {
                return (error);
            }


            //déplacement effectif
            //On ne déplace que le premier pion pour économiser des ressources
            plat[m.x1][m.y1] = no_player;
            plat[m.x2][m.y2] = current_player;
            if (opponents >= 1) {
                plat[m.x2 - opponents][m.y2] = other_player;
            }
        }
    }

//************************************************************************************************
//************************************************************************************************

        //Déplacement latéral : pas d'ennemis dans les cases d'arrivées (ici la première)
        /*
        if(opponents>0){
            return(error);
        }
         */


        //déplacement latéral de taille 1 = déplacement en ligne de taille 1


//** 1) déplacement latéral de taille 2 **********************************************************
    else if((abs_c(m.x1-m.x2)+abs_c(m.y1-m.y2))==2){

        if(opponents>0){
            return(error);
        }

        //On ne peut pas savoir si on se déplace de manière horizontale ou verticale
        //Solution : tester les cases du carré x1y1 x1y2 x2y1 x2y2

//****** 1.1 déplacement latéral horizontal
        if(plat[m.x1][m.y2]==current_player){

            if(opponents>0){
                return(error);
            }

            //test de la deuxième arrivée
            if(plat[m.x2][m.y1]!=no_player){
                return(error);
            }

            //déplacement effectif
            plat[m.x1][m.y1] = no_player;
            plat[m.x2][m.y1] = no_player;
            plat[m.x2][m.y2] = current_player;
            plat[m.x1][m.y2] = current_player;
        }


//****** 1.2 déplacement latéral vertical
        else if(plat[m.x2][m.y1]==current_player){

            if(opponents>0){
                return(error);
            }

            //test de la deuxième arrivée
            if(plat[m.x1][m.y2]!=no_player){
                return(error);
            }

            //déplacement effectif
            plat[m.x1][m.y1] = no_player;
            plat[m.x1][m.y2] = no_player;
            plat[m.x2][m.y1] = current_player;
            plat[m.x2][m.y2] = current_player;
        }


//****** 1.3 Pas de pion allié sur les cases adjacentes
        else{
            return(error);
        }

    }


//** 2) déplacement latéral de taille 3 **********************************************************

//** 2.1 déplacement latéral vertical de taille 3
    else if(abs_c(m.x1-m.x2)==2 && abs_c(m.y1-m.y2)==1){

        if(opponents>0){
            return(error);
        }

        //x1 bas & x2 haut
        if(m.x1>m.x2){

            //test de la sélection
            if(plat[m.x1-1][m.y1]!=current_player || plat[m.x2][m.y1]!=current_player){
                return(error);
            }

            //test de l'arrivée
            if(plat[m.x1][m.y2]!=no_player || plat[m.x1-1][m.y2]!=no_player){
                return(error);
            }

            //déplacement effectif gauche et droite
            plat[m.x1][m.y1] = no_player;
            plat[m.x1-1][m.y1] = no_player;
            plat[m.x2][m.y1] = no_player; //x1-2 = x2
            plat[m.x1][m.y2] = current_player;
            plat[m.x1-1][m.y2] = current_player;
            plat[m.x2][m.y2] = current_player; //x1-2 = x2

        }


        //x1 haut & x2 bas
        if(m.x1>m.x2){

            //test de la sélection
            if(plat[m.x1+1][m.y1]!=current_player || plat[m.x2][m.y1]!=current_player){
                return(error);
            }

            //test de l'arrivée
            if(plat[m.x1][m.y2]!=no_player || plat[m.x1+1][m.y2]!=no_player){
                return(error);
            }

            //déplacement effectif gauche et droite
            plat[m.x1][m.y1] = no_player;
            plat[m.x1+1][m.y1] = no_player;
            plat[m.x2][m.y1] = no_player; //x1+2 = x2
            plat[m.x1][m.y2] = current_player;
            plat[m.x1+1][m.y2] = current_player;
            plat[m.x2][m.y2] = current_player; //x1+2 = x2
        }

    }

// 2.2 déplacement latéral horizontal de taille 3
    else if(abs_c(m.x1-m.x2)==2 && abs_c(m.y1-m.y2)==1){

        if(opponents>0){
            return(error);
        }

        //y1 droite & y2 gauche
        if(m.y1<m.y2){

            //test de l'arrivée
            if(plat[m.x2][m.y1]!=no_player || plat[m.x2][m.y1+1]!=no_player){
                return(error);
            }

            //déplacement effectif gauche et droite
            plat[m.x1][m.y1] = no_player;
            plat[m.x1][m.y1+1] = no_player;
            plat[m.x1][m.y1+2] = no_player; //y1+2 = y2
            plat[m.x2][m.y1] = current_player;
            plat[m.x2][m.y1+1] = current_player;
            plat[m.x2][m.y1+2] = current_player; //y1+2 = y2

        }


        //y1 gauche & y2 droite
        if(m.y1>m.y2){

            //test de l'arrivée
            if(plat[m.x2][m.y1]!=no_player || plat[m.x2][m.y1-1]!=no_player){
                return(error);
            }

            //déplacement effectif gauche et droite
            plat[m.x1][m.y1] = no_player;
            plat[m.x1][m.y1-1] = no_player;
            plat[m.x1][m.y1-2] = no_player; //y1-2 = y2
            plat[m.x2][m.y1] = current_player;
            plat[m.x2][m.y1-1] = current_player;
            plat[m.x2][m.y1-2] = current_player; //y1-2 = y2

        }

    }

        //sélection trop grande
    else{
        return(error);
    }

    return(success);
}
void resetBoard(Plateau p) {
    p=plateau;
}
int minimax(Plateau p,int depth,int alpha,int beta,bool isMaximizingPlayer){
	return 1;
}
char aiMove(Plateau p) {
    Move m;
	int score=-INFINITY;
	for (int i=1;i<MAX_I-1;i++) {
		for (int j=1;j<MAX_J-1;j++) {
			if (p[i][j]==CASE_NOIRE) {
                //possibleMove(p); // liste des mouvements possible
                m.x1=i;
                m.y1=j;
                m.x2=i-1;
                m.y2=j;
                move(p,m);
				int scoreMove=minimax(p,0,1,1,false);
				resetBoard(p);
				if (scoreMove>score) { // choisit le meilleur move en fonction du score
					score=scoreMove;
                    m.x1=i;
                    m.y1=j;
                    m.x2=i+1;
                    m.y2=j+1;
				}
			}
		}
	}
    char a=move(p,m);
    printf("\n\nRetour de la fonction move : %d\n",a);
}

char playerMove(Plateau p){
    char charac[1000]="";
    printf("Quel mouvement ? de type xx:xx\n");
    scanf("%s",charac);
    Move m=translate_move(charac);
    char a=move(p,m);
    printf("\n\nRetour de la fonction move : %d",a);
}


int main(int argc, char *argv[]) {
    int end=0;
    int turn_count=1;
    printf("Début du jeu\n");
    display(plateau);
    while (end!=1) {
		if(turn_count%2==1) {
            printf("Tour %i\n",turn_count);
		    printf("C'est au tour des noirs(ia) de jouer\n");
		    aiMove(plateau);
            display(plateau);
            printf("\n*************************************\n");
		}
		else {
            printf("Tour %i\n",turn_count);
	    	printf("C'est à votre tour de jouer\n");
		    playerMove(plateau);
            printf("\n*************************************\n");
		}
		turn_count++;
	}
}