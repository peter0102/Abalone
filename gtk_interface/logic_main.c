#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../global.h"
#include "interface.h"
#include "logic_main.h"
#include "../ai.h"
#include "../allMove.h"
#include "../move.h"

void display(Board board){
    for (int i=1; i<MAX_I-1; i++){
        for (int j=1; j<MAX_J-1; j++){
            if (board[i][j]==WHITE){
                printf("W | ");
            }
            if (board[i][j]==BLACK){
                printf("B | ");
            }
            if (board[i][j]==EMPTY){
                printf(". | ");
            }
        }
        printf("\n");
    }
}

char isItWin(Board board){
    for(char i=0; i<=8; i++){
        if(board[0][i] != EMPTY || board[i][9] != EMPTY || board[9][(9-i)] != EMPTY || board[(9-i)][0] != EMPTY){
            return(ERROR);
        }
    }
    return SUCCESS;
}

char playerMove(Board board){
    Move m;
    char charac[1000]="";
    printf("Quel mouvement ? de type xx:xx\n");
    scanf("%s",charac);
    translateMove(m,charac);
    char a=allMove(board,m,WHITE,BLACK);
}

void nextTurn(GameData* gd, Move move) {
    //On vérifie que la partie ne soit pas déjà terminée
    if (isItWin(gd->board) == ERROR) {
        printf("Partie terminée : évènement ignoré");
        return;
    }

    gd->current_player = otherPlayer(gd->current_player);
    if (gd->current_player == ERROR) {
        printf("Erreur d'affectation des joueurs. Evènement ignoré.");
        return;
    }
    setTurnColor(gd->current_player);    

    gd->nb_turn ++;
    setTurnNumber(gd->nb_turn);

    if (gd->me != gd->current_player) {
        char a = allMove(gd->board, move, gd->current_player, otherPlayer(gd->current_player));
        if (a == ERROR) printf("Mouvement invalide");
        drawBoard(gd->board);
        nextTurn(gd, move);
    } else {
        //char a = aiMove(gd->board, gd->current_player, otherPlayer(gd->current_player));
        drawBoard(gd->board);
    }
}