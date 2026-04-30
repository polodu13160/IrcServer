#include "../../inc/User.hpp"
#include "User.hpp"



User::User(int userfd, std::string nickname, std::string username)
		: _userFd(userfd),
		_nickname(nickname),
		_username(username) {
	this->_registered = false;
	this->_passMatch = false;
	this->_isBot = false;

	this->setHasDisconnected(false);
}


User::User() : _userFd(), _registered(), _passMatch(), _isBot() {
}

User::~User() {
}

bool User::setUserRegistration(Server &server) {
	if (!this->_nickname.empty() && !this->_username.empty() && !this->_realname.empty() && this->_passMatch == true) {
		this->_registered = true;
		std::string line = ":" + server._ip + " 001 " + this->_nickname + " :Welcome to the Internet Relay Network " + this->_nickname + "!\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		line = ":" + server.getIp() + " 002 " + this->getNickname() + " :Your host is " + server.getIp() + ", running version 1.0\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		line = ":" + server._ip + " 003 " + this->_nickname + " :This server was created on " + __DATE__ + "\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		line = ":" + server.getIp() + " 004 " + this->getNickname() + " " + server.getIp() + " 1.0 o i\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		line = ":" + server._ip + " 375 " + this->_nickname + " :- " + server._ip + " Message of the Day -\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		line = ":" + server._ip + " 372 " + this->_nickname + " :- Welcome to " + server._ip + ". Please be respectful and enjoy your stay.\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		line = ":" + server._ip + " 372 " + this->_nickname + " :- Type /LIST to browse available channels.\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		line = ":" + server._ip + " 376 " + this->_nickname + " :End of /MOTD command.\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		if (this->_nickname == BOTNAME) {
			std::cout << "[BOT] " << BOTNAME << " has connected to the server." << std::endl;
			this->_isBot = true;
			server._bot = this;
		}
		std::cout << "[INFO] New user registered — nick: " << this->_nickname
				  << " | user: " << this->_username
				  << " | real: " << this->_realname << std::endl;
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
	size_t pos = this->_message.find("\r\n");
	if (pos != std::string::npos) {
		if(this->_message.size() > 512){
			this->_message = ":";
			this->_message += HOST;
			this->_message += " 417 " + this->_nickname + " : Your message is too long \r\n" ;
			Server::sendCheck(this->_userFd, this->_message.c_str(), this->_message.size(), 0);
			return this->_message = "";
		}
		std::string cmd = this->_message.substr(0, pos);
		this->_message.erase(0, pos + 2);
		return cmd;
	}
	this->_message = "";
	return this->_message;
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
	this->_message += message;
}

std::string &User::getIp()
{
    return this->_ip;
}

void User::setHasDisconnected(bool val)
{
    this->_hasDisconnected = val;
}

bool User::getHasDisconnected()
{
    return this->_hasDisconnected;
}
