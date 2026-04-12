#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sys/epoll.h>
#include <vector>
#include "../../Define.hpp"
#include "../MessageParsing/User.hpp"
#include "../inc/Channel.hpp"
using namespace std;


class Server {

  public:
    Server();
    Server(Server &other);
    Server &operator=(Server &other);
    ~Server();

    void	setServerId(const SOCKET socketId);
	void	setServerPass(const std::string &password);
	void	setServerPort(const int port);
	void	setUserfd(int fd);
    int		getServerId() const;
	int		getServerPort();
	SOCKADDR_IN	&getServerSin();
	std::string getServerPassword();
    void	sockaddrInit();
    // User createUserInstance(int userFd, char* info);

    // User	*createUserInstance(int userFd, char *info);


    class errorServerSocket : public std::exception {
      public:
        virtual const char* what() const throw();
    };

	vector<Channel> chanVector;

private:
    static bool _isServerWorking;
	int			_port;
    std::string	_serverPassword;
    SOCKET      _serverFd;
    SOCKADDR_IN _sin;

    std::map<int, User> _users;

};

std::ostream&	operator<<(std::ostream& os, Server &server);

#endif
