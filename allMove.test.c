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
        fprintf(stderr, "allMove: absChar: expecting %d while got %d\n", a_expected, a_actual);
    }
    if(b_actual != b_expected){
        fprintf(stderr, "allMove: absChar: expecting %d while got %d\n", b_expected, b_actual);
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
        fprintf(stderr, "allMove: checkSuicide: a suicide has been authorized\n");
    }
    if(checkSuicide(e)==ERROR){
        fprintf(stderr, "allMove: checkSuicide: authorized move has been considered suicide\n");
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
            {EMPTY, EMPTY, WHITE, EMPTY, WHITE, EMPTY, EMPTY, WHITE, WHITE, EMPTY},
            {EMPTY, EMPTY, WHITE, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WHITE, WHITE, WHITE, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
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
        fprintf(stderr, "allMove: whatMove: unrecognized movement : LINE_HOR_RIGHT\n");
    }

    //En ligne horizontal à gauche
    Move line_hor_left_one = {{1,1},{2,1}}; //taille 1
    Move line_hor_left_two = {{1,1},{3,1}}; //taille 2
    Move line_hor_left_three = {{1,1},{4,1}}; //taille 3
    if(whatMove(b,line_hor_left_one,current_player) != LINE_HOR_LEFT||\
    whatMove(b,line_hor_left_two,current_player) != LINE_HOR_LEFT||\
    whatMove(b,line_hor_left_three,current_player) != LINE_HOR_LEFT){
        fprintf(stderr, "allMove: whatMove: unrecognized movement : LINE_HOR_LEFT\n");
    }

    //En ligne vertical vers le bas
    Move line_ver_down_one = {{5,6},{2,2}}; //taille 1
    Move line_ver_down_two = {{4,6},{2,2}}; //taille 2
    Move line_ver_down_three = {{3,6},{2,2}}; //taille 3
    if(whatMove(b,line_ver_down_one,current_player) != LINE_VER_DOWN||\
    whatMove(b,line_ver_down_two,current_player) != LINE_VER_DOWN||\
    whatMove(b,line_ver_down_three,current_player) != LINE_VER_DOWN){
        fprintf(stderr, "allMove: whatMove: unrecognized movement : LINE_VER_DOWN\n");
    }

    //En ligne vertical vers le haut
    Move line_ver_up_one = {{3,2},{2,2}}; //taille 1
    Move line_ver_up_two = {{4,2},{2,2}}; //taille 2
    Move line_ver_up_three = {{5,2},{2,2}}; //taille 3
    if(whatMove(b,line_ver_up_one,current_player) != LINE_VER_UP||\
    whatMove(b,line_ver_up_two,current_player) != LINE_VER_UP||\
    whatMove(b,line_ver_up_three,current_player) != LINE_VER_UP){
        fprintf(stderr, "allMove: whatMove: unrecognized movement : LINE_VER_UP\n");
    }

    //Latéral taille 2 horizontal
    Move lat_two_hor_up_right_left = {{4,3},{8,7}}; //à gauche commençant en haut finissant en bas
    Move lat_two_hor_up_left_right = {{4,3},{7,8}}; //à gauche commençant en bas finissant en haut
    Move lat_two_hor_down_right_left = {{4,5},{8,7}}; //à droite commençant en haut finissant en bas
    Move lat_two_hor_down_left_right = {{4,5},{7,8}}; //à droite commençant en bas finissant en haut
    if(whatMove(b,lat_two_hor_up_right_left,current_player) != LAT_2_HOR||\
    whatMove(b,lat_two_hor_up_left_right,current_player) != LAT_2_HOR||\
    whatMove(b,lat_two_hor_down_right_left,current_player) != LAT_2_HOR||\
    whatMove(b,lat_two_hor_down_left_right,current_player) != LAT_2_HOR){
        fprintf(stderr, "allMove: whatMove: unrecognized movement : LAT_2_HOR\n");
    }

    //Latéral taille 2 vertical
    Move lat_two_ver_left_up_down = {{3,4},{4,3}}; //à gauche commençant en haut finissant en bas
    Move lat_two_ver_left_down_up = {{4,3},{4,3}}; //à gauche commençant en bas finissant en haut
    Move lat_two_ver_right_up_down = {{3,4},{4,5}}; //à droite commençant en haut finissant en bas
    Move lat_two_ver_right_down_up = {{4,3},{4,5}}; //à droite commençant en bas finissant en haut
    if(whatMove(b,lat_two_ver_left_up_down,current_player) != LAT_2_VER||\
    whatMove(b,lat_two_ver_left_down_up,current_player) != LAT_2_VER||\
    whatMove(b,lat_two_ver_right_up_down,current_player) != LAT_2_VER||\
    whatMove(b,lat_two_ver_right_down_up,current_player) != LAT_2_VER){
        fprintf(stderr, "allMove: whatMove: unrecognized movement : LAT_2_VER\n");
    }

    //Latéral taille 3 vertical x0 en bas
    Move lat_three_ver_x0_down_right = {{5,3},{2,1}};
    Move lat_three_ver_x0_down_left = {{5,3},{2,3}};
    if(whatMove(b,lat_two_ver_left_up_down,current_player) != LAT_3_VER_X0_DOWN||\
    whatMove(b,lat_two_ver_left_down_up,current_player) != LAT_3_VER_X0_DOWN){
        fprintf(stderr, "allMove: whatMove: unrecognized movement : LAT_3_VER_X0_DOWN\n");
    }

    //Latéral taille 3 vertical x0 en haut
    Move lat_three_ver_x0_up_right = {{3,5},{2,1}};
    Move lat_three_ver_x0_up_left = {{3,5},{2,3}};
    if(whatMove(b,lat_three_ver_x0_up_right,current_player) != LAT_3_VER_X0_DOWN||\
    whatMove(b,lat_three_ver_x0_up_left,current_player) != LAT_3_VER_X0_DOWN){
        fprintf(stderr, "allMove: whatMove: unrecognized movement : LAT_3_VER_X0_DOWN\n");
    }

    //Latéral taille 3 horizontal y0 à droite
    Move lat_three_hor_y0_right_up = {{7,6},{7,5}};
    Move lat_three_hor_y0_right_down = {{7,8},{7,5}};
    if(whatMove(b,lat_three_hor_y0_right_up,current_player) != LAT_3_HOR_Y0_RIGHT||\
    whatMove(b,lat_three_hor_y0_right_down,current_player) != LAT_3_HOR_Y0_RIGHT){
        fprintf(stderr, "allMove: whatMove: unrecognized movement : LAT_3_HOR_Y0_RIGHT\n");
    }

    //Latéral taille 3 horizontal y0 à gauche
    Move lat_three_hor_y0_left_up = {{7,6},{5,7}};
    Move lat_three_hor_y0_left_down = {{7,8},{5,7}};
    if(whatMove(b,lat_three_hor_y0_left_up,current_player) != LAT_3_HOR_Y0_LEFT||\
    whatMove(b,lat_three_hor_y0_left_down,current_player) != LAT_3_HOR_Y0_LEFT){
        fprintf(stderr, "allMove: whatMove: unrecognized movement : LAT_3_HOR_Y0_RIGHT\n");
    }
}

