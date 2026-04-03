#include "Server.hpp"

#include <fstream>

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

const char *Server::errorServerSocket::what() const throw() {
  return "Error\nServer Socket ID is equal to SOCKET_ERROR";
}

Server::~Server() {

}


void Server::setServerId(const SOCKET socketId){
	this->serverId = socketId;
}

int	Server::getServerId() {
	return this->serverId;
}


void Server::sockaddrInit() {
	this->sin.sin_addr.s_addr = INADDR_ANY;
	this->sin.sin_family =		AF_INET;
	this->sin.sin_port =		htons(PORT);
}


std::ostream& operator<<(std::ostream& os, Server& server) {

	os << "Server socket = " << server.getServerId() << std::endl;
	return os;
}
