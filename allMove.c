//joueurs
#define current_player 'W'
#define other_player 'B'
#define no_player '0'
//types de mouvement
#define line_horizontal_right 'a'
#define line_horizontal_left 'b'
#define line_vertical_down 'c'
#define line_vertical_up 'd'
#define lateral_two_horizontal 'e'
#define lateral_two_vertical 'f'
#define lateral_three_vertical_x0_down 'g'
#define lateral_three_vertical_x0_up 'h'
#define lateral_three_horizontal_y0_right 'i'
#define lateral_three_horizontal_y0_left 'j'
//gestion d'erreurs
#define error 'k'
#define success 'l'
//définition des types
typedef char Plateau[10][10];
typedef char Move[2][2];
typedef char Triple[2][3]; //x ou y puis x0 1 ou 2
//fonctions

char abs_c(char v){
    if(v<0){
        return(-v);
    }
    else{
        return(v);
    }
}

char whatMove(Plateau plat,Move m) {
    //déplacement en ligne horizontal
    if (m[0][0] == m[0][1]) {
        //déplacement vers la droite
        if (m[1][0] < m[1][1]) {
            return (line_horizontal_right);
        }
        //déplacement vers la gauche
        if (m[1][0] > m[1][1]) {
            return (line_horizontal_left);
        }
    }
        //déplacement en ligne vertical
    else if (m[1][0] == m[1][1]) {
        //déplacement vers le bas
        if (m[0][0] < m[0][1]) {
            return (line_vertical_down);
        }
        //déplacement vers le haut
        if (m[0][0] > m[0][1]) {
            return (line_vertical_up);
        }
    }
        //déplacement latéral de taille 2
    else if ((abs_c(m[0][0] - m[0][1]) + abs_c(m[1][0] - m[1][1])) == 2) {
        //déplacement latéral horizontal
        if (plat[m[0][0]][m[1][1]] == current_player) {
            return (lateral_two_horizontal);
        }
            //déplacement latéral vertical
        else if (plat[m[0][1]][m[1][0]] == current_player) {
            return (lateral_two_vertical);
        }
    }
        //déplacement latéral vertical de taille 3
    else if (abs_c(m[0][0] - m[0][1]) == 2 && abs_c(m[1][0] - m[1][1]) == 1) {
        //x0 bas & x1 haut
        if (m[0][0] > m[0][1]) {
            return (lateral_three_vertical_x0_down);
        }
        //x0 haut & x1 bas
        if (m[0][0] < m[0][1]) {
            return (lateral_three_vertical_x0_up);
        }
    }
        //déplacement latéral horizontal de taille 3
    else if (abs_c(m[0][0] - m[0][1]) == 1 && abs_c(m[1][0] - m[1][1]) == 2) {
        //y0 droite & y1 gauche
        if (m[1][0] < m[1][1]) {
            return (lateral_three_horizontal_y0_right);
        }
        //y0 gauche & y1 droite
        if (m[1][0] > m[1][1]) {
            return (lateral_three_horizontal_y0_left);
        }
    }
    return (error);
}

char allies(char type_of_move,Move m){
    if(type_of_move==line_horizontal_right || type_of_move==line_horizontal_left){
        return(abs_c(m[1][0] - m[1][1]));
    }
    else if(type_of_move==line_vertical_up || type_of_move==line_vertical_down) {
        return(abs_c(m[0][0] - m[0][1]));
    }
    else if(type_of_move==lateral_two_horizontal || type_of_move==lateral_two_vertical) {
        return(2);
    }
    else if(type_of_move==lateral_three_vertical_x0_down || type_of_move==lateral_three_vertical_x0_up ||\
    type_of_move==lateral_three_horizontal_y0_right || type_of_move==lateral_three_horizontal_y0_left){
        return(3);
    }
    return(error);
}

