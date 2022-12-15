/**
 * \file server.h
 * \brief Création d'un serveur 
 * \author Groupe 1
 * \version 0.1
*/

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

/**
 * \fn TCPCreateServer(short service)
 * \brief Création d'un serveur
 * \param service Le numéro de port
 * \return Retourne le descripteur de la socket
*/
SOCKET TCPCreateServer(short service);



#endif //ABALONE_SERVER
