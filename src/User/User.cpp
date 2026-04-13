#include "../../inc/User.hpp"

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

const std::string	&User::getRealname(void)const{
	return this->_realname;
}

std::string	User::getMessage(void){
	if(this->message.find("\r\n") != std::string::npos){
		std::string	msg(this->message);
		this->message = msg += msg.find("\r\n");
		msg.erase(msg.find("\r\n"));
		std::string	leftover = this->message.substr(4, this->message.size() - 4);
		this->message = leftover;
		return msg;
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
