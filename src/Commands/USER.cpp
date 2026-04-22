#include "../../inc/User.hpp"
#include <bitset>

bool	checkAndSetMode(int mode, unsigned int &refUserMode) {

	if (mode < 0)
		return false;
	std::bitset<32>	checkMode(mode);
	std::bitset<32>	reelMode(refUserMode);

	for (size_t i = 0; i < checkMode.size() ; i++) {
		if (checkMode.test(i))
			reelMode.set(i);
	}
	refUserMode = static_cast<u_int32_t>(reelMode.to_ulong());
	#if (DEBUG==1)
	// std::cout << "Mode passé = " << mode << " Mode du user = " << refUserMode << std::endl;
	#endif //DEBUG

	return true;
}


int	wordCountInUser(const std::vector<std::string> &ref, unsigned int &refUserMode) {

	std::string			params;


	std::string invalidChar = " @\n\r";

	if (ref[0].find_first_of(invalidChar) != std::string::npos) {

		return false;
	}
	std::istringstream ss(ref[1]);
	std::string	garbage;
	int					mode;

	if (!(ss >> mode) || !checkAndSetMode(mode, refUserMode))
		return false;

	//	Verif Unused + :

	// Verif REal NAme
	return 4;
}

void	User::userCmd(Server& server, const std::vector<std::string>& userName) {

	(void)server;
	std::string name = this->_nickname;
	if (name.empty())
		name = "*";
	if (this->registered == true) {
		const std::string line = ":127.0.0.1 462 " + name + " :Unauthorized command (already registered)";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	// std::cout << "LA " << std::endl;
	if (wordCountInUser(userName, this->_userMode) < 4) {
		const std::string line = "127.0.0.1 461 " + name + "USER :Not enough parameters";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	this->_username = userName[0];
	std::string line =  ":127.0.0.1 001 " + this->_nickname + " :Welcome to the Internet Relay Network\r\n";
	Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
	line = ":127.0.0.1 002 " + this->_nickname + " :Your host is 127.0.0.1, tunning version 0.1\r\n";
	Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
	line = ":127.0.0.1 003 " + this->_nickname + " :This Server was created the 13 April 2027\r\n";
	Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
	line = ":127.0.0.1 004 " + this->_nickname + " 127.0.0.1 1.0 o i\r\n";
	Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
	line = ":127.0.0.1 375 " + this->_nickname + " :- 127.0.0.1 Message of the day - \r\n";
	Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
	line = ":127.0.0.1 372 " + this->_nickname + " :- WELCOME LES BB ! \r\n";
	Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
	line = ":127.0.0.1 376 " + this->_nickname + " :End of MOTD command\r\n";
	Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);


}
