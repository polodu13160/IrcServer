#ifndef USER_HPP
# define USER_HPP

#include <iostream>
#include <sstream>
#include <vector>

#include "Channel.hpp"
#include "Server.hpp"
#include "Define.hpp"

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

	void nickCmd(Server& server, const std::vector<std::string> &nickName);
	void userCmd(Server& server, const std::vector<std::string> &userName);
	void modeCmd(Server& server, std::vector<std::string> &modeStr);
	void joinCmd(Server &server, const std::vector<std::string>& arg);
	void listCmd(Server &server, std::vector<std::string> channels_string);
	void pongCmd(const std::vector<std::string> &arg) const;
	void partCmd(Server &server, std::vector<std::string> &arg);


	private :
	int			_userFd;
	std::string	_nickname;
	std::string	_username;
	std::string	_realname;
	std::string	message;

	int	nbChannelRegistered;

	bool	hasANickName;
	bool	hasAUserName;
	bool	registered;
	bool	passMatch;

	__uint32_t		_userMode;

	friend class Server;

};

void	TokenizeMsg(std::string msg);
void	getMsg(Server &server, std::string msg, int userFd);

#endif
