#ifndef ABALONE_SERVER
#define ABALONE_SERVER

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>  
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h> 
#include <netinet/in.h>


typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1


SOCKET TCP_Create_Server(short service);



#endif //ABALONE_SERVER
