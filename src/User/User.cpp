#include "../../inc/User.hpp"



User::User(int userfd, std::string nickname, std::string username)
		: _userFd(userfd),
		_nickname(nickname),
		_username(username) {
	this->registered = false;
}


User::User() {

}

User::~User(void){}

const std::string	&User::getNickname(void)const{
	return this->_nickname;
}

const std::string	&User::getUsername(void)const{
	return this->_username;
}

const std::string	&User::getRealname(void)const{
	return this->_realname;
}

std::string	User::getMessage(void){
	size_t pos = this->message.find("\r\n");
	if (pos != std::string::npos) {
		std::string cmd = this->message.substr(0, pos);
		this->message.erase(0, pos + 2);
		return cmd;
	}
	std::string str("");
	return str;
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

void	User::setRealname(std::string realname){
	this->_realname = realname;
}

void	User::setUserFd(int userFd){
	this->_userFd = userFd;
}

void	User::setMessage(std::string message){
	this->message += message;
}
