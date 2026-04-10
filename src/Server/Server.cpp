#include "Server.hpp"

#include <fstream>


// SERVER CLASS CREATION

bool Server::_isServerWorking = false;

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
	this->_serverFd = socketId;
}

void Server::setServerPass(const std::string &password) {
	this->_serverPassword = password;
}

void Server::setServerPort(const int port) {
	this->_port = port;
}

int	Server::getServerId() const {
	return this->_serverFd;
}

int Server::getServerPort() {
	return this->_port;
}

std::string Server::getServerPassword() {
	return this->_serverPassword;
}

SOCKADDR_IN &Server::getServerSin() {
	return this->_sin;
}

void Server::sockaddrInit(std::string port) {

	int portValue = 0;
	try {
		portValue = stoi(port);
	}
	catch (std::exception &e) {
		std::cout << e.what();
	}
	this->_sin.sin_addr.s_addr = INADDR_ANY;
	this->_sin.sin_family =		AF_INET;
	this->_sin.sin_port =		htons(portValue);
	this->_port = portValue;

	bind(this->_serverFd, reinterpret_cast<sockaddr *>(&this->_sin), sizeof(this->_sin));

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
