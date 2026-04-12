#ifndef USER_HPP
# define USER_HPP

#include <iostream>
#include <sstream>
#include <vector>

#include "Message.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "cmdPars.hpp"

class Server;

class User{
	public :
	User();
	User(int userfd, std::string nickname, std::string username);
	~User(void);

	const std::string	&getNickname(void)const;
	const std::string	&getUsername(void)const;
	const std::string	&getRealname(void)const;
	const int			&getUserFd(void)const;
	std::string			getMessage(void);

	void	setNickname(std::string nickname);
	void	setUsername(std::string username);
	void	setRealname(std::string realname);
	void	setUserFd(int userFd);
	void	setMessage(std::string realname);


	// CMD

	void nickCmd(Server& server, const std::string& nickName);
	void userCmd(Server& server, const std::string& userName);
	void joinCmd(Server& server, User& user, std::string channel, std::string pass);

	private :
	int			_userFd;
	std::string	_nickname;
	std::string	_username;
	std::string	_realname;
	std::string	message;

	bool	hasANickName;
	bool	hasAUserName;
	bool	registered;

	friend class Server;

};

void	TokenizeMsg(std::string msg);
void	getMsg(Server &server, std::string msg, int userFd);

#endif
