#ifndef USER_HPP
# define USER_HPP
#include <iostream>
#include "../Server/Server.hpp"

class Server;

class User{
	public :
	User();
	User(int userfd, std::string nickname, std::string username);
	~User(void);

	const std::string	&getNickname(void)const;
	const std::string	&getUsername(void)const;
	const int			&getUserFd(void)const;

	void	setNickname(std::string nickname);
	void	setUsername(std::string username);
	void	setUserFd(int userFd);


	// CMD

	void nickCmd(Server& server, const std::string& nickName);

	private :
	int			_userFd;
	std::string	_nickname;
	std::string	_username;

	bool	hasANickName;

	friend class Server;

};

void	TokenizeMsg(std::string msg);

#endif
