//fichier de test à ignorer
#include "global.h"
#include "allMove.h"

char lmove(Board board, char current_player, Move* list_possible_moves[56]){
    char nb_possible_moves = 0;
    //Move list_possible_moves[56]; //coups max = 4 directions * 14 pions
    Triple line;
    char nb_allies_line = 0;
    Triple ver;
    char nb_allies_ver = 0;
    for(char i=0;i<8;i++){
        for(char j=0;j<8;j++){
            for(char k=0;board[i][j+k] == current_player && k<3;k++){
                nb_allies_line++;
                line[0][k] = i;
                line[1][k] = j+k;
            }
            for(char l=0;board[i+l][j] == current_player && l<3;l++){
                nb_allies_ver++;
                ver[0][l] = i+l;
                ver[1][l] = j;
            }
            //check des moves
            //checkMove(Board board, Move m,char current_player)

            //en ligne
            for(char a=0;a<nb_allies_line;a++){
                Move m_right_line={{line[0][0],line[0][0]},{line[1][0],line[1][a]+1}}; //à droite
                Move m_left_line={{line[0][0],line[0][0]},{line[1][a],line[1][0]-a}}; //à gauche
                Move m_up_line={{line[0][0],line[0][0]},{line[1][0],line[1][a]-1}}; //en haut
                Move m_down_line={{line[0][0],line[0][0]},{line[1][0],line[1][a]+1}}; //en bas

                //Mise sous forme de pointeurs
                Move* m[4]={&m_right_line,&m_left_line,&m_up_line,&m_down_line};

                for(char b=0;b<4;b++) {
                    if (checkMove(board, *m[b], current_player) == SUCCESS) {
                        list_possible_moves[nb_possible_moves] = m[b];
                        nb_possible_moves++;
                    }
                }
            }

            //vertical
            for(char a=0;a<nb_allies_line;a++){
                Move m_right_ver={{ver[0][0],ver[0][0]},{ver[1][0],ver[1][a]+1}}; //à droite
                Move m_left_ver={{ver[0][0],ver[0][0]},{ver[1][a],ver[1][0]-a}}; //à gauche
                Move m_up_ver={{ver[0][0]+a,ver[0][0]-a},{ver[1][0],ver[1][0]}}; //en haut
                Move m_down_ver={{ver[0][0],ver[0][0]},{ver[1][a]+1,ver[1][0]}}; //en bas

                //Mise sous forme de pointeurs
                Move* m[4]={&m_right_ver,&m_left_ver,&m_up_ver,&m_down_ver};

                for(char b=0;b<4;b++) {
                    if (checkMove(board, *m[b], current_player) == SUCCESS) {
                        list_possible_moves[nb_possible_moves] = m[b];
                        nb_possible_moves++;
                    }
                }
            }
        }
    }
    return(nb_possible_moves);
}