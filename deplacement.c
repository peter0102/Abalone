#include <stdio.h>
#include <string.h>
#include "deplacement.h"

int move_chr_convert (char chr, char type) {
    int index = -1;
    switch (type) {
        case 'l': index = (int)(chr-'@'); break;
        case 'n': index = (int)(chr-'0'); break;
        default: printf("%s", "Erreur de conversion : type de caractère inconnu."); return -1;
    }
    return (index > 0 && index < 9) ? index : -1;
}

void move_change_all(Move* move, int new_coords[4]) {
    move->x1 = new_coords[0];
    move->y1 = new_coords[1];
    move->x2 = new_coords[2];
    move->y2 = new_coords[3];
}

Move translate_move(char* input) {
    Move move = {-1, -1, -1, -1};

    //Si la longueur de l'entree n'est pas 5, il y a erreur
    if (strlen(input) != 5) return move;

    //Si le 3eme caractere n'est pas ':', il y a erreur
    if (input[2] != ':') return move;

    int numbers[] = {
        move_chr_convert(input[0], 'l'),
        move_chr_convert(input[1], 'n'),
        move_chr_convert(input[3], 'l'),
        move_chr_convert(input[4], 'n')
    };

    for (int i = 0; i < 4; i++) {
        if (numbers[i] == -1) return move;
    }
    move_change_all(&move, numbers);
    return move;
}

void print_move(Move move) {
    printf("%i, %i\n%i, %i\n\n", move.x1, move.y1, move.x2, move.y2);
}