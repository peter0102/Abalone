#include "global.h"

char otherPlayer(char player) {
    if (player == BLACK) return WHITE;
    else if (player == WHITE) return BLACK;
    else return ERROR;
}