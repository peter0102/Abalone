#include "network.h"


SOCKET TCPCreateClient(char* serverName,short service){

    struct protoent *ppe = getprotobyname("tcp");
    if (ppe == NULL) exit(1);

    SOCKET s = socket(AF_INET,SOCK_STREAM,ppe->p_proto);
    if (s == INVALID_SOCKET) exit(1);

    struct sockaddr_in sin;
    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(serverName);
    sin.sin_port = htons(service);
    int opt = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt,1 );

    if (connect(s,(struct sockaddr*) &sin,sizeof(sin)) == SOCKET_ERROR) exit(1);

    return s;
}


SOCKET TCPCreateServer(short service){
    struct protoent *ppe = getprotobyname("tcp");
    if (ppe==NULL) exit(1);

    SOCKET s = socket (AF_INET,SOCK_STREAM,ppe->p_proto);
    if (s==INVALID_SOCKET) exit(1);

    struct sockaddr_in sin;
    memset (&sin,0,sizeof(sin));
    sin.sin_family=AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(service);

    int opt = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt,1 );

    if(bind(s,(struct sockaddr*)&sin,sizeof(sin))==SOCKET_ERROR) exit(1);

    if(listen(s,5) == SOCKET_ERROR) exit(1);
    return s;
}
/* A ajouter au main.c
// Envoi de mon coup à l'adversaire
char *move = "A1:B1";
write(fdclient, move, sizeof(move));
// Récupération du coup de l'adversaire (dans `opponent_move`)
char *opponent_move = malloc(sizeof(char) * 6);
read(fdclient, opponent_move, sizeof(opponent_move));
*/


int main(int argc,char** argv){
    if(argv[0]=='-c'){
    	TCPCreateClient(argv[1],argv[2]);
	}
	if(argv[0]=='-s'){
    	TCPCreateServer(argv[1]);
	}
}

