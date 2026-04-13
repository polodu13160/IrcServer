#ifndef USER_HPP
# define USER_HPP
#include <iostream>

class User{
	public :
	User(int userfd, std::string nickname, std::string username);
	~User(void);

	const std::string	&getNickname(void)const;
	const std::string	&getUsername(void)const;
	const int			&getUserFd(void)const;

	void	setNickname(std::string nickname);
	void	setUsername(std::string username);
	void	setUserFd(int userFd);

	void kick(User &user, User &userKick);
    void invite(User &user, User &userInvite);
    void topic(User &user, std::string topic);
    void mode(char type, User &user);
    void join(User &user, std::string password = "");

	private :
	int			_userFd;
	std::string	_nickname;
	std::string	_username;
	static const std::string TYPEMODE;
};

#endif