void active(Move m,char type_of_move,char nb_allies,Triple coords_allies,Triple coords_ennemies){
    //initialisation alliés
    coords_allies[0][0] = m[0][0];
    coords_allies[1][0] = m[1][0];
    //initialisation ennemis
    coords_ennemies[0][0] = m[0][1];
    coords_ennemies[1][0] = m[1][1];
    //disjonctions de cas
    for(char i = 1;i<nb_allies;i++) {
        switch (type_of_move) {
            case line_horizontal_right: {
                coords_allies[0][i] = m[0][0];
                coords_allies[1][i] = m[1][0] + i;
                coords_ennemies[0][i] = m[0][1];
                coords_ennemies[1][i] = m[1][1] + i;
            }
                break;
            case line_horizontal_left: {
                coords_allies[0][i] = m[0][0];
                coords_allies[1][i] = m[1][0] - i;
                coords_ennemies[0][i] = m[0][1];
                coords_ennemies[1][i] = m[1][1] - i;
            }
                break;
            case line_vertical_down: {
                coords_allies[0][i] = m[0][0] + i;
                coords_allies[1][i] = m[1][0];
                coords_ennemies[0][i] = m[0][1] + i;
                coords_ennemies[1][i] = m[1][1];
            }
                break;
            case line_vertical_up: {
                coords_allies[0][i] = m[0][0] - i;
                coords_allies[1][i] = m[1][0] ;
                coords_ennemies[0][i] = m[0][1] - i;
                coords_ennemies[1][i] = m[1][1];
            }
                break;
            case lateral_two_horizontal: {
                coords_allies[0][1] = m[0][0];
                coords_allies[1][1] = m[1][1];
                coords_ennemies[0][1] = m[0][1];
                coords_ennemies[1][1] = m[1][0];
            }
                break;
            case lateral_two_vertical: {
                coords_allies[0][1] = m[0][1];
                coords_allies[1][1] = m[1][0];
                coords_ennemies[0][1] = m[0][0];
                coords_ennemies[1][1] = m[1][1];
            }
                break;
            case lateral_three_vertical_x0_down: {
                coords_allies[0][i] = m[0][0] - i;
                coords_allies[1][i] = m[1][0];
                coords_ennemies[0][i] = m[0][1] + i;
                coords_ennemies[1][i] = m[1][1];
            }
                break;
            case lateral_three_vertical_x0_up: {
                coords_allies[0][i] = m[0][0] + i;
                coords_allies[1][i] = m[1][0];
                coords_ennemies[0][i] = m[0][1] - i;
                coords_ennemies[1][i] = m[1][1];
            }
                break;
            case lateral_three_horizontal_y0_right:{
                coords_allies[0][i] = m[0][0];
                coords_allies[1][i] = m[1][0] + i;
                coords_ennemies[0][i] = m[0][1];
                coords_ennemies[1][i] = m[1][1] - i;
            }
                break;
            case lateral_three_horizontal_y0_left:{
                coords_allies[0][i] = m[0][0];
                coords_allies[1][i] = m[1][0] - i;
                coords_ennemies[0][i] = m[0][1];
                coords_ennemies[1][i] = m[1][1] + i;
            }
        }
    }
}

char ennemies(Plateau plat,Triple coords_ennemies,char nb_allies){
    char nb_ennemies=0;
    for(char i=0;i<nb_allies;i++) {
        if(plat[coords_ennemies[0][i]][coords_ennemies[1][i]]==current_player){
            return(error);
        }
        else if(plat[coords_ennemies[0][i]][coords_ennemies[1][i]]==no_player){
            return(nb_ennemies);
        }
        else{
            nb_ennemies++;
        }
    }
    return(error);
}

char checkColor(Triple coords,char color, char nb_allies, Plateau plat){
    for(char i=0;i<nb_allies;i++) {
        if(plat[coords[0][i]][coords[1][i]]!=color){
            return(error);
        }
    }
    return(success);
}

char checkMove(Plateau plat, Move m) {
    char type_of_move = whatMove(plat,m);
    char nb_allies = allies(type_of_move,m);
    //Initialisation des actifs (alliés + ennemis)
    Triple coords_allies;
    Triple coords_ennemies;
    active(m, type_of_move, nb_allies, coords_allies, coords_ennemies);
    char nb_ennemies = ennemies(plat, coords_ennemies, nb_allies);
    if(nb_ennemies == error){
        return(error);
    }
    //vérification des couleurs
    if(checkColor(coords_allies,current_player,nb_allies,plat)==error){
        return(error);
    }
    return(success);
}

char pierre(Plateau plat, Move m){
    if(checkMove(plat,m)==error){
        if(plat[m[1][0]][m[1][1]]==current_player){
            return(current_player);
        }
        else{
            return(error);
        }
    }
    return(success);
}

void moveLine(Plateau plat,Move m,Triple coords_ennemies,char nb_ennemies){
    //déplacement des alliés
    plat[m[0][0]][m[1][0]] = no_player;
    plat[coords_ennemies[0][0]][coords_ennemies[1][0]] = current_player;
    //déplacement des ennemis
    if (nb_ennemies > 0) {
        plat[coords_ennemies[0][nb_ennemies]][coords_ennemies[1][nb_ennemies]] = other_player;
    }
}

void moveLateral(Plateau plat,Triple coords_allies,Triple coords_ennemies, char nb_allies){
    for(char i=0;i<nb_allies;i++){
        plat[coords_allies[0][i]][coords_allies[1][i]]=no_player;
        plat[coords_ennemies[0][i]][coords_ennemies[1][i]]=current_player;
    }
}

void move(Plateau plat,Move m,Triple coords_ennemies,char nb_ennemies,char type_of_move,Triple coords_allies, char nb_allies){
    //déplacement en ligne
    if(type_of_move == line_vertical_down || type_of_move == line_vertical_up ||\
    type_of_move== line_horizontal_left || type_of_move == line_horizontal_right) {
        moveLine(plat,m,coords_ennemies,nb_ennemies);
    }
        //déplacement latéral
    else{
        moveLateral(plat,coords_allies,coords_ennemies,nb_allies);
    }
}

char allMove(Plateau plat,Move m){
    char type_of_move = whatMove(plat,m);
    char nb_allies = allies(type_of_move,m);
    if(nb_allies == error){ //si le type de mouvement est error nb_allies renvoie error
        return(error);
    }
    Triple coords_allies;
    Triple coords_ennemies;
    active(m, type_of_move, nb_allies, coords_allies, coords_ennemies);
    char nb_ennemies = ennemies(plat,coords_ennemies,nb_allies);
    char good_color = checkColor(coords_allies,current_player,nb_allies,plat);
    if(nb_ennemies == error || good_color == error){
        return(error);
    }
    move(plat,m,coords_ennemies,nb_ennemies,type_of_move,coords_allies,nb_allies);
    return(success);
}
