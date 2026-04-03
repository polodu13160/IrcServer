#include "Server.hpp"

bool Server::isServerWorking = false;

Server::Server() {
}

Server::Server(Server &other) {
	(void)other;
}

void Server::setServerId(const SOCKET socketId){
  this->serverId = socketId;
}

Server &Server::operator=(Server &other) {
	(void)other;

	return *this;
}

const char *Server::errorServerSocket::what() const throw() {
  return "Error\nServer Socket ID is equal to SOCKET_ERROR";
}

Server::~Server() {

}
