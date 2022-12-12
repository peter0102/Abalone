//joueurs
//#define current_player 'W'
//#define other_player 'B'
#define EMPTY '0'
//types de mouvement
#define LINE_HOR_RIGHT 'a'
#define LINE_HOR_LEFT 'b'
#define LINE_VER_DOWN 'c'
#define LINE_VER_UP 'd'
#define LAT_2_HOR 'e'
#define LAT_2_VER 'f'
#define LAT_3_VER_X0_DOWN 'g'
#define LAT_3_VER_X0_UP 'h'
#define LAT_3_HOR_Y0_RIGHT 'i'
#define LAT_3_HOR_Y0_LEFT 'j'
//gestion d'erreurs
#define ERROR 'x'
#define SUCCESS 'l'
//définition des types
typedef char Plateau[10][10];
typedef char Move[2][2];
typedef char Triple[2][3]; //x ou y puis x0 1 ou 2
//fonctions

char absChar(char v){
    if(v<0){
        return(-v);
    }
    else{
        return(v);
    }
}

char checkSuicide(Move m){
    if(m[0][1]==0 || m[0][1]==9 || m[1][1]==0 || m[1][1]==9){
        return(ERROR);
    }
    return(SUCCESS);
}

char whatMove(Plateau plat,Move m, char current_player) {
    //déplacement en ligne horizontal
    if (m[0][0] == m[0][1]) {
        //déplacement vers la droite
        if (m[1][0] < m[1][1]) {
            return (LINE_HOR_RIGHT);
        }
        //déplacement vers la gauche
        if (m[1][0] > m[1][1]) {
            return (LINE_HOR_LEFT);
        }
    }
        //déplacement en ligne vertical
    else if (m[1][0] == m[1][1]) {
        //déplacement vers le bas
        if (m[0][0] < m[0][1]) {
            return (LINE_VER_DOWN);
        }
        //déplacement vers le haut
        if (m[0][0] > m[0][1]) {
            return (LINE_VER_UP);
        }
    }
        //déplacement latéral de taille 2
    else if ((absChar(m[0][0] - m[0][1]) + absChar(m[1][0] - m[1][1])) == 2) {
        //déplacement latéral horizontal
        if (plat[m[0][0]][m[1][1]] == current_player) {
            return (LAT_2_HOR);
        }
            //déplacement latéral vertical
        else if (plat[m[0][1]][m[1][0]] == current_player) {
            return (LAT_2_VER);
        }
    }
        //déplacement latéral vertical de taille 3
    else if (absChar(m[0][0] - m[0][1]) == 2 && absChar(m[1][0] - m[1][1]) == 1) {
        //x0 bas & x1 haut
        if (m[0][0] > m[0][1]) {
            return (LAT_3_VER_X0_DOWN);
        }
        //x0 haut & x1 bas
        if (m[0][0] < m[0][1]) {
            return (LAT_3_VER_X0_UP);
        }
    }
        //déplacement latéral horizontal de taille 3
    else if (absChar(m[0][0] - m[0][1]) == 1 && absChar(m[1][0] - m[1][1]) == 2) {
        //y0 droite & y1 gauche
        if (m[1][0] < m[1][1]) {
            return (LAT_3_HOR_Y0_RIGHT);
        }
        //y0 gauche & y1 droite
        if (m[1][0] > m[1][1]) {
            return (LAT_3_HOR_Y0_LEFT);
        }
    }
    return (ERROR);
}

char allies(char type_of_move,Move m){
    if(type_of_move==LINE_HOR_RIGHT || type_of_move==LINE_HOR_LEFT){
        return(absChar(m[1][0] - m[1][1]));
    }
    else if(type_of_move==LINE_VER_UP || type_of_move==LINE_VER_DOWN) {
        return(absChar(m[0][0] - m[0][1]));
    }
    else if(type_of_move==LAT_2_HOR || type_of_move==LAT_2_VER) {
        return(2);
    }
    else if(type_of_move==LAT_3_VER_X0_DOWN || type_of_move==LAT_3_VER_X0_UP ||\
    type_of_move==LAT_3_HOR_Y0_RIGHT || type_of_move==LAT_3_HOR_Y0_LEFT){
        return(3);
    }
    return(ERROR);
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
            case LINE_HOR_RIGHT: {
                coords_allies[0][i] = m[0][0];
                coords_allies[1][i] = m[1][0] + i;
                coords_ennemies[0][i] = m[0][1];
                coords_ennemies[1][i] = m[1][1] + i;
            }
                break;
            case LINE_HOR_LEFT: {
                coords_allies[0][i] = m[0][0];
                coords_allies[1][i] = m[1][0] - i;
                coords_ennemies[0][i] = m[0][1];
                coords_ennemies[1][i] = m[1][1] - i;
            }
                break;
            case LINE_VER_DOWN: {
                coords_allies[0][i] = m[0][0] + i;
                coords_allies[1][i] = m[1][0];
                coords_ennemies[0][i] = m[0][1] + i;
                coords_ennemies[1][i] = m[1][1];
            }
                break;
            case LINE_VER_UP: {
                coords_allies[0][i] = m[0][0] - i;
                coords_allies[1][i] = m[1][0] ;
                coords_ennemies[0][i] = m[0][1] - i;
                coords_ennemies[1][i] = m[1][1];
            }
                break;
            case LAT_2_HOR: {
                coords_allies[0][1] = m[0][0];
                coords_allies[1][1] = m[1][1];
                coords_ennemies[0][1] = m[0][1];
                coords_ennemies[1][1] = m[1][0];
            }
                break;
            case LAT_2_VER: {
                coords_allies[0][1] = m[0][1];
                coords_allies[1][1] = m[1][0];
                coords_ennemies[0][1] = m[0][0];
                coords_ennemies[1][1] = m[1][1];
            }
                break;
            case LAT_3_VER_X0_DOWN: {
                coords_allies[0][i] = m[0][0] - i;
                coords_allies[1][i] = m[1][0];
                coords_ennemies[0][i] = m[0][1] + i;
                coords_ennemies[1][i] = m[1][1];
            }
                break;
            case LAT_3_VER_X0_UP: {
                coords_allies[0][i] = m[0][0] + i;
                coords_allies[1][i] = m[1][0];
                coords_ennemies[0][i] = m[0][1] - i;
                coords_ennemies[1][i] = m[1][1];
            }
                break;
            case LAT_3_HOR_Y0_RIGHT:{
                coords_allies[0][i] = m[0][0];
                coords_allies[1][i] = m[1][0] + i;
                coords_ennemies[0][i] = m[0][1];
                coords_ennemies[1][i] = m[1][1] - i;
            }
                break;
            case LAT_3_HOR_Y0_LEFT:{
                coords_allies[0][i] = m[0][0];
                coords_allies[1][i] = m[1][0] - i;
                coords_ennemies[0][i] = m[0][1];
                coords_ennemies[1][i] = m[1][1] + i;
            }
        }
    }
}

