#include <stdio.h>
#include "global.h"
#include "allMove.h"

/*
 * Liste de fonctions à tester
 * absChar
 * checkSuicide
 * whatMove
 * allies
 * active
 * ennemiesLine
 * ennemiesLat
 * ennemies
 * checkColor
 * checkMove
 * checkForList
 * moveLine
 * moveLateral
 * move
 * allMove
 */

//syntaxe message d'erreur : fprintf(stderr, "test_add_1_2: add: expecting %d while got %d", expected, actual)

void testAbsChar(){
    //test de absChar : char absChar(char v)
    char a = -10;
    char b = 7;
    char a_expected = 10;
    char b_expected = 7;
    char a_actual = absChar(a);
    char b_actual = absChar(b);
    if(a_actual != a_expected){
        fprintf(stderr, "allMove: absChar: expecting %d while got %d", a_expected, a_actual);
    }
    if(b_actual != b_expected){
        fprintf(stderr, "allMove: absChar: expecting %d while got %d", b_expected, b_actual);
    }
}

void testCheckSuicide(){
    //bords
    Move a = {{1,4},{0,4}}; //suicide en haut
    Move b = {{5,8},{5,9}}; //suicide à droite
    Move c = {{8,6},{9,6}}; //suicide en bas
    Move d = {{7,1},{7,0}}; //suicide à gauche
    //coup quelconque
    Move e = {{1,1},{2,1}}; //coup autorisé

    if(checkSuicide(a)!=ERROR||checkSuicide(b)!=ERROR||checkSuicide(c)!=ERROR||checkSuicide(d)!=ERROR){
        fprintf(stderr, "allMove: checkSuicide: a suicide has been authorized");
    }
    if(checkSuicide(e)==ERROR){
        fprintf(stderr, "allMove: checkSuicide: authorized move has been considered suicide");
    }

}

void testWhatMove(){
    //test de whatMove : whatMove(Board board,Move m, char current_player)
    /* Liste des mouvements possibles
     * LINE_HOR_RIGHT 'a'
     * LINE_HOR_LEFT 'b'
     * LINE_VER_DOWN 'c'
     * LINE_VER_UP 'd'
     * LAT_2_HOR 'e'
     * LAT_2_VER 'f'
     * LAT_3_VER_X0_DOWN 'g'
     * LAT_3_VER_X0_UP 'h'
     * LAT_3_HOR_Y0_RIGHT 'i'
     * LAT_3_HOR_Y0_LEFT 'j'
     */
    Board b = {
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, WHITE, EMPTY, WHITE, EMPTY, WHITE, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, WHITE, EMPTY, WHITE, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, WHITE, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, EMPTY, EMPTY},
            {EMPTY, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}
    };

    char current_player = WHITE;

    //En ligne horizontal à droite
    Move line_hor_right_one = {{1,1},{7,8}}; //taille 1
    Move line_hor_right_two = {{1,1},{6,8}}; //taille 2
    Move line_hor_right_three = {{1,1},{5,8}}; //taille 3
    if(whatMove(b,line_hor_right_one,current_player) != LINE_HOR_RIGHT||\
    whatMove(b,line_hor_right_two,current_player) != LINE_HOR_RIGHT||\
    whatMove(b,line_hor_right_three,current_player) != LINE_HOR_RIGHT){
        fprintf(stderr, "allMove: whatMove: unrecognized movement : LINE_HOR_RIGHT");
    }

    //En ligne horizontal à gauche
    Move line_hor_left_one = {{1,1},{2,1}}; //taille 1
    Move line_hor_left_two = {{1,1},{3,1}}; //taille 2
    Move line_hor_left_three = {{1,1},{4,1}}; //taille 3
    if(whatMove(b,line_hor_left_one,current_player) != LINE_HOR_LEFT||\
    whatMove(b,line_hor_left_two,current_player) != LINE_HOR_LEFT||\
    whatMove(b,line_hor_left_three,current_player) != LINE_HOR_LEFT){
        fprintf(stderr, "allMove: whatMove: unrecognized movement : LINE_HOR_LEFT");
    }

    //En ligne vertical vers le bas
    Move line_ver_down_one = {{5,6},{2,2}}; //taille 1
    Move line_ver_down_two = {{4,6},{2,2}}; //taille 2
    Move line_ver_down_three = {{3,6},{2,2}}; //taille 3
    if(whatMove(b,line_ver_down_one,current_player) != LINE_VER_DOWN||\
    whatMove(b,line_ver_down_two,current_player) != LINE_VER_DOWN||\
    whatMove(b,line_ver_down_three,current_player) != LINE_VER_DOWN){
        fprintf(stderr, "allMove: whatMove: unrecognized movement : LINE_VER_DOWN");
    }

    //En ligne vertical vers le haut
    Move line_ver_up_one = {{3,2},{2,2}}; //taille 1
    Move line_ver_up_two = {{4,2},{2,2}}; //taille 2
    Move line_ver_up_three = {{5,2},{2,2}}; //taille 3
    if(whatMove(b,line_ver_up_one,current_player) != LINE_VER_UP||\
    whatMove(b,line_ver_up_two,current_player) != LINE_VER_UP||\
    whatMove(b,line_ver_up_three,current_player) != LINE_VER_UP){
        fprintf(stderr, "allMove: whatMove: unrecognized movement : LINE_VER_UP");
    }

    //Latéral taille 2 horizontal
    Move lat_two_hor_left_up_down = {{3,4},{4,3}}; //à gauche commençant en haut finissant en bas
    Move lat_two_hor_left_down_up = {{4,3},{4,3}}; //à gauche commençant en bas finissant en haut
    Move lat_two_hor_right_up_down = {{3,4},{4,5}}; //à droite commençant en haut finissant en bas
    Move lat_two_hor_right_down_up = {{4,3},{4,5}}; //à droite commençant en bas finissant en haut
    if(whatMove(b,lat_two_hor_left_up_down,current_player) != LAT_2_HOR||\
    whatMove(b,lat_two_hor_left_down_up,current_player) != LAT_2_HOR||\
    whatMove(b,lat_two_hor_right_up_down,current_player) != LAT_2_HOR||\
    whatMove(b,lat_two_hor_right_down_up,current_player) != LAT_2_HOR){
        fprintf(stderr, "allMove: whatMove: unrecognized movement : LAT_2_HOR");
    }
}

char testingAllMove(){
    testAbsChar();
    testCheckSuicide();

}