void testAllies(){
    //test de allies : char allies(char type_of_move,Move m)

    //En ligne horizontal à droite
    Move line_hor_right_one = {{1,1},{7,8}}; //taille 1
    Move line_hor_right_two = {{1,1},{6,8}}; //taille 2
    Move line_hor_right_three = {{1,1},{5,8}}; //taille 3
    if(allies(LINE_HOR_RIGHT,line_hor_right_one) != 1||allies(LINE_HOR_RIGHT,line_hor_right_two) != 2||\
    allies(LINE_HOR_RIGHT,line_hor_right_three) != 3){
        fprintf(stderr, "allMove: allies: did not count well the allies for the movement : LINE_HOR_RIGHT\n");
    }

    //En ligne horizontal à gauche
    Move line_hor_left_one = {{1,1},{2,1}}; //taille 1
    Move line_hor_left_two = {{1,1},{3,1}}; //taille 2
    Move line_hor_left_three = {{1,1},{4,1}}; //taille 3
    if(allies(LINE_HOR_LEFT,line_hor_left_one) != 1||allies(LINE_HOR_LEFT,line_hor_left_two) != 2||\
    allies(LINE_HOR_LEFT,line_hor_left_three) != 3) {
        fprintf(stderr, "allMove: allies: did not count well the allies for the movement : LINE_HOR_LEFT\n");
    }

    //En ligne vertical vers le bas
    Move line_ver_down_one = {{5,6},{2,2}}; //taille 1
    Move line_ver_down_two = {{4,6},{2,2}}; //taille 2
    Move line_ver_down_three = {{3,6},{2,2}}; //taille 3
    if(allies(LINE_VER_DOWN,line_ver_down_one) != 1||allies(LINE_VER_DOWN,line_ver_down_two) != 2||\
    allies(LINE_VER_DOWN,line_ver_down_three) != 3) {
        fprintf(stderr, "allMove: allies: did not count well the allies for the movement : LINE_VER_DOWN\n");
    }

    //En ligne vertical vers le haut
    Move line_ver_up_one = {{3,2},{2,2}}; //taille 1
    Move line_ver_up_two = {{4,2},{2,2}}; //taille 2
    Move line_ver_up_three = {{5,2},{2,2}}; //taille 3
    if(allies(LINE_VER_UP,line_ver_up_one) != 1||allies(LINE_VER_UP,line_ver_up_two) != 2||\
    allies(LINE_VER_UP,line_ver_up_three) != 3) {
        fprintf(stderr, "allMove: allies: did not count well the allies for the movement : LINE_VER_UP\n");
    }

    //Latéral taille 2 horizontal
    Move lat_two_hor_up_right_left = {{4,3},{8,7}}; //à gauche commençant en haut finissant en bas
    if(allies(LAT_2_HOR,lat_two_hor_up_right_left) != 2){
        fprintf(stderr, "allMove: allies: did not count well the allies for the movement : LAT_2_HOR\n");
    }

    //Latéral taille 2 vertical
    Move lat_two_ver_left_up_down = {{3,4},{4,3}}; //à gauche commençant en haut finissant en bas
    if(allies(LAT_2_VER,lat_two_ver_left_up_down) != 2){
        fprintf(stderr, "allMove: allies: did not count well the allies for the movement : LAT_2_VER\n");
    }

    //Latéral taille 3 vertical x0 en bas
    Move lat_three_ver_x0_down_right = {{5,3},{2,1}};
    if(allies(LAT_3_VER_X0_DOWN,lat_three_ver_x0_down_right) != 3){
        fprintf(stderr, "allMove: allies: did not count well the allies for the movement : LAT_3_VER_X0_DOWN\n");
    }

    //Latéral taille 3 vertical x0 en haut
    Move lat_three_ver_x0_up_right = {{3,5},{2,1}};
    if(allies(LAT_3_VER_X0_UP,lat_three_ver_x0_up_right) != 3){
        fprintf(stderr, "allMove: allies: did not count well the allies for the movement : LAT_3_VER_X0_UP");
    }

    //Latéral taille 3 horizontal y0 à droite
    Move lat_three_hor_y0_right_up = {{7,6},{7,5}};
    if(allies(LAT_3_HOR_Y0_RIGHT,lat_three_hor_y0_right_up) != 3){
        fprintf(stderr, "allMove: allies: did not count well the allies for the movement : LAT_3_HOR_Y0_RIGHT");
    }

    //Latéral taille 3 horizontal y0 à gauche
    Move lat_three_hor_y0_left_up = {{7,6},{5,7}};
    if(allies(LAT_3_HOR_Y0_LEFT,lat_three_hor_y0_left_up) != 3){
        fprintf(stderr, "allMove: allies: did not count well the allies for the movement : LAT_3_HOR_Y0_LEFT\n");
    }
}

