#include "Server.hpp"

#include <fstream>


// SERVER CLASS CREATION

bool Server::isServerWorking = false;

Server::Server() {
	sockaddrInit();
}

Server::Server(Server &other) {
	(void)other;
	sockaddrInit();
}

Server &Server::operator=(Server &other) {
	(void)other;
	sockaddrInit();
	return *this;
}

Server::~Server() {

}

// SERVER CLASS MEMBER FUNCTIONS


void Server::setServerId(const SOCKET socketId){
	this->serverId = socketId;
}

int	Server::getServerId() const {
	return this->serverId;
}


void Server::sockaddrInit() {
	this->sin.sin_addr.s_addr = INADDR_ANY;
	this->sin.sin_family =		AF_INET;
	this->sin.sin_port =		htons(PORT);
}


// SERVER CLASS OUT AND EXCEPTIONS

const char *Server::errorServerSocket::what() const throw() {
	return "Error\nServer Socket ID is equal to SOCKET_ERROR";
}

std::ostream& operator<<(std::ostream& os, Server& server) {

	os << "Server socket = " << server.getServerId() << std::endl;
	return os;
}
