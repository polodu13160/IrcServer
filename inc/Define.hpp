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
#define HOST			"127.0.0.1"

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

// MODE ENUMS

enum e_modes {
	MODE_INVITE_O = 		(1 << 0),
	MODE_TOPIC_RESTRICT = 	(1 << 1),
	MODE_KEY_SET =			(1 << 2),
	MODE_LIMIT_SET =		(1 << 3),
	MODE_OPERATOR =			(1 << 4),
	MODE_BAD =				(1 << 5)
};

#define NEG_SIGN	false
#define POS_SIGN	true


#endif
