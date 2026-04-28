#include "../../inc/User.hpp"



User::User(int userfd, std::string nickname, std::string username)
		: _userFd(userfd),
		_nickname(nickname),
		_username(username) {
	this->registered = false;
	this->passMatch = false;
	this->_isBot = false;
	this->_isBot = false;
	this->hasDisconnected = false;
}


User::User() {
}

User::~User(void) {
}

bool	User::setUserRegistration(Server &server){


	if (!this->_nickname.empty() && !this->_username.empty() && !this->_realname.empty() && this->passMatch == true) {
		this->registered = true;
		std::string line = ":" + server._ip + " 001 " + this->_nickname + " :Welcome to the Internet Relay Network\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		line = ":" + server.getIp() + " 002 " + this->getNickname() + " :Your host is " + server.getIp() + ", running version 0.1\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		line = ":" + server._ip + " 003 " + this->_nickname + " :This Server was created a while ago \r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		line = ":" + server.getIp() + " 004 " + this->getNickname() + " " + server.getIp() + " 1.0 o i\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		line = ":" + server._ip + " 375 " + this->_nickname + " :- " + server._ip + " Message of the day - \r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		line = ":" + server._ip + " 372 " + this->_nickname + " :- WELCOME LES BB ! \r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		line = ":" + server._ip + " 376 " + this->_nickname + " :End of MOTD command\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);

		if (this->_nickname == BOTNAME) {
			std::cout << "Bot connected" << std::endl;
			this->_isBot = true;
			server.bot = this;
		}
		std::cout << this->_username << "   " << this->_nickname << "  " << this->_realname << std::endl;
		return true;
	}
	return false;
}

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

std::string &User::getIp()
{
    return this->_ip;
}
