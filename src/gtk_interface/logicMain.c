#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "../global.h"
#include "interface.h"
#include "../initCheck.h"
#include "logicMain.h"
#include "../ai.h"
#include "../allMove.h"
#include "../move.h"

char isItWin(Board board){
    for(char i=0; i<=8; i++){
        if(board[0][i] != EMPTY || board[i][9] != EMPTY || board[9][(9-i)] != EMPTY || board[(9-i)][0] != EMPTY){
            return(SUCCESS);
        }
    }
    return ERROR;
}

GameData init(InitData data) {
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
	switch(data.mode) {
		case 'b': gd.me = BLACK; break;
		case 'w': gd.me = WHITE; break;
        case 'c': gd.me = BLACK; break;
		case 's': gd.me = WHITE; break;
		default: gd.me = ERROR; break;
	}
    gd.fdclient = data.fdclient;
	gd.current_player = BLACK;
	setPlayerColor(gd.me);
	setTurnColor(gd.current_player);
    gd.nb_turn = 1;
    
	return gd;
}

void nextTurnLocal(GameData* gd, Move move) {
    gd->current_player = otherPlayer(gd->current_player);
    if (gd->current_player == ERROR) {
        setNotification("Erreur d'affectation des joueurs");
        return;
    }

    setTurnColor(gd->current_player);    
    gd->nb_turn ++;
    setTurnNumber(gd->nb_turn);

    if (gd->me != gd->current_player) {
        char a = allMove(gd->board, move, otherPlayer(gd->current_player), gd->current_player);
        if (a == ERROR) setNotification("Déplacement invalide");
        else {
            setLastMove(move, otherPlayer(gd->current_player));
            setNotification("");
        }
        drawBoard(gd->board);
        if (isItWin(gd->board) == SUCCESS) {
            setNotification("Victoire");
            return;
        }
        nextTurnAILocal(gd);
    } else setNotification("Ce n'est pas votre tour !");
}

void nextTurnAILocal(GameData* gd) {
    gd->current_player = otherPlayer(gd->current_player);
    if (gd->current_player == ERROR) {
        setNotification("Erreur d'affectation des joueurs");
        return;
    }

    setTurnColor(gd->current_player);    
    gd->nb_turn ++;
    setTurnNumber(gd->nb_turn);

    if (gd->me != gd->current_player) {
        setNotification("AI : Ce n'est pas son tour !");
        return;
    }
    Move move;
    aiBestMove(move, gd->board, otherPlayer(gd->current_player), gd->current_player);
    char a = allMove(gd->board, move, otherPlayer(gd->current_player), gd->current_player);
    if (a == ERROR) {
        setNotification("IA: Déplacement invalide");
        return;
    }

    setLastMove(move, otherPlayer(gd->current_player));
    drawBoard(gd->board);
    
    if (isItWin(gd->board) == SUCCESS) {
        setNotification("Défaite");
        return;
    }
}

void nextTurnPlayerNetwork(GameData* gd) {
    if (gd->me == gd->current_player) {
        Move move;
        aiBestMove(move, gd->board, gd->current_player, otherPlayer(gd->current_player));
        char* moveStr = translateMoveReverse(move);
        int w = write(gd->fdclient, moveStr, 6);
        
        char a = allMove(gd->board, move, gd->current_player, otherPlayer(gd->current_player));
        if (a == ERROR) {
            setNotification("IA: Déplacement invalide");
            // Défaite
            return;
        }
        else {
            setLastMove(move, gd->current_player);
            setNotification("");
        }
    }
    else setNotification("Ce n'est pas votre tour !");

    gd->current_player = otherPlayer(gd->current_player);
    if (gd->current_player == ERROR) {
        setNotification("Erreur d'affectation des joueurs");
    }
    setTurnColor(gd->current_player);    
    gd->nb_turn ++;
    setTurnNumber(gd->nb_turn);
    drawBoard(gd->board);
    
    if (isItWin(gd->board) == SUCCESS) {
        setNotification("Victoire");
        return;
    }
    nextTurnOpponentNetwork(gd);
}

void nextTurnOpponentNetwork(GameData* gd) {
    if (gd->me != gd->current_player) {
        char* moveStr = malloc(6);
        int r = read(gd->fdclient, moveStr, 6);
        if (r != 6) {
            setNotification("Mvt mal réceptionné");
            //On gagne!
            return;
        }
        Move move;
        translateMove(move, moveStr);
        char a = allMove(gd->board, move, gd->current_player, otherPlayer(gd->current_player));
        if (a == ERROR) setNotification("Adv : Déplacement invalide"); //On gagne!
        else {
            setLastMove(move, gd->current_player);
            setNotification("");
        }
        
    } else setNotification("Adv: Ce n'est pas son tour !");
    gd->current_player = otherPlayer(gd->current_player);
    if (gd->current_player == ERROR) {
        setNotification("Erreur d'affectation des joueurs");
        return;
    }
    setTurnColor(gd->current_player);    
    gd->nb_turn ++;
    setTurnNumber(gd->nb_turn);
    drawBoard(gd->board);

    if (isItWin(gd->board) == SUCCESS) {
        setNotification("Défaite");
        return;
    }
}