#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>

class Server {

  public:
    Server();
    Server(Server &other);
    Server &operator=(Server &other);
    ~Server();

  private:
    bool isServerWorking;
};

#endif
