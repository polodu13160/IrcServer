#include "../../inc/User.hpp"
#include "User.hpp"


void	User::passCmd(Server &server, std::vector<std::string> &arg) {

	if (arg.empty()) {
		const std::string line = ":127.0.0.1 461 PASS :Not enough parameters\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	if (this->registered == true) {
		const std::string line = ":127.0.0.1 462 " + this->_nickname + " :You may not reregister\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	if (server._serverPassword != arg[0]) {
		const std::string line = ":127.0.0.1 464 * :Password Incorrect\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	this->passMatch = true;
}


