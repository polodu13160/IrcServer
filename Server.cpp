#include "Server.hpp"

#include <fstream>


// SERVER CLASS CREATION

bool Server::isServerWorking = false;

Server::Server() {
}

Server::Server(Server &other) {
	(void)other;
}

Server &Server::operator=(Server &other) {
	(void)other;
	return *this;
}

Server::~Server() {

}

// SERVER CLASS MEMBER FUNCTIONS


void Server::setServerId(const SOCKET socketId){
	this->serverId = socketId;
}

void Server::setServerPass(const std::string &password) {
	this->serverPassword = password;
}

int	Server::getServerId() const {
	return this->serverId;
}

int Server::getServerPort() {
	return this->port;
}

std::string Server::getServerPassword() {
	return this->serverPassword;
}


void Server::sockaddrInit(std::string port) {

	int portValue = 0;
	try {
		portValue = stoi(port);
	}
	catch (std::exception &e) {
		std::cout << e.what();
	}
	this->sin.sin_addr.s_addr = INADDR_ANY;
	this->sin.sin_family =		AF_INET;
	this->sin.sin_port =		htons(portValue);
	this->port = portValue;

	bind(this->serverId, reinterpret_cast<sockaddr *>(&this->sin), sizeof(this->sin));

}


// SERVER CLASS OUT AND EXCEPTIONS

const char *Server::errorServerSocket::what() const throw() {
	return "Error\nServer Socket ID is equal to SOCKET_ERROR";
}

std::ostream& operator<<(std::ostream& os, Server& server) {

	os << "Server socket = " << server.getServerId() << std::endl <<
		"Server Ports = " << server.getServerPort() << std::endl << "Server Password =  " << server.getServerPassword();
	return os;
}
