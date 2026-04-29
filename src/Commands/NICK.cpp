#include <sys/socket.h>

#include "User.hpp"



bool	nickInvalidChar(const std::string &nickName) {

	const std::string firstValidChar = "[]\\`_^{|}";
	if (!nickName[0])
		return false;
	if (!std::isalpha(nickName[0]) && firstValidChar.find(nickName[0]) == std::string::npos) {
		return false;
	}
	const std::string everyValidChar = "1234567890-ABCDEFGHIJKLMONPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz[]\\`_^{|}";
	if (nickName.find_first_not_of(everyValidChar) != std::string::npos) {
		return false;
	}
	return true;
}

bool	nickAlreadyUsed(const std::string& nickName, std::map<int, User>& _users) {
	for (std::map<int, User>::iterator it = _users.begin(); it != _users.end(); ++it) {
		if (it->second.getNickname() == nickName)
			return true;
	}
	return false;
}

void	User::nickCmd(Server &server, const std::vector<std::string>& nickName) {

	if (this->passMatch == false) {

		const std::string line = ":" + server.getIp() + " 431 * :Can't connect without password\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	if (nickName.empty()) {

		const std::string line = ":" + server.getIp() + " 431 * :No nickname given\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	if (nickName[0].empty() || nickName[0].size() > 9) {
		const std::string line = ":" + server.getIp() + " 432 " + nickName[0] + " :Erroneous nickname\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	if (!nickInvalidChar(nickName[0])) {

		const std::string line = ":" + server.getIp() + " 432 " + nickName[0] + " :Erroneous nickname\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	if (nickAlreadyUsed(nickName[0], server._users)) {
		const std::string line = ":" + server.getIp() + " 433 " + nickName[0] + " :Nickname is already in use\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}

	if (this->_nickname.empty()) {
		this->setNickname(nickName[0]);
		setUserRegistration(server);
	} else {
		const std::string line = ":" + this->_nickname + "!" + this->_username + "@" + this->_ip + " NICK :" + nickName[0] + "\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		this->setNickname(nickName[0]);
	}
}
