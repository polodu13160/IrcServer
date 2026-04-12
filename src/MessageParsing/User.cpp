#include "User.hpp"

User::User(int userfd, std::string nickname, std::string username) : _userFd(userfd), _nickname(nickname), _username(username){}


User::User() {

}

User::~User(void){}

const std::string	&User::getNickname(void)const{
	return this->_nickname;
}

const std::string	&User::getUsername(void)const{
	return this->_username;
}

const int	&User::getUserFd(void)const{
	return this->_userFd;
}

void	User::setNickname(std::string nickname){
	this->_nickname = nickname;
}

void	User::setUsername(std::string username){
	this->_username = username;
}

void	User::setUserFd(int userFd){
	this->_userFd = userFd;
}
