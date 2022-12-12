#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initial_check(int argc, const char* argv[]);

int main(int argc, const char * argv[]){
    char string1;
    strcpy(&string1,argv[0]);
    char string2;
    strcpy(&string2,argv[1]);
    char string3;
    strcpy(&string3,argv[2]);            
}

void initial_check(int argc, const char* argv[]) {
    if (argc == 3 && argv[0] == "./abalone") {
        if(argv[1] == "-l" && argv[2] == "blanc") {
            //Lancement local : on joue les blancs
            return;
        }
        else if(argv[1] == "-l" && argv[2] == "noir") {
            //Lancement local : on joue les noirs
            return;
        }
        else if(argv[1] == "-s") {
            //Lancement réseau : on est le serveur
            return;
        }
        else if(argv[1] == "-c") {
            //Lancement réseau : on est le client
            return;        
        }
    }
    printf("Erreur de syntaxe");
    printf("Veuillez taper l'une de ces quatre commandes:\n./abalone -l blanc \n./abalone -l noir \n./abalone -s port \n./abalone -c A.B.C.D:port");
}