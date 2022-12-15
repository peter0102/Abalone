#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "global.h"
#include "main.h"
#include "ai.h"
#include "allMove.h"
#include "move.h"

void display(Board board){
    printf("1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |\n");
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
        if(board[0][i]!=0 || board[i][9]!=0 || board[9][(9-i)]!=0 || board[(9-i)][0]!=0){
            return(ERROR);
        }
    }
    return SUCCESS;
}

void playerMove(Board board,char current_player,char other_player){
    Move m;
    char charac[1000]="";
    printf("Quel mouvement ? de type xx:xx\n");
    scanf("%s",charac);
    translateMove(m,charac);
    char a=allMove(board,m,current_player,other_player);
    display(board);
}

int main(int argc, char *argv[]) {
    Board board = {
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
    };
    char current_player;
    char other_player;
    int turn_count=1;
    printf("Début du jeu\n");
    display(board);
    while (isItWin(board)!=SUCCESS){
		if(turn_count%2==1) { //turn_count = 1 --> current_player = 'B'
            current_player = BLACK;
            other_player = WHITE;
            printf("Tour %i\n",turn_count);
		    printf("C'est au tour des noirs (IA) de jouer\n");
		    Move bestMove;
            aiBestMove(bestMove, board,current_player,other_player);
            char a = allMove(board,bestMove,current_player,other_player);
            display(board);
            printf("\n*************************************\n");
		}
		else { //turn_count = 2 --> current_player = 'W'
            current_player = WHITE;
            other_player = BLACK;
            printf("Tour %i\n",turn_count);
	    	printf("C'est à votre tour (blancs) de jouer\n");
		    playerMove(board,current_player,other_player);
            display(board);
            printf("\n*************************************\n");
		}
		turn_count++;
	}
}
