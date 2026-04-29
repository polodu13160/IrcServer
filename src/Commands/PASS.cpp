#include "User.hpp"

bool	User::checkRegistration(Server &server) const {

	if (this->registered == false) {
		const std::string line = ":" + server.getIp() + " 451 : You have not registered.\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		return false;
	}
	return true;
}

void	User::passCmd(Server &server, const std::vector<std::string> &arg) {

	if (arg.empty()) {
		const std::string line = ":" + server.getIp() + " 461 PASS :Not enough parameters\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		std::cout << "La" << std::endl;
		return;
	}
	if (this->registered == true) {
		const std::string line = ":" + server.getIp() + " 462 " + this->_nickname + " :You may not reregister\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	if (server._serverPassword != arg[0]) {
		const std::string line = ":" + server.getIp() + " 464 * :Password Incorrect\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	#if (DEBUG==1) 
	 	std::cout << "ici" << std::endl;
	#endif //DEBUG
	
	this->passMatch = true;
}


