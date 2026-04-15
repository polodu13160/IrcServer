#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Channel.hpp"
#include "../Define.hpp"
#include "User.hpp"

class User;
class Channel;
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

	User	*getUser(int fd, Server &server);
    static void messageToServer(const char *text, ...);

private:
    static bool _isServerWorking;
	int			_port;
    std::string	_serverPassword;
    SOCKET      _serverFd;
    SOCKADDR_IN _sin;

	int	_maxChanPerUser;

    std::map<int, User> _users;
	std::vector<Channel> _chanVector;
    

	friend class User;

};

std::ostream&	operator<<(std::ostream& os, Server &server);

#endif
