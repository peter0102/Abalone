#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "move.h"


#define ERROR 'x'
#define SUCCESS 'l'

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

void translateMove(Move move, char* input) {
    move[0][0] = ERROR; move[0][1] = ERROR; move[1][0] = ERROR; move[1][1] = ERROR;

    //Si la longueur de l'entree n'est pas 5, il y a erreur
    if (strlen(input) != 5) return;
    //Si le 3eme caractere n'est pas ':', il y a erreur
    if (input[2] != ':') return;

    char numbers[] = {
        moveChrConvert(input[0], 'l'),
        moveChrConvert(input[3], 'l'),
        moveChrConvert(input[1], 'n'),
        moveChrConvert(input[4], 'n')
    };
    for (int i = 0; i < 4; i++) {
        if (numbers[i] == ERROR) return;
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            move[i][j] = numbers[(2*i)+j];
    }
    return;
}

char* translateMoveReverse(Move move) {
    char* str = malloc(6);

    str[0] = moveChrConvertReverse(move[0][0], 'l');
    str[1] = moveChrConvertReverse(move[1][0], 'n');
    str[2] = ':';
    str[3] = moveChrConvertReverse(move[0][1], 'l');
    str[4] = moveChrConvertReverse(move[1][1], 'n');
    str[5] = '\0';
    return str;
}


void printMove(Move move) {
    printf("%i, %i\n%i, %i\n\n", move[0][0], move[1][0], move[0][1], move[1][1]);
}