char ennemies(Plateau plat,Triple coords_ennemies,char nb_allies, char current_player){
    char nb_ennemies=0;
    for(char i=0;i<nb_allies;i++) {
        if(plat[coords_ennemies[0][i]][coords_ennemies[1][i]]==current_player){
            return(ERROR);
        }
        else if(plat[coords_ennemies[0][i]][coords_ennemies[1][i]]==EMPTY){
            return(nb_ennemies);
        }
        else{
            nb_ennemies++;
        }
    }
    return(ERROR);
}

char checkColor(Triple coords,char color, char nb_allies, Plateau plat){
    for(char i=0;i<nb_allies;i++) {
        if(plat[coords[0][i]][coords[1][i]]!=color){
            return(ERROR);
        }
    }
    return(SUCCESS);
}

char checkMove(Plateau plat, Move m,char current_player) {
    if(checkSuicide(m)==ERROR){
        return(ERROR);
    }
    char type_of_move = whatMove(plat,m,current_player);
    char nb_allies = allies(type_of_move,m);
    //Initialisation des actifs (alliés + ennemis)
    Triple coords_allies;
    Triple coords_ennemies;
    active(m, type_of_move, nb_allies, coords_allies, coords_ennemies);
    char nb_ennemies = ennemies(plat, coords_ennemies, nb_allies, current_player);
    if(nb_ennemies == ERROR){
        return(ERROR);
    }
    //vérification des couleurs
    if(checkColor(coords_allies,current_player,nb_allies,plat)==ERROR){
        return(ERROR);
    }
    return(SUCCESS);
}

char pierre(Plateau plat, Move m, char current_player){
    if(checkMove(plat,m,current_player)==ERROR){
        if(plat[m[0][1]][m[1][1]]==current_player){
            return(current_player);
        }
        else{
            return(ERROR);
        }
    }
    return(SUCCESS);
}

void moveLine(Plateau plat,Move m,Triple coords_ennemies,char nb_ennemies,char current_player,char other_player){
    //déplacement des alliés
    plat[m[0][0]][m[1][0]] = EMPTY;
    plat[coords_ennemies[0][0]][coords_ennemies[1][0]] = current_player;
    //déplacement des ennemis
    if (nb_ennemies > 0) {
        plat[coords_ennemies[0][nb_ennemies]][coords_ennemies[1][nb_ennemies]] = other_player;
    }
}

void moveLateral(Plateau plat,Triple coords_allies,Triple coords_ennemies, char nb_allies, char current_player){
    for(char i=0;i<nb_allies;i++){
        plat[coords_allies[0][i]][coords_allies[1][i]]=EMPTY;
        plat[coords_ennemies[0][i]][coords_ennemies[1][i]]=current_player;
    }
}

void move(Plateau plat,Move m,Triple coords_ennemies,char nb_ennemies,char type_of_move,Triple coords_allies,\
char nb_allies,char current_player, char other_player){
    //déplacement en ligne
    if(type_of_move == LINE_VER_DOWN || type_of_move == LINE_VER_UP ||\
    type_of_move== LINE_HOR_LEFT || type_of_move == LINE_HOR_RIGHT) {
        moveLine(plat,m,coords_ennemies,nb_ennemies,current_player,other_player);
    }
        //déplacement latéral
    else{
        moveLateral(plat,coords_allies,coords_ennemies,nb_allies, current_player);
    }
}

char allMove(Plateau plat,Move m,char current_player,char other_player){
    if(checkSuicide(m)==ERROR){
        return(ERROR);
    }
    char type_of_move = whatMove(plat,m,current_player);
    char nb_allies = allies(type_of_move,m);
    if(nb_allies == ERROR){ //si le type de mouvement est ERROR nb_allies renvoie ERROR
        return(ERROR);
    }
    Triple coords_allies;
    Triple coords_ennemies;
    active(m, type_of_move, nb_allies, coords_allies, coords_ennemies);
    char nb_ennemies = ennemies(plat,coords_ennemies,nb_allies, current_player);
    char good_color = checkColor(coords_allies,current_player,nb_allies,plat);
    if(nb_ennemies == ERROR || good_color == ERROR){
        return(ERROR);
    }
    move(plat,m,coords_ennemies,nb_ennemies,type_of_move,coords_allies,nb_allies,current_player,other_player);
    return(SUCCESS);
}
