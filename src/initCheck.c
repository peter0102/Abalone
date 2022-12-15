#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"
#include "client.h"
#include "server.h"
#include "initCheck.h"

InitData initialCheck(int argc, char *argv[]) {
    InitData data = {.mode=ERROR, .fdclient=-1};
    
    if (argc != 3) { printError();return data; }
    if (strcmp(argv[0], "./abalone") != 0) { printError(); return data; }
    
    if(strcmp(argv[1], "-l") == 0) {
        //Lancement local
        if (strcmp(argv[2], "blanc") == 0) {
            //On joue les blancs
            data.mode = 'w';
            return data;
        } else if(strcmp(argv[2], "noir") == 0) {
            //On joue les noirs
            data.mode = 'b';
            return data;
        }
    }
    else if(strcmp(argv[1], "-s") == 0) {
        //Lancement réseau : on est le serveur
        data.fdclient = TCPCreateServer((short)atoi(argv[2]));
        data.mode = 's';
        return data;
    } else if(strcmp(argv[1], "-c") == 0) {
        //Lancement réseau : on est le client
        char* server_name = strtok(argv[2], ":");
        short service = (short)atoi(strtok(NULL, ":"));
        data.fdclient = TCPCreateClient(server_name, service);
        data.mode = 'c';
        return data;
    }
    printError();
    return data;
}

void printError(){
    printf("Erreur de syntaxe.\n");
    printf("Veuillez taper l'une de ces quatre commandes:\n./abalone -l blanc \n./abalone -l noir \n./abalone -s port \n./abalone -c A.B.C.D:port\n");
}