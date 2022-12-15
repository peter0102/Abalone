#include "server.h"

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
    int c = accept(s, NULL, NULL);
    if (c == SOCKET_ERROR) exit(1);

    return c;
}