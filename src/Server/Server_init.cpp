#include "../../inc/Server.hpp"
#include <fcntl.h>
#include <sys/epoll.h>
#include <cstring>
#include <cerrno>

void Server::sockaddrInit()
{

	std::memset(&(this->_sin), 0, sizeof(SOCKADDR_IN));

	this->_sin.sin_addr.s_addr = INADDR_ANY;
	this->_sin.sin_family = AF_INET;
	this->_sin.sin_port = htons(this->_port);
}

static int convertPort(const char *arg)
{

	std::stringstream ss;
	int tmp = 0;
	char rest;
	ss << arg;

	if (!(ss >> tmp) || (ss >> rest))
		return -1;
	if (tmp < 1024 || tmp > 65535)
		return -1;
	return tmp;
}

void Server::setServerPort(const char *str)
{

	const int newPort = convertPort(str);
	// if (newPort == -1)
	// 	throw Server::errorBadPort();
	this->_port = newPort;
}

void Server::setServerPass(const char *password)
{

	const std::string newPass(password);
	this->_serverPassword = newPass;
}

void Server::setSocketParams()
{

	const SOCKET serverId = socket(AF_INET, SOCK_STREAM, 0);
	if (serverId == SOCKET_ERROR)
	{
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

void Server::EpollInstance()
{

	int epollInstance = epoll_create1(EPOLL_CLOEXEC);
	epoll_event serverEvent = {};
	serverEvent.events = EPOLLIN;
	serverEvent.data.fd = this->_serverFd;

	epoll_ctl(epollInstance, EPOLL_CTL_ADD, this->_serverFd, &serverEvent);

	epoll_event userEvent[64];

	int clientFd = 0;
	std::string clientIp;

	std::cout << RED << "SERVER INITIALISATION DONE !" << RESET << std::endl;

	while (true)
	{
		const int ready = epoll_wait(epollInstance, userEvent, 64, -1);

		for (int i = 0; i < ready; i++)
		{

			if (userEvent[i].data.fd == this->_serverFd)
			{
				struct sockaddr_in clientAddr;
				socklen_t clientAddrLen = sizeof(clientAddr);

				while (true)
				{
					clientFd = accept(this->_serverFd, reinterpret_cast<struct sockaddr *>(&clientAddr), &clientAddrLen);
					if (clientFd == -1)
						break;
					clientIp = inet_ntoa(clientAddr.sin_addr);
					fcntl(clientFd, F_SETFL, O_NONBLOCK); 

					struct epoll_event ev;
					std::memset(&ev, 0, sizeof(ev));
					ev.events = EPOLLIN;
					ev.data.fd = clientFd;
					epoll_ctl(epollInstance, EPOLL_CTL_ADD, clientFd, &ev);

					this->setUserFd(clientFd, clientIp); 
					std::cout << GREEN << "NEW USER CONNECTED: " << clientIp << " (FD: " << clientFd << ")" << RESET << std::endl;
				}
			}
			else
			{
				char buffer[MAX_SIZE_MESSAGE + 1];

				std::memset(buffer, 0, MAX_SIZE_MESSAGE);

				size_t bytes = recv(userEvent[i].data.fd, buffer, MAX_SIZE_MESSAGE, 0);

				if (bytes == 0)
				{
					std::cout << RED << "CLient deco" << RESET << std::endl;
					epoll_ctl(epollInstance, EPOLL_CTL_DEL, userEvent[i].data.fd, NULL);
					close(userEvent[i].data.fd);
					// kais important de faire ca sinon pas supprimer totalement et ca rentre quand meme dans
					// getmessage jai deja eu un segfault a cause de ca
					// normalement comme ca c good
					this->_users.erase(userEvent[i].data.fd);
					continue;
				}
				getMsg(*this, buffer, userEvent[i].data.fd);
#if (DEBUG == 1)
// std::cout << CYAN << "NEW MSG FROM CLIENT FD " << clientFd << " : " << RESET << std::endl;
// std::cout << buffer << std::endl;
// std::cout << CYAN << "END OF MSG " << RESET << std::endl;
#endif // DEBUG
			}
		}
	}
}