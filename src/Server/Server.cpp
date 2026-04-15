#include "../../inc/Server.hpp"

#include <fstream>
#include <cstring>
#include <sstream>
#include <cstdarg>


/**
 * @brief send message for terminal of server
 * 
 * @param text first message followed by a space
 * @param ... others messages followed by  spaces, 
 * @attention the last param must to be NULL 
 */
void Server::messageToServer(const char *text, ...)
{
    if (text == NULL)
        return;
    std::va_list args;
    std::cout << text;
    va_start(args, text);
    const char *val = va_arg(args, const char *);
    const char *valNext;
    while (val != NULL)
    {
        if ((valNext = va_arg(args, const char *)) == NULL)
            std::cout << val;
        else 
            std::cout << val << " ";
        val = valNext;
    }
    va_end(args);
    std::cout << std::endl;
}



// SERVER CLASS CREATION

bool Server::_isServerWorking = false;

Server::Server() : _maxChanPerUser(100){
	// Channel	test("test", "");
	// this->chanVector.push_back(test);
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

User	*Server::getUser(int fd, Server &server){
	std::map<int, User>::iterator	it;
	for(it = server._users.begin(); it != server._users.end(); ++it){
		if(it->second._userFd == fd)
			return &it->second;
	}
	return NULL;
}
