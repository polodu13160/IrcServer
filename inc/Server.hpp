#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Channel.hpp"
#include "Define.hpp"
#include "User.hpp"

class User;
class Channel;
class Server {

  public:
	//utils pour le timestamp
	const std::string timeNow() const;

    Server();


	Server(const char *port, const char *password);
    Server(Server &other);
    Server &operator=(Server &other);
    ~Server();


	// Nouvelle classe :

	void setServerPort(const char *str);
	void setServerPass(const char *password);
	void setSocketParams();
	void EpollInstance();


	// Ancienne classe

	void	setUserFd(int fd);
	SOCKADDR_IN	&getServerSin();
	std::string getServerPassword();
    void	sockaddrInit();
    // User createUserInstance(int userFd, char* info);

    // User	*createUserInstance(int userFd, char *info);
    Channel	*findChannel(std::string channel);

	User	*getUser(int fd, Server &server);
	User	*getUserbyNickname(std::string nickname);
    static void messageToServer(const char *text, ...);


	class errorServerSocket : public std::exception {
	public:
		virtual const char* what() const throw();
	};

	// class errorBadPort : public std::exception {
	// public:
	// 	virtual const char* what() const throw();
	// };

	class errorSetSockOpt : public std::exception {
	public:
		virtual const char* what() const throw();
	};

	static void	sendCheck(int __fd, const void *__buf, size_t __n, int __flags);

	class SendFailure : public std::exception{
		virtual const char *what(void)const throw();
	};

	// class errorBind : public std::exception {
	// public:
	// 	virtual const char* what() const throw();
	// };

private:
    static bool _isServerWorking;
	int			_port;
    std::string	_serverPassword;
    SOCKET      _serverFd;
    SOCKADDR_IN _sin;

	int	_maxChanPerUser;

    std::map<int, User> _users;
	std::map<std::string, Channel*> _chanMap;


	friend class User;

};

// std::ostream&	operator<<(std::ostream& os, Server &server);


#endif
