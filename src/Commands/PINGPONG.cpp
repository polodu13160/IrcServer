#include "../../inc/User.hpp"


void	User::pongCmd(const std::vector<std::string> &arg) const {

	const std::string line = ":127.0.0.1 PONG 127.0.0.1 " + arg[0] + "\r\n";
	Server::sendCheck(this->_userFd, line.c_str(), line.size(), 0);
}
