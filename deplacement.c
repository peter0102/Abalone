#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deplacement.h"

char moveChrConvert (char chr, char type) {
    char index = ERROR;
    switch (type) {
        case 'l': index = (chr-'@'); break;
        case 'n': index = (chr-'0'); break;
        default: printf("%s", "Erreur de conversion : type de caractère inconnu."); return -1;
    }
    return (index > 0 && index < 9) ? index : ERROR;
}

char moveChrConvertReverse (char index, char type) {
    if (index < 1 || index > 8) return ERROR;
    switch (type) {
        case 'l': return (index + '@');
        case 'n': return (index + '0');
        default: printf("%s", "Erreur de conversion : type de caractère inconnu."); return ERROR;
    }
}

Move translateMove(char* input) {
    Move move = createMove(ERROR, ERROR, ERROR, ERROR);

    //Si la longueur de l'entree n'est pas 5, il y a erreur
    if (strlen(input) != 5) return move;
    //Si le 3eme caractere n'est pas ':', il y a erreur
    if (input[2] != ':') return move;

    char numbers[] = {
        moveChrConvert(input[0], 'l'),
        moveChrConvert(input[1], 'n'),
        moveChrConvert(input[3], 'l'),
        moveChrConvert(input[4], 'n')
    };
    for (int i = 0; i < 4; i++) {
        if (numbers[i] == ERROR) return move;
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            move[i][j] = numbers[(2*i)+j];
    }
    return move;
}

char* translateMoveReverse(Move move) {
    char* str = malloc(5);

    str[0] = moveChrConvertReverse(move[0][0], 'l');
    str[1] = moveChrConvertReverse(move[0][1], 'n');
    str[2] = ':';
    str[3] = moveChrConvertReverse(move[1][0], 'l');
    str[4] = moveChrConvertReverse(move[1][1], 'n');
    return str;
}

Move createMove(int x1, int y1, int x2, int y2) {
    Move move = malloc(2 * sizeof(char*));
    for(int i = 0; i < 2; i++)
        move[i] = malloc(2);
    move[0][0] = (char)x1;
    move[1][0] = (char)y1;
    move[0][1] = (char)x2;
    move[1][1] = (char)y2;
    return move;
}

void printMove(Move move) {
    printf("%i, %i\n%i, %i\n\n", move[0][0], move[1][0], move[0][1], move[1][1]);
}
