#include "../../inc/Server.hpp"

#include <fstream>
#include <cstring>
#include <sstream>
#include <fcntl.h>

#include <cstdarg>

const std::string Server::timeNow() const
{
	std::stringstream ss;
	time_t now = time(0);
	ss << now;
	return ss.str();
}

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

Channel *Server::findChannel(std::string name)
{
    std::map<std::string, Channel*>::iterator it = this->_chanMap.find(name);

    if (it != this->_chanMap.end())
        return it->second;

    return NULL;
}

// SERVER CLASS CREATION

bool Server::_isServerWorking = false;

Server::Server(const char *port, const char *password)
	: _port(0), _serverFd(0), _sin()
{
	setServerPass(password);
	setServerPort(port);
	setSocketParams();
	EpollInstance();
}

Server::Server(Server &other)
{
	(void)other;
}

Server &Server::operator=(Server &other)
{
	(void)other;
	return *this;
}

Server::~Server()
{
}

// SERVER CLASS MEMBER FUNCTIONS

std::string Server::getServerPassword()
{
	return this->_serverPassword;
}

SOCKADDR_IN &Server::getServerSin()
{
	return this->_sin;
}

void Server::setUserFd(int fd, std::string ip)
{
	this->_users[fd] = User(fd, "", "");
	this->_users[fd]._ip = ip;
}

// SERVER CLASS OUT AND EXCEPTIONS

// std::ostream& operator<<(std::ostream& os, Server& server) {
//
// 	os << "Server socket = " << server.getServerId() << std::endl <<
// 		"Server Ports = " << server.getServerPort() << std::endl << "Server Password =  " << server.getServerPassword();
// 	return os;
// }

User *Server::getUser(int fd, Server &server)
{
	std::map<int, User>::iterator it;
	for (it = server._users.begin(); it != server._users.end(); ++it)
	{
		if (it->second._userFd == fd)
			return &it->second;
	}
	return NULL;
}

User *Server::getUserbyNickname(std::string nickname)
{
	std::map<int, User>::iterator it;
	for (it = this->_users.begin(); it != this->_users.end(); ++it)
	{
		if (it->second.getNickname() == nickname)
			return &it->second;
	}
	return NULL;
}

const char *Server::errorServerSocket::what() const throw()
{
	return "Error\nServer Socket ID is equal to SOCKET_ERROR.";
}

const char *Server::errorSetSockOpt::what() const throw()
{
	return "Error\nBad Port provided.";
}

void	Server::sendCheck(int fd, const void *buf, size_t n, int flags){
	if(send(fd, buf, n, flags) == -1)
		throw Server::SendFailure();
}

const char* Server::SendFailure::what(void)const throw(){
	return("Send failed to execute!");
}
