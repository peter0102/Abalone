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

char isItWin(Board board){
    for(char i=0; i<=8; i++){
        if(board[0][i] != EMPTY || board[i][9] != EMPTY || board[9][(9-i)] != EMPTY || board[(9-i)][0] != EMPTY){
            return(ERROR);
        }
    }
    return SUCCESS;
}

GameData init(char mode) {
	GameData gd = {.board = {
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, EMPTY},
        {EMPTY, EMPTY, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, EMPTY, EMPTY},
        {EMPTY, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}
    }};
    
	switch(mode) {
		case 'b': gd.me = BLACK; break;
		case 'w': gd.me = WHITE; break;
		default: gd.me = ERROR; break;
	}
	gd.current_player = BLACK;
	setPlayerColor(gd.me);
	setTurnColor(gd.current_player);
    gd.nb_turn = 1;
	return gd;
}

void nextTurn(GameData* gd, Move move) {
    //On vérifie que la partie ne soit pas déjà terminée
    if (isItWin(gd->board) == ERROR) {
        printf("Partie terminée : évènement ignoré");
        setNotification("Partie déjà terminée");
        return;
    }

    gd->current_player = otherPlayer(gd->current_player);
    if (gd->current_player == ERROR) {
        printf("Erreur d'affectation des joueurs. Evènement ignoré.");
        setNotification("Erreur d'affect. des joueurs");
        return;
    }
    setTurnColor(gd->current_player);    

    gd->nb_turn ++;
    setTurnNumber(gd->nb_turn);

    if (gd->me != gd->current_player) {
        char a = allMove(gd->board, move, otherPlayer(gd->current_player), gd->current_player);
        if (a == ERROR) {
            printf("Déplacement invalide");
            setNotification("Déplacement invalide");
        } else {
            setLastMove(move);
            setNotification("");
        }
        drawBoard(gd->board);
        nextTurn(gd, move);
    } else {
        aiBestMove(move, gd->board, otherPlayer(gd->current_player), gd->current_player);
        char a = allMove(gd->board, move, otherPlayer(gd->current_player), gd->current_player);
        if (a != ERROR) setLastMove(move);
        drawBoard(gd->board);
    }
}