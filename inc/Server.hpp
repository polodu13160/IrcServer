#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <map>
#include <sys/epoll.h>

#include "Channel.hpp"
#include "Define.hpp"
#include "User.hpp"

class User;
class Channel;

class Server {

public:

    Server();
    Server(const char *port, const char *password);
    ~Server();


    void setServerPort(const char *str);
    void setServerPass(const char *password);
    void sockaddrInit();
    void setSocketParams();
    void EpollInstance();


    SOCKADDR_IN       &getServerSin();
    std::string        getServerPassword();
    std::string       &getIp();
    const std::string  timeNow() const;


    void   setUserFd(int fd, std::string ip);
    User  *getUser(int fd, Server &server);
    User  *getUserByNickname(const std::string &nickname);


    Channel *findChannel(const std::string &channel);
    void     deletedChannel(Channel *channel);


    static void messageToServer(const char *text, ...);
    static void sendCheck(int fd, const void *buf, size_t n, int flags);
	void	getMsgFD(Server &server, std::string msg, int userFd);



    class errorBind        : public std::exception {
		public: const char *what() const throw();
    };
    class errorListen      : public std::exception {
		public: const char *what() const throw();
    };
    class errorFcntl       : public std::exception {
		public: const char *what() const throw();
    };
    class errorSocket      : public std::exception {
		public: const char *what() const throw();
    };
    class errorBadPort     : public std::exception {
		public: const char *what() const throw();
    };
    class errorSetSockOpt  : public std::exception {
		public: const char *what() const throw();
    };
    class errorEpollCreate : public std::exception {
		public: const char *what() const throw();
    };
    class errorEpollCtl    : public std::exception {
		public: const char *what() const throw();
    };
    class errorEpollWait   : public std::exception {
		public: const char *what() const throw();
    };
    class errorAccept      : public std::exception {
		public: const char *what() const throw();
    };
    class errorRecv        : public std::exception {
		public: const char *what() const throw();
    };
    class sendFailure      : public std::exception {
		public: const char *what() const throw();
    };

private:
    static bool _isServerWorking;

	SOCKET      _serverFd;
	SOCKADDR_IN _sin;
	std::string _serverPassword;
	std::string _ip;
	epoll_event _userEvent[64];
	int         _port;
	int         _epollInstance;
	int         _maxChanPerUser;

	User      *bot;

	std::map<int, User>              _users;
	std::map<std::string, Channel *> _chanMap;

	friend class User;
};

#endif
