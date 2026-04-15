#include "../../inc/Server.hpp"

#include <fstream>
#include <cstring>
#include <sstream>
#include <fcntl.h>



static int	convertPort(const char *arg) {

	std::stringstream	ss;
	int					tmp = 0;
	char				rest;
	ss << arg;

	if (!(ss >> tmp) || (ss >> rest))
		return -1;
	if (tmp < 1024 || tmp > 65535)
		return -1;
	return tmp;
}

void Server::setServerPort(const char *str) {

	const int	newPort = convertPort(str);
	if (newPort == -1)
		throw Server::errorServerSocket();
	this->_port = newPort;
}

void Server::setServerPass(const char *password) {
	
	std::string newPass(password);
	this->_serverPassword = newPass;
}

void	Server::setSocketParams() {

	const SOCKET serverId = socket(AF_INET, SOCK_STREAM, 0);
	if (serverId == SOCKET_ERROR) {
		throw Server::errorServerSocket();
	}
	this->_serverFd = serverId;
	const int opt = 1;
	if (setsockopt(this->_serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) != 0)
		throw Server::errorServerSocket();
	this->sockaddrInit();
	if (bind(_serverFd, reinterpret_cast<sockaddr *>(&_sin), sizeof(_sin)) == -1)
		throw errorServerSocket();
	listen(_serverFd, SOMAXCONN);
	fcntl(_serverFd, F_SETFL, O_NONBLOCK);
}




// SERVER CLASS CREATION

bool Server::_isServerWorking = false;

Server::Server(const char *port, const char *password)
	: _port(0), _serverFd(0), _sin() {
	setServerPass(password);
	setServerPort(port);
	setSocketParams();
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

void Server::setUserfd(int fd) {
	this->_users[fd] = User(fd, "", "");
}

void Server::sockaddrInit() {

	std::memset(&(this->_sin), 0, sizeof(SOCKADDR_IN));

	this->_sin.sin_addr.s_addr = INADDR_ANY;
	this->_sin.sin_family =		AF_INET;
	this->_sin.sin_port =		htons(this->_port);

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

User	*Server::getUser(int fd, Server &server){
	std::map<int, User>::iterator	it;
	for(it = server._users.begin(); it != server._users.end(); ++it){
		if(it->second._userFd == fd)
			return &it->second;
	}
	return NULL;
}