void testActive(){
    //test de la fonction active : active(Move m,char type_of_move,char nb_allies,Triple coords_allies,Triple coords_ennemies)

    Triple coords_allies;
    Triple coords_ennemies;

    //En ligne horizontal à droite
    Move line_hor_right_one = {{1,1},{7,8}}; //taille 1
    Move line_hor_right_two = {{1,1},{6,8}}; //taille 2
    Move line_hor_right_three = {{1,1},{5,8}}; //taille 3

    active(line_hor_right_one,LINE_HOR_RIGHT,1,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 1 ||coords_allies[1][0] != 7||\
    coords_ennemies[0][0] != 1 ||coords_ennemies[1][0] != 8){
        fprintf(stderr, "allMove: active: wrong coordinates : LINE_HOR_RIGHT size 1\n");
    }
    active(line_hor_right_two,LINE_HOR_RIGHT,2,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 1 ||coords_allies[1][0] != 6||coords_allies[0][1] != 1||coords_allies[1][1] != 7||\
    coords_ennemies[0][0] != 1 ||coords_ennemies[1][0] != 8||coords_ennemies[0][1] != 1 ||coords_ennemies[1][1] != 9){
        fprintf(stderr, "allMove: active: wrong coordinates : LINE_HOR_RIGHT size 2\n");
    }
    active(line_hor_right_three,LINE_HOR_RIGHT,3,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 1 ||coords_allies[1][0] != 6||coords_allies[0][1] != 1||coords_allies[1][1] != 7||\
    coords_allies[0][2] != 1||coords_allies[1][2] != 8||\
    coords_ennemies[0][0] != 1 ||coords_ennemies[1][0] != 8||coords_ennemies[0][1] != 1 ||coords_ennemies[1][1] != 9||\
    coords_ennemies[0][2] != 1 ||coords_ennemies[1][2] != 10){
        fprintf(stderr, "allMove: active: wrong coordinates : LINE_HOR_RIGHT size 3\n");
    }

    //En ligne horizontal à gauche
    Move line_hor_left_one = {{1,1},{2,1}}; //taille 1
    Move line_hor_left_two = {{1,1},{3,1}}; //taille 2
    Move line_hor_left_three = {{1,1},{4,1}}; //taille 3
    active(line_hor_left_one,LINE_HOR_LEFT,1,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 1 ||coords_allies[1][0] != 2||\
    coords_ennemies[0][0] != 1 ||coords_ennemies[1][0] != 1){
        fprintf(stderr, "allMove: active: wrong coordinates : LINE_HOR_LEFT size 1\n");
    }
    active(line_hor_left_two,LINE_HOR_LEFT,2,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 1 ||coords_allies[1][0] != 3||coords_allies[0][1] != 1||coords_allies[1][1] != 2||\
    coords_ennemies[0][0] != 1 ||coords_ennemies[1][0] != 1||coords_ennemies[0][1] != 1 ||coords_ennemies[1][1] != 0){
        fprintf(stderr, "allMove: active: wrong coordinates : LINE_HOR_LEFT size 2\n");
    }
    active(line_hor_left_three,LINE_HOR_LEFT,3,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 1 ||coords_allies[1][0] != 3||coords_allies[0][1] != 1||coords_allies[1][1] != 2||\
    coords_allies[0][2] != 1||coords_allies[1][2] != 1||\
    coords_ennemies[0][0] != 1 ||coords_ennemies[1][0] != 1||coords_ennemies[0][1] != 1 ||coords_ennemies[1][1] != 0||\
    coords_ennemies[0][2] != 1 ||coords_ennemies[1][2] != -1){
        fprintf(stderr, "allMove: active: wrong coordinates : LINE_HOR_LEFT size 3\n");
    }

    //En ligne vertical vers le bas
    Move line_ver_down_one = {{5,6},{2,2}}; //taille 1
    Move line_ver_down_two = {{4,6},{2,2}}; //taille 2
    Move line_ver_down_three = {{3,6},{2,2}}; //taille 3
    active(line_hor_left_one,LINE_VER_DOWN,1,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 5 ||coords_allies[1][0] != 2||\
    coords_ennemies[0][0] != 6 ||coords_ennemies[1][0] != 2){
        fprintf(stderr, "allMove: active: wrong coordinates : LINE_VER_DOWN size 1\n");
    }
    active(line_hor_left_two,LINE_VER_DOWN,2,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 4 ||coords_allies[1][0] != 2||coords_allies[0][1] != 5||coords_allies[1][1] != 2||\
    coords_ennemies[0][0] != 6 ||coords_ennemies[1][0] != 2||coords_ennemies[0][1] != 7 ||coords_ennemies[1][1] != 2){
        fprintf(stderr, "allMove: active: wrong coordinates : LINE_VER_DOWN size 2\n");
    }
    active(line_hor_left_three,LINE_VER_DOWN,3,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 3 ||coords_allies[1][0] != 2||coords_allies[0][1] != 4||coords_allies[1][1] != 2||\
    coords_allies[0][2] != 5||coords_allies[1][2] != 2||\
    coords_ennemies[0][0] != 6 ||coords_ennemies[1][0] != 2||coords_ennemies[0][1] != 7 ||coords_ennemies[1][1] != 2||\
    coords_ennemies[0][2] != 8 ||coords_ennemies[1][2] != 2){
        fprintf(stderr, "allMove: active: wrong coordinates : LINE_VER_DOWN size 3\n");
    }

    //En ligne vertical vers le haut
    Move line_ver_up_one = {{3,2},{2,2}}; //taille 1
    Move line_ver_up_two = {{4,2},{2,2}}; //taille 2
    Move line_ver_up_three = {{5,2},{2,2}}; //taille 3
    active(line_hor_left_one,LINE_VER_UP,1,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 3 ||coords_allies[1][0] != 2||\
    coords_ennemies[0][0] != 2 ||coords_ennemies[1][0] != 2){
        fprintf(stderr, "allMove: active: wrong coordinates : LINE_VER_UP size 1\n");
    }
    active(line_hor_left_two,LINE_VER_UP,2,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 4 ||coords_allies[1][0] != 2||coords_allies[0][1] != 3||coords_allies[1][1] != 2||\
    coords_ennemies[0][0] != 2 ||coords_ennemies[1][0] != 2||coords_ennemies[0][1] != 1 ||coords_ennemies[1][1] != 2){
        fprintf(stderr, "allMove: active: wrong coordinates : LINE_VER_UP size 2\n");
    }
    active(line_hor_left_three,LINE_VER_UP,3,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 5 ||coords_allies[1][0] != 2||coords_allies[0][1] != 4||coords_allies[1][1] != 2||\
    coords_allies[0][2] != 3||coords_allies[1][2] != 2||\
    coords_ennemies[0][0] != 2 ||coords_ennemies[1][0] != 2||coords_ennemies[0][1] != 1 ||coords_ennemies[1][1] != 2||\
    coords_ennemies[0][2] != 0 ||coords_ennemies[1][2] != 2){
        fprintf(stderr, "allMove: active: wrong coordinates : LINE_VER_UP size 3\n");
    }

    //Latéral taille 2 horizontal
    Move lat_two_hor_up_right_left = {{4,3},{8,7}}; //à gauche commençant en haut finissant en bas
    Move lat_two_hor_down_left_right = {{4,5},{7,8}}; //à droite commençant en bas finissant en haut
    active(lat_two_hor_up_right_left,LAT_2_HOR,2,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 4 ||coords_allies[1][0] != 2||coords_allies[0][1] != 3||coords_allies[1][1] != 2||\
    coords_ennemies[0][0] != 2 ||coords_ennemies[1][0] != 2||coords_ennemies[0][1] != 1 ||coords_ennemies[1][1] != 2){
        fprintf(stderr, "allMove: active: wrong coordinates : LAT_2_HOR size 2\n");
    }
    active(lat_two_hor_down_left_right,LINE_VER_UP,2,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 4 ||coords_allies[1][0] != 2||coords_allies[0][1] != 3||coords_allies[1][1] != 2||\
    coords_ennemies[0][0] != 2 ||coords_ennemies[1][0] != 2||coords_ennemies[0][1] != 1 ||coords_ennemies[1][1] != 2){
        fprintf(stderr, "allMove: active: wrong coordinates : LAT_2_HOR size 2\n");
    }

    //Latéral taille 2 vertical
    Move lat_two_ver_left_up_down = {{3,4},{4,3}}; //à gauche commençant en haut finissant en bas
    Move lat_two_ver_left_down_up = {{4,3},{4,3}}; //à gauche commençant en bas finissant en haut
    Move lat_two_ver_right_up_down = {{3,4},{4,5}}; //à droite commençant en haut finissant en bas
    Move lat_two_ver_right_down_up = {{4,3},{4,5}}; //à droite commençant en bas finissant en haut
    if(whatMove(b,lat_two_ver_left_up_down,current_player) != LAT_2_VER||\
    whatMove(b,lat_two_ver_left_down_up,current_player) != LAT_2_VER||\
    whatMove(b,lat_two_ver_right_up_down,current_player) != LAT_2_VER||\
    whatMove(b,lat_two_ver_right_down_up,current_player) != LAT_2_VER){
        fprintf(stderr, "allMove: whatMove: unrecognized movement : LAT_2_VER");
    }

    //Latéral taille 3 vertical x0 en bas
    Move lat_three_ver_x0_down_right = {{5,3},{2,1}};
    Move lat_three_ver_x0_down_left = {{5,3},{2,3}};
    if(whatMove(b,lat_two_ver_left_up_down,current_player) != LAT_3_VER_X0_DOWN||\
    whatMove(b,lat_two_ver_left_down_up,current_player) != LAT_3_VER_X0_DOWN){
        fprintf(stderr, "allMove: whatMove: unrecognized movement : LAT_3_VER_X0_DOWN");
    }

    //Latéral taille 3 vertical x0 en haut
    Move lat_three_ver_x0_up_right = {{3,5},{2,1}};
    Move lat_three_ver_x0_up_left = {{3,5},{2,3}};
    if(whatMove(b,lat_three_ver_x0_up_right,current_player) != LAT_3_VER_X0_DOWN||\
    whatMove(b,lat_three_ver_x0_up_left,current_player) != LAT_3_VER_X0_DOWN){
        fprintf(stderr, "allMove: whatMove: unrecognized movement : LAT_3_VER_X0_DOWN");
    }

    //Latéral taille 3 horizontal y0 à droite
    Move lat_three_hor_y0_right_up = {{7,6},{7,5}};
    Move lat_three_hor_y0_right_down = {{7,8},{7,5}};
    if(whatMove(b,lat_three_hor_y0_right_up,current_player) != LAT_3_HOR_Y0_RIGHT||\
    whatMove(b,lat_three_hor_y0_right_down,current_player) != LAT_3_HOR_Y0_RIGHT){
        fprintf(stderr, "allMove: whatMove: unrecognized movement : LAT_3_HOR_Y0_RIGHT");
    }

    //Latéral taille 3 horizontal y0 à gauche
    Move lat_three_hor_y0_left_up = {{7,6},{5,7}};
    Move lat_three_hor_y0_left_down = {{7,8},{5,7}};
    if(whatMove(b,lat_three_hor_y0_left_up,current_player) != LAT_3_HOR_Y0_LEFT||\
    whatMove(b,lat_three_hor_y0_left_down,current_player) != LAT_3_HOR_Y0_LEFT){
        fprintf(stderr, "allMove: whatMove: unrecognized movement : LAT_3_HOR_Y0_RIGHT");
    }
}

char testingAllMove(){
    testAbsChar();
    testCheckSuicide();
    testWhatMove();
    testAllies();
}