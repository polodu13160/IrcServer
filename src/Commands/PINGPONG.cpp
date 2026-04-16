#include "../../inc/User.hpp"


void	User::pongCmd(const std::vector<std::string> &arg) const {

	const std::string line = "PONG " + arg[0] + "\r\n";
	send(this->_userFd, line.c_str(), line.size(), 0);
}
