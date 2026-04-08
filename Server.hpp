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
    int		getServerId() const;

    class errorServerSocket : public std::exception {
      public:
        virtual const char* what() const throw();
    };

  private:

    static bool isServerWorking;
    SOCKET      serverId;
    SOCKADDR_IN sin;

	void	sockaddrInit();

};

std::ostream&	operator<<(std::ostream& os, Server &server);

#endif
