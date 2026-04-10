#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <sys/epoll.h>
#include "../../Define.hpp"

class Server {

  public:
    Server();
    Server(Server &other);
    Server &operator=(Server &other);
    ~Server();

    void	setServerId(const SOCKET socketId);
	void	setServerPass(const std::string &password);
	void	setServerPort(const int port);
    int		getServerId() const;
	int		getServerPort();
	SOCKADDR_IN	&getServerSin();
	std::string getServerPassword();
    void	sockaddrInit(std::string port);


    class errorServerSocket : public std::exception {
      public:
        virtual const char* what() const throw();
    };

private:
    static bool _isServerWorking;
	int			_port;
    std::string	_serverPassword;
    SOCKET      _serverFd;
    SOCKADDR_IN _sin;
};

std::ostream&	operator<<(std::ostream& os, Server &server);

#endif
