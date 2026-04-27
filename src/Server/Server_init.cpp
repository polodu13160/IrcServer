#include "../../inc/Server.hpp"
#include <fcntl.h>
#include <sys/epoll.h>
#include <cstring>
#include <cerrno>

void Server::sockaddrInit()
{
    std::memset(&this->_sin, 0, sizeof(SOCKADDR_IN));
    this->_sin.sin_addr.s_addr = INADDR_ANY;
    this->_sin.sin_family      = AF_INET;
    this->_sin.sin_port        = htons(this->_port);
}

static int convertPort(const char *arg)
{
    std::stringstream ss;
    int  tmp = 0;
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
    if (newPort == -1)
        throw Server::errorBadPort();
    this->_port = newPort;
}

void Server::setServerPass(const char *password)
{
    this->_serverPassword = std::string(password);
}

void Server::setSocketParams()
{
    const SOCKET serverId = socket(AF_INET, SOCK_STREAM, 0);
    if (serverId == SOCKET_ERROR)
        throw Server::errorSocket();
    this->_serverFd = serverId;

    const int opt = 1;
    if (setsockopt(this->_serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) != 0)
        throw Server::errorSetSockOpt();

    this->sockaddrInit();
    this->_ip = HOST;
    std::cout << RED << "Server IP: " << this->_ip << RESET << std::endl;

    if (bind(this->_serverFd, reinterpret_cast<sockaddr *>(&this->_sin), sizeof(this->_sin)) == -1)
        throw Server::errorBind();

    if (listen(this->_serverFd, SOMAXCONN) == -1)
        throw Server::errorListen();

    if (fcntl(this->_serverFd, F_SETFL, O_NONBLOCK) == -1)
        throw Server::errorFcntl();
}

void Server::EpollInstance()
{
    this->_epollInstance = epoll_create1(EPOLL_CLOEXEC);
    if (this->_epollInstance == -1)
        throw Server::errorEpollCreate();

    epoll_event serverEvent = {}; // a cahnger
    serverEvent.events   = EPOLLIN;
    serverEvent.data.fd  = this->_serverFd;
    if (epoll_ctl(this->_epollInstance, EPOLL_CTL_ADD, this->_serverFd, &serverEvent) == -1)
        throw Server::errorEpollCtl();

    while (true)
    {
        const int ready = epoll_wait(this->_epollInstance, this->_userEvent, 64, -1);
        if (ready == -1)
        {
            if (errno == EINTR)
                continue;
            throw Server::errorEpollWait();
        }

        for (int i = 0; i < ready; i++)
        {
            if (this->_userEvent[i].data.fd == this->_serverFd)
            {
                struct sockaddr_in clientAddr;
				socklen_t          clientAddrLen = sizeof(clientAddr);
				std::memset(&clientAddr, 0, clientAddrLen);

				while (true)
                {
                    const int clientFd = accept(this->_serverFd, reinterpret_cast<struct sockaddr *>(&clientAddr),&clientAddrLen);

                    if (clientFd == -1)
                    {
                        if (errno == EAGAIN || errno == EWOULDBLOCK)
                            break;
                        throw Server::errorAccept();
                    }

                    if (fcntl(clientFd, F_SETFL, O_NONBLOCK) == -1)
                    {
                        close(clientFd);
                        throw Server::errorFcntl();
                    }

                    epoll_event ev = {};
                    ev.events  = EPOLLIN;
                    ev.data.fd = clientFd;
                    if (epoll_ctl(this->_epollInstance, EPOLL_CTL_ADD, clientFd, &ev) == -1)
                    {
                        close(clientFd);
                        throw Server::errorEpollCtl();
                    }

                    const std::string clientIp = inet_ntoa(clientAddr.sin_addr);
                    this->setUserFd(clientFd, clientIp);
                    std::cout << GREEN << "New client: " << clientIp
                              << " (fd=" << clientFd << ")" << RESET << std::endl;
                }
            }
            else
            {
                const int fd = this->_userEvent[i].data.fd;
                char      buffer[MAX_SIZE_MESSAGE + 1];
                std::memset(buffer, 0, sizeof(buffer));

                const ssize_t bytes = recv(fd, buffer, MAX_SIZE_MESSAGE, 0);

                if (bytes == 0)
                {
                    std::cout << RED << "Client disconnected (fd=" << fd << ")" << RESET << std::endl;
                    epoll_ctl(this->_epollInstance, EPOLL_CTL_DEL, fd, NULL);
                    close(fd);
                	this->_userEvent[i].data.fd = -1;
                    this->_users.erase(fd);
                    continue;
                }
                if (bytes == -1)
                {
                    if (errno == EAGAIN || errno == EWOULDBLOCK)
                        continue;

                    epoll_ctl(this->_epollInstance, EPOLL_CTL_DEL, fd, NULL);
                    close(fd);
                	this->_userEvent[i].data.fd = -1;
                    this->_users.erase(fd);
                    continue;
                }

                getMsgFD(*this, buffer, fd);
            }
        }
    }
}