#ifndef USER_HPP
# define USER_HPP
#include <iostream>

class User{
	public :
	User(int userfd);
	~User(void);

	const std::string	&getNickname(void)const;
	const std::string	&getUsername(void)const;
	const int			&getUserFd(void)const;

	void	setNickname(std::string nickname);
	void	setUsername(std::string username);
	void	setUserFd(int userFd);

	private :
	int			_userFd;
	std::string	_nickname;
	std::string	_username;
};

#endif
