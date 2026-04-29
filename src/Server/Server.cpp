#include "Server.hpp"

#include <fstream>
#include <cstring>
#include <sstream>
#include <fcntl.h>

#include <cstdarg>
#include "Server.hpp"


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

Channel *Server::findChannel(const std::string &channel)
{
    const std::map<std::string, Channel*>::iterator it = this->_chanMap.find(channel);

    if (it != this->_chanMap.end())
        return it->second;

    return NULL;
}

// SERVER CLASS CREATION

bool Server::_isServerWorking = false;

Server::Server(const char *port, const char *password)
	: _serverFd(0), _sin(), _userEvent(), _port(0), _epollInstance(), _maxChanPerUser(), bot(NULL)
{
	setServerPass(password);
	setServerPort(port);
	std::memset(this->_userEvent, 0, sizeof(this->_userEvent));
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

void Server::deletedChannel(Channel *channel)
{
	this->_chanMap.erase(channel->getName());
	delete channel;
}

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

User *Server::getUserByNickname(const std::string &nickname)
{
	for (std::map<int, User>::iterator it = this->_users.begin(); it != this->_users.end(); ++it)
	{
		if (it->second.getNickname() == nickname)
			return &it->second;
	}
	return NULL;
}

void	Server::sendCheck(int fd, const void *buf, size_t n, int flags){
	if(send(fd, buf, n, flags) == -1)
		throw Server::sendFailure();
}


std::string &Server::getIp()
{
	return this->_ip;
}

Server::~Server() {

	for (std::map<int, User>::iterator it = this->_users.begin(); it != this->_users.end(); ++it) {
		epoll_ctl(this->_epollInstance, EPOLL_CTL_DEL, it->first, NULL);
		close(it->first);
	}
	this->_users.clear();
	if (this->_epollInstance > 0)
		close(this->_epollInstance);
	    this->_users.clear();
	if (this->_serverFd > 0) {
		close(this->_serverFd);
		this->_serverFd = -1;
	}
	for (std::map<std::string, Channel*>::iterator it = this->_chanMap.begin(); it != this->_chanMap.end(); ++it) {
		delete it->second;
	}
}



const char *Server::errorSocket::what() const throw()
{
	return "Error\nServer Socket ID is equal to SOCKET_ERROR.";
}

const char *Server::errorSetSockOpt::what() const throw()
{
	return "Error\nsetsockopt function crashed.";
}

const char *Server::errorBind::what() const throw()
{
	return "Error\nbind function crashed.";
}

const char *Server::errorBadPort::what() const throw()
{
	return "Error\nbad port provided.";
}

const char* Server::sendFailure::what(void)const throw(){
	return("Send failed to execute!");
}

const char *Server::errorListen::what() const throw()
{
	return "Error\nlisten function crashed.";
}

const char *Server::errorFcntl::what() const throw()
{
	return "Error\nfcntl function crashed.";
}

const char *Server::errorEpollCreate::what() const throw()
{
	return "Error\nepoll_create1 function crashed.";
}

const char *Server::errorEpollCtl::what() const throw()
{
	return "Error\nepoll_ctl function crashed.";
}

const char *Server::errorEpollWait::what() const throw()
{
	return "Error\nepoll_wait function crashed.";
}

const char *Server::errorAccept::what() const throw()
{
	return "Error\naccept function crashed.";
}

const char *Server::errorRecv::what() const throw()
{
	return "Error\nrecv function crashed.";
}



