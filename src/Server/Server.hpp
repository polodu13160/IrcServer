#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sys/epoll.h>
#include "../../inc/Channel.hpp"
#include "../../Define.hpp"
#include "../MessageParsing/User.hpp"

class User;
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

	User	*getUser(int fd, Server server);

private:
    static bool _isServerWorking;
	int			_port;
    std::string	_serverPassword;
    SOCKET      _serverFd;
    SOCKADDR_IN _sin;

    std::map<int, User> _users;

	friend class User;

};

std::ostream&	operator<<(std::ostream& os, Server &server);

#endif
