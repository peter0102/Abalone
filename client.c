#include "client.h"


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
