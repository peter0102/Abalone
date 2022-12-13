#include <stdio.h>
#include <string.h>
#include "global.h"
#include "init_check.h"

char initialCheck(int argc, char *argv[]) {
    if (argc != 3) { printError();return ERROR; }
    if (strcmp(argv[0], "./abalone") != 0) { printError(); printf("Noob"); return ERROR; }
    
    if(strcmp(argv[1], "-l") == 0) {
        //Lancement local
        if (strcmp(argv[2], "blanc") == 0)
            //On joue les blancs
            return 'w';
        else if(strcmp(argv[2], "noir") == 0)
            //On joue les noirs
            return 'b';
    }
    else if(strcmp(argv[1], "-s") == 0)
        //Lancement réseau : on est le serveur
        return 's';
    else if(strcmp(argv[1], "-c") == 0)
        //Lancement réseau : on est le client
        return 'c';
    printError();
    return ERROR;
}

void printError(){
    printf("Erreur de syntaxe.\n");
    printf("Veuillez taper l'une de ces quatre commandes:\n./abalone -l blanc \n./abalone -l noir \n./abalone -s port \n./abalone -c A.B.C.D:port\n");
}