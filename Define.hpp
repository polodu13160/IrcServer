#ifndef DEFINE_HPP
#define DEFINE_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// SERVER OPTIONS

#define INVALID_SOCKET  (-1)
#define SOCKET_ERROR    (-1)
#define PORT			6667

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;

// LISTE DES ERREURS, BIEN REGARDER SI ELLES EXISTENT PAS DEJA.

#define ERR_SERVERCRASH "Server crash."
#define ERR_SOCKET		"Socket function crash."
#define ERR_POLL		"Poll function crash."



// LISTE DES COULEURS


#define RESET			"\033[0m"
#define RED     		"\033[31m"
#define GREEN   		"\033[32m"
#define YELLOW  		"\033[33m"
#define CYAN    		"\033[36m"
#define BOLD    		"\033[1m"




#endif
