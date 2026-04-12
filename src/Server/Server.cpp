#include "Server.hpp"

#include <fstream>
#include <cstring>
#include <sstream>



// SERVER CLASS CREATION

bool Server::_isServerWorking = false;

Server::Server() {
	Channel	test("test", "");
	this->chanVector.push_back(test);
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

void Server::setUserfd(int fd) {
	this->_users[fd] = User(fd, "", "");
}

void Server::sockaddrInit() {

	std::memset(&(this->_sin), 0, sizeof(SOCKADDR_IN));

	this->_sin.sin_addr.s_addr = INADDR_ANY;
	this->_sin.sin_family =		AF_INET;
	this->_sin.sin_port =		htons(this->_port);

}


// User Server::createUserInstance(int userFd, char* info) {
//
// 	std::string nickname;
// 	std::string	username;
// 	std::string realname;
// 	std::string cmd;
//
// 	User test(1, "caca", "caca");
// 	std::string msg(info);
//
// 	std::stringstream ss(msg);
//
// 	ss >> cmd;
// 	ss >> cmd;
// 	ss >> cmd;
// 	ss >> cmd;
// 	ss >> nickname;
// 	ss >> cmd;
// 	ss >> username;
//
// 	std::cout << "Nickname = " << nickname << " Username = " << username << std::endl;
// 	return test;
//
// }


// SERVER CLASS OUT AND EXCEPTIONS

const char *Server::errorServerSocket::what() const throw() {
	return "Error\nServer Socket ID is equal to SOCKET_ERROR";
}

std::ostream& operator<<(std::ostream& os, Server& server) {

	os << "Server socket = " << server.getServerId() << std::endl <<
		"Server Ports = " << server.getServerPort() << std::endl << "Server Password =  " << server.getServerPassword();
	return os;
}
