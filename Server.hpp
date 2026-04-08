#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include "Define.hpp"

class Server {

  public:
    Server();
    Server(Server &other);
    Server &operator=(Server &other);
    ~Server();

    void	setServerId(const SOCKET socketId);
	void	setServerPass(const std::string &password);
    int		getServerId() const;
	int		getServerPort();
	std::string getServerPassword();
    void	sockaddrInit(std::string port);


    class errorServerSocket : public std::exception {
      public:
        virtual const char* what() const throw();
    };

private:
    static bool isServerWorking;
	int			port;
    std::string	serverPassword;
    SOCKET      serverId;
    SOCKADDR_IN sin;
};

std::ostream&	operator<<(std::ostream& os, Server &server);

#endif
