/**
 * \file client.h
 * \brief Fonction d'établissement de connexion
 * \author Groupe 1
 * \version 0.1
*/

#ifndef ABALONE_CLIENT
#define ABALONE_CLIENT

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
 * \fn TCPCreateClient(char* severName,short service)
 * \brief Etabli la connexion d'un client à un serveur
 * \param serverName L'adresse IP
 * \param service Le numéro de port
 * \return Retourne le descripteur de la socket
*/
SOCKET TCPCreateClient(char* severName,short service);




#endif //ABALONE_CLIENT
