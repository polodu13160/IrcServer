#include "User.hpp"


void	User::pongCmd(Server &server, const std::vector<std::string> &arg) {

	const std::string line = ":" + server._ip + " PONG " + server._ip  + " " + arg[0] + "\r\n";
	Server::sendCheck(this->_userFd, line.c_str(), line.size(), 0);
}
