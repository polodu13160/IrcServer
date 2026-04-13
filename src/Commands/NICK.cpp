#include <sys/socket.h>

#include "../../inc/User.hpp"

bool	nickInvalidChar(std::string nickName) {

	const std::string firstValidChar = "[]\\`_^{|}";
	if (!std::isalpha(nickName[0]) && firstValidChar.find(nickName[0]) == std::string::npos) {
		return false;
	}
	const std::string everyValidChar = "-ABCDEFGHIJKLMONPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz[]\\`_^{|}";
	if (nickName.find_first_not_of(everyValidChar) != std::string::npos) {
		return false;
	}
	return true;
}

bool	nickAlreadyUsed(const std::string& nickName, std::map<int, User>& _users) {

	std::map<int, User>::iterator it;

	for (it = _users.begin(); it != _users.end(); ++it) {
		if (it->second.getNickname() == nickName)
			return true;
	}
	return false;
}

void	User::nickCmd(Server &server, const std::vector<std::string>& nickName) {

	std::cout << "Nick cree : " << nickName[0] << std::endl;

	if (nickName.empty()) {

		const std::string line = ":127.0.0.1 431 * :No nickname given\r\n";
		send(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	if (!nickInvalidChar(nickName[0])) {

		const std::string line = ":127.0.0.1 432 " + nickName[0] + " :Erroneous nickname\r\n";
		send(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	if (!nickAlreadyUsed(nickName[0], server._users)) {
		const std::string line = ":127.0.0.1 433 " + nickName[0] + " :Nickname is already in use\r\n";
		send(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	if (this->_nickname.empty()) {
		this->setNickname(nickName[0]);
		return;
	}
	const std::string line = ":" + this->_nickname + "!" + this->_username + "@127.0.0.1 NICK :" + nickName[0] + "\r\n";
	send(this->_userFd, line.c_str(), line.length(), 0);
	this->setNickname(nickName[0]);
	std::cout << RED << "USER NICKNAME = " << nickName[0] << RESET << std::endl;
}
