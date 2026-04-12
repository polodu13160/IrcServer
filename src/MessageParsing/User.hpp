#ifndef USER_HPP
# define USER_HPP
#include <iostream>

class User{
	public :
	User();
	User(int userfd, std::string nickname, std::string username);
	~User(void);

	const std::string	&getNickname(void)const;
	const std::string	&getUsername(void)const;
	const std::string	&getRealname(void)const;
	const int			&getUserFd(void)const;

	void	setNickname(std::string nickname);
	void	setUsername(std::string username);
	void	setRealname(std::string realname);
	void	setUserFd(int userFd);

	private :
	int			_userFd;
	std::string	_nickname;
	std::string	_username;
	std::string	_realname;
	std::string	message;

	bool	hasANickName;

};

void	TokenizeMsg(std::string msg);

#endif
