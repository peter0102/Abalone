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

/*
 * Liste de mouvements à tester
 * LINE_HOR_RIGHT
 * LINE_HOR_LEFT
 * LINE_VER_DOWN
 * LINE_VER_UP
 * LAT_2_HOR
 * LAT_2_VER
 * LAT_3_VER_X0_DOWN
 * LAT_3_VER_X0_UP
 * LAT_3_HOR_Y0_RIGHT
 * LAT_3_HOR_Y0_LEFT
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
    if(coords_allies[0][0] != 4 ||coords_allies[1][0] != 8||coords_allies[0][1] != 4||coords_allies[1][1] != 7||\
    coords_ennemies[0][0] != 3 ||coords_ennemies[1][0] != 7||coords_ennemies[0][1] != 3 ||coords_ennemies[1][1] != 8){
        fprintf(stderr, "allMove: active: wrong coordinates : LAT_2_HOR size 2\n");
    }
    active(lat_two_hor_down_left_right,LAT_2_HOR,2,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 4 ||coords_allies[1][0] != 8||coords_allies[0][1] != 4||coords_allies[1][1] != 7||\
    coords_ennemies[0][0] != 2 ||coords_ennemies[1][0] != 2||coords_ennemies[0][1] != 1 ||coords_ennemies[1][1] != 2){
        fprintf(stderr, "allMove: active: wrong coordinates : LAT_2_HOR size 2\n");
    }

    //Latéral taille 2 vertical
    Move lat_two_ver_left_up_down = {{3,4},{4,3}}; //à gauche commençant en haut finissant en bas
    Move lat_two_ver_right_down_up = {{4,3},{4,5}}; //à droite commençant en bas finissant en haut
    active(lat_two_ver_left_up_down,LAT_2_VER,2,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 3 ||coords_allies[1][0] != 4||coords_allies[0][1] != 4||coords_allies[1][1] != 4||\
    coords_ennemies[0][0] != 4 ||coords_ennemies[1][0] != 3||coords_ennemies[0][1] != 3 ||coords_ennemies[1][1] != 3){
        fprintf(stderr, "allMove: active: wrong coordinates : LAT_2_VER size 2\n");
    }
    active(lat_two_ver_right_down_up,LAT_2_VER,2,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 4 ||coords_allies[1][0] != 3||coords_allies[0][1] != 4||coords_allies[1][1] != 4||\
    coords_ennemies[0][0] != 3 ||coords_ennemies[1][0] != 4||coords_ennemies[0][1] !=5 ||coords_ennemies[1][1] != 5){
        fprintf(stderr, "allMove: active: wrong coordinates : LAT_2_VER size 2\n");
    }

    //Latéral taille 3 vertical x0 en bas
    Move lat_three_ver_x0_down_right = {{5,3},{2,1}};
    Move lat_three_ver_x0_down_left = {{5,3},{2,3}};
    active(lat_three_ver_x0_down_right,LAT_3_VER_X0_DOWN,2,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 5||coords_allies[1][0] != 2||coords_allies[0][1] != 4||coords_allies[1][1] != 2||\
    coords_allies[0][2] != 3||coords_allies[1][2] != 2||\
    coords_ennemies[0][0] != 3 ||coords_ennemies[1][0] != 1||coords_ennemies[0][1] != 4 ||coords_ennemies[1][1] != 1||\
    coords_ennemies[0][2] != 5 ||coords_ennemies[1][2] != 1){
        fprintf(stderr, "allMove: active: wrong coordinates : LAT_3_VER_X0_DOWN size 2\n");
    }
    active(lat_three_ver_x0_down_left,LAT_3_VER_X0_DOWN,2,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 5||coords_allies[1][0] != 2||coords_allies[0][1] != 4||coords_allies[1][1] != 2||\
    coords_allies[0][2] != 3||coords_allies[1][2] != 2||\
    coords_ennemies[0][0] != 3 ||coords_ennemies[1][0] != 3||coords_ennemies[0][1] != 4 ||coords_ennemies[1][1] != 3||\
    coords_ennemies[0][2] != 5 ||coords_ennemies[1][2] != 3){
        fprintf(stderr, "allMove: active: wrong coordinates : LAT_3_VER_X0_DOWN size 2\n");
    }


    //Latéral taille 3 vertical x0 en haut
    Move lat_three_ver_x0_up_right = {{3,5},{2,1}};
    Move lat_three_ver_x0_up_left = {{3,5},{2,3}};
    active(lat_three_ver_x0_down_right,LAT_3_VER_X0_UP,2,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 3||coords_allies[1][0] != 2||coords_allies[0][1] != 4||coords_allies[1][1] != 2||\
    coords_allies[0][2] != 5||coords_allies[1][2] != 2||\
    coords_ennemies[0][0] != 5 ||coords_ennemies[1][0] != 1||coords_ennemies[0][1] != 4 ||coords_ennemies[1][1] != 1||\
    coords_ennemies[0][2] != 3 ||coords_ennemies[1][2] != 1){
        fprintf(stderr, "allMove: active: wrong coordinates : LAT_3_VER_X0_UP size 2\n");
    }
    active(lat_three_ver_x0_down_left,LAT_3_VER_X0_UP,2,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 3||coords_allies[1][0] != 2||coords_allies[0][1] != 4||coords_allies[1][1] != 2||\
    coords_allies[0][2] != 5||coords_allies[1][2] != 2||\
    coords_ennemies[0][0] != 5 ||coords_ennemies[1][0] != 3||coords_ennemies[0][1] != 4 ||coords_ennemies[1][1] != 3||\
    coords_ennemies[0][2] != 3 ||coords_ennemies[1][2] != 3){
        fprintf(stderr, "allMove: active: wrong coordinates : LAT_3_VER_X0_UP size 2\n");
    }

    //Latéral taille 3 horizontal y0 à droite
    Move lat_three_hor_y0_right_up = {{7,6},{7,5}};
    Move lat_three_hor_y0_right_down = {{7,8},{7,5}};
    active(lat_three_hor_y0_right_up,LAT_3_HOR_Y0_RIGHT,2,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 7||coords_allies[1][0] != 7||coords_allies[0][1] != 7||coords_allies[1][1] != 6||\
    coords_allies[0][2] != 7||coords_allies[1][2] != 5||\
    coords_ennemies[0][0] != 6 ||coords_ennemies[1][0] != 5||coords_ennemies[0][1] != 6 ||coords_ennemies[1][1] != 6||\
    coords_ennemies[0][2] != 6 ||coords_ennemies[1][2] != 7){
        fprintf(stderr, "allMove: active: wrong coordinates : LAT_3_HOR_Y0_RIGHT size 2\n");
    }
    active(lat_three_hor_y0_right_down,LAT_3_HOR_Y0_RIGHT,2,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 7||coords_allies[1][0] != 7||coords_allies[0][1] != 7||coords_allies[1][1] != 6||\
    coords_allies[0][2] != 7||coords_allies[1][2] != 5||\
    coords_ennemies[0][0] != 8 ||coords_ennemies[1][0] != 5||coords_ennemies[0][1] != 8 ||coords_ennemies[1][1] != 6||\
    coords_ennemies[0][2] != 8 ||coords_ennemies[1][2] != 7){
        fprintf(stderr, "allMove: active: wrong coordinates : LAT_3_HOR_Y0_RIGHT size 2\n");
    }

    //Latéral taille 3 horizontal y0 à gauche
    Move lat_three_hor_y0_left_up = {{7,6},{5,7}};
    Move lat_three_hor_y0_left_down = {{7,8},{5,7}};
    active(lat_three_hor_y0_left_up,LAT_3_HOR_Y0_LEFT,2,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 7||coords_allies[1][0] != 5||coords_allies[0][1] != 7||coords_allies[1][1] != 6||\
    coords_allies[0][2] != 7||coords_allies[1][2] != 7||\
    coords_ennemies[0][0] != 6 ||coords_ennemies[1][0] != 7||coords_ennemies[0][1] != 6 ||coords_ennemies[1][1] != 6||\
    coords_ennemies[0][2] != 6 ||coords_ennemies[1][2] != 5){
        fprintf(stderr, "allMove: active: wrong coordinates : LAT_3_HOR_Y0_LEFT size 2\n");
    }
    active(lat_three_hor_y0_left_down,LAT_3_HOR_Y0_LEFT,2,coords_allies,coords_ennemies);
    if(coords_allies[0][0] != 7||coords_allies[1][0] != 5||coords_allies[0][1] != 7||coords_allies[1][1] != 6||\
    coords_allies[0][2] != 7||coords_allies[1][2] != 7||\
    coords_ennemies[0][0] != 8 ||coords_ennemies[1][0] != 7||coords_ennemies[0][1] != 8 ||coords_ennemies[1][1] != 6||\
    coords_ennemies[0][2] != 8 ||coords_ennemies[1][2] != 5){
        fprintf(stderr, "allMove: active: wrong coordinates : LAT_3_HOR_Y0_LEFT size 2\n");
    }
}

void testEnnemies(){
    //test de ennemies donc ennemiesLine et ennemiesLat
    Board a = {
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, BLACK, BLACK, BLACK, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}, //cas 1.1 & cas 2.1
            {EMPTY, BLACK, BLACK, BLACK, EMPTY, EMPTY, WHITE, EMPTY, EMPTY, EMPTY},
            {EMPTY, BLACK, BLACK, BLACK, EMPTY, EMPTY, BLACK, EMPTY, EMPTY, EMPTY},
            {EMPTY, BLACK, BLACK, BLACK, EMPTY, WHITE, EMPTY, EMPTY, EMPTY, EMPTY}, //cas 2.2
            {EMPTY, BLACK, BLACK, BLACK, EMPTY, WHITE, WHITE, EMPTY, EMPTY, EMPTY},
            {EMPTY, BLACK, BLACK, BLACK, EMPTY, WHITE, BLACK, EMPTY, EMPTY, EMPTY},
            {EMPTY, BLACK, BLACK, BLACK, EMPTY, BLACK, EMPTY, EMPTY, EMPTY, EMPTY}, //cas 2.3
            {EMPTY, BLACK, BLACK, BLACK, EMPTY, BLACK, WHITE, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}
    };

    Board b = {
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, BLACK, BLACK, BLACK, EMPTY, BLACK, BLACK, EMPTY, EMPTY, EMPTY},
            {EMPTY, BLACK, BLACK, BLACK, WHITE, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}, //cas 1.2 & cas 2.4
            {EMPTY, BLACK, BLACK, BLACK, WHITE, EMPTY, WHITE, EMPTY, EMPTY, EMPTY},
            {EMPTY, BLACK, BLACK, BLACK, WHITE, EMPTY, BLACK, EMPTY, EMPTY, EMPTY},
            {EMPTY, BLACK, BLACK, BLACK, WHITE, WHITE, EMPTY, EMPTY, EMPTY, EMPTY}, //cas 2.5
            {EMPTY, BLACK, BLACK, BLACK, WHITE, WHITE, WHITE, EMPTY, EMPTY, EMPTY},
            {EMPTY, BLACK, BLACK, BLACK, WHITE, WHITE, BLACK, EMPTY, EMPTY, EMPTY},
            {EMPTY, BLACK, BLACK, BLACK, WHITE, BLACK, EMPTY, EMPTY, EMPTY, EMPTY}, //cas 2.6
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}
    };

    Board c = {
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, BLACK, BLACK, BLACK, WHITE, BLACK, WHITE, EMPTY, EMPTY, EMPTY},
            {EMPTY, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, EMPTY, EMPTY, EMPTY},
            {EMPTY, BLACK, BLACK, BLACK, BLACK, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}, //cas 1.3 & cas 2.7
            {EMPTY, BLACK, BLACK, BLACK, BLACK, EMPTY, WHITE, EMPTY, EMPTY, EMPTY},
            {EMPTY, BLACK, BLACK, BLACK, BLACK, EMPTY, BLACK, EMPTY, EMPTY, EMPTY},
            {EMPTY, BLACK, BLACK, BLACK, BLACK, WHITE, EMPTY, EMPTY, EMPTY, EMPTY}, //cas 2.8
            {EMPTY, BLACK, BLACK, BLACK, BLACK, WHITE, WHITE, EMPTY, EMPTY, EMPTY},
            {EMPTY, BLACK, BLACK, BLACK, BLACK, WHITE, BLACK, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}
    };

    Board d = {
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, BLACK, BLACK, BLACK, BLACK, BLACK, EMPTY, EMPTY, EMPTY, EMPTY}, //cas 2.9
            {EMPTY, BLACK, BLACK, BLACK, BLACK, BLACK, WHITE, EMPTY, EMPTY, EMPTY},
            {EMPTY, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, EMPTY, EMPTY, EMPTY},
            //fin des triples
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}
    };

    //Cas en ligne (39 possibilités (1.3 2.9 3.27)

    Move a_one_one = {{1,1},{3,4}};
    Move b_one_two = {{2,2},{3,4}};
    Move c_one_three = {{3,3},{3,4}};

    Move a_two_one = {{1,1},{2,4}};
    Move a_two_two = {{4,4},{2,4}};
    Move a_two_three = {{7,7},{2,4}};
    Move b_two_four = {{1,2},{2,4}};
    Move b_two_five = {{1,5},{2,4}};
    Move b_two_six = {{1,8},{2,4}};
    Move c_two_seven = {{1,3},{2,4}};
    Move c_two_eight = {{1,6},{2,4}};
    Move d_two_nine = {{1,1},{2,4}};

    Move a_three_one_one = {{1,1},{1,4}};
    Move a_three_one_two = {{2,1},{2,4}};
    Move a_three_one_three= {{3,1},{3,4}};
    Move a_three_one_four = {{4,1},{4,4}};
    Move a_three_one_five = {{5,1},{5,4}};
    Move a_three_one_six = {{6,1},{6,4}};
    Move a_three_one_seven = {{7,1},{7,4}};
    Move a_three_one_eight = {{8,1},{8,4}};
    Move b_three_one_nine = {{1,1},{1,4}};
    Move b_three_two_one = {{2,1},{2,4}};
    Move b_three_two_two = {{3,1},{3,4}};
    Move b_three_two_three = {{4,1},{4,4}};
    Move b_three_two_four = {{5,1},{5,4}};
    Move b_three_two_five = {{6,1},{6,4}};
    Move b_three_two_six = {{7,1},{7,4}};
    Move b_three_two_seven = {{8,1},{8,4}};
    Move c_three_two_eight = {{1,1},{1,4}};
    Move c_three_two_nine = {{2,1},{2,4}};
    Move c_three_three_one = {{3,1},{3,4}};
    Move c_three_three_two = {{4,1},{4,4}};
    Move c_three_three_three = {{5,1},{5,4}};
    Move c_three_three_four = {{6,1},{6,4}};
    Move c_three_three_five = {{7,1},{7,4}};
    Move c_three_three_six = {{8,1},{8,4}};
    Move d_three_three_seven = {{1,1},{1,4}};
    Move d_three_three_eight = {{2,1},{2,4}};
    Move d_three_three_nine = {{3,1},{3,4}};

    Move* moves_line[39] = {&a_one_one,&b_one_two,&c_one_three,
&a_two_one, &a_two_two, &a_two_three, &b_two_four, &b_two_five, &b_two_six, &c_two_seven, &c_two_eight, &d_two_nine,
&a_three_one_one, &a_three_one_two, &a_three_one_three, &a_three_one_four, &a_three_one_five, &a_three_one_six,
&a_three_one_seven, &a_three_one_eight, &b_three_one_nine, &b_three_two_one, &b_three_two_two, &b_three_two_three,
&b_three_two_four, &b_three_two_five, &b_three_two_six, &b_three_two_seven, &c_three_two_eight, &c_three_two_nine,
&c_three_three_one, &c_three_three_two, &c_three_three_three, &c_three_three_four, &c_three_three_five,
&c_three_three_six, &d_three_three_seven, &d_three_three_eight, &d_three_three_nine};

    char nb_ennemies_line[39] = {0,ERROR,ERROR,
 0,0,0,1,ERROR,ERROR,ERROR,ERROR,ERROR,
 0,0,0,0,0,0,0,0,0,
 1,1,1,2,ERROR,ERROR,ERROR,ERROR,ERROR,
ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR};

    Board* ennemies_board[4] = {&a,&b,&c,&d};

    //on suppose que les fonctions précédentes fonctionnent (elles sont testées avant)
    char errors = 0; //max 39
    Triple coords_allies;
    Triple coords_ennemies;
    char current_player = BLACK;
    char nb_allies;
    char type_of_move = LINE_HOR_RIGHT;
    // active(Move m,char type_of_move,char nb_allies,Triple coords_allies,Triple coords_ennemies)
    // allies(char type_of_move,Move m)
    // ennemies(Board board,Triple coords_ennemies,char nb_allies, char current_player, char type_of_move)
    for(int i=0;i<39;i++){
        nb_allies = allies(type_of_move,*moves_line[i]);
        active(*moves_line[i],type_of_move,nb_allies,coords_allies,coords_ennemies);
        if(i<3){ //cas 1
            if(ennemies(*ennemies_board[i],coords_ennemies,nb_allies,current_player,type_of_move != nb_ennemies_line[i])!=nb_ennemies_line[i]){
                errors++;
            }
        }
        else if(i<12){ //cas 2
            if(i==11){
                if(ennemies(d,coords_ennemies,nb_allies,current_player,type_of_move) != nb_ennemies_line[i]){
                    errors++;
                }
            }
            else{
                if(ennemies(*ennemies_board[(i-3)/3],coords_ennemies,nb_allies,current_player,type_of_move != nb_ennemies_line[i])){
                    errors++;
                }
            }
        }
        else{ //cas 3
            if(ennemies(*ennemies_board[(i-12)/8],coords_ennemies,nb_allies,current_player,type_of_move != nb_ennemies_line[i])){
                errors++;
            }
        }
    }

    if(errors!=0){
        fprintf(stderr, "allMove: ennemies: %d errors while processing ennemies in all states of LINE_HOR_RIGHT move\n",errors);
    }
}

char testingAllMove(){
    testAbsChar();
    testCheckSuicide();
    testWhatMove();
    testAllies();
    testActive();
}