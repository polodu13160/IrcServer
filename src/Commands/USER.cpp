#include "../../inc/User.hpp"

int	wordCountInUser(const std::vector<std::string> &ref) {

	std::string			params;


	std::string invalidChar = "\0 @\n\r";

	if (ref[0].find_first_of(invalidChar))
		return false;

	std::istringstream ss(ref[1]);
	std::string	garbage;
	int					mode;

	if (!(ss >> mode) || (ss >> garbage))
		return false;
	else if (checkMode)

	// Verif bon int [1]

	//	Verif Unused + :

	// Verif REal NAme
}

void	User::userCmd(Server& server, const std::vector<std::string>& userName) {

	(void)server;
	std::string name = this->_nickname;
	if (name.empty())
		name = "*";

	if (this->registered == true) {
		const std::string line = ":127.0.0.1 462 " + name + " :Unauthorized command (already registered)";
		send(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	if (wordCountInUser(userName) < 4) {
		const std::string line = "127.0.0.1 461 " + name + "USER :Not enough parameters";
		send(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	this->_username = userName[0];
	std::string line =  ":127.0.0.1 001 " + this->_nickname + " :Welcome to the Internet Relay Network\r\n";
	send(this->_userFd, line.c_str(), line.length(), 0);
	line = ":127.0.0.1 002 " + this->_nickname + " :Your host is 127.0.0.1, tunning version 0.1\r\n";
	send(this->_userFd, line.c_str(), line.length(), 0);
	line = ":127.0.0.1 003 " + this->_nickname + " :This Server was created the 13 April 2027\r\n";
	send(this->_userFd, line.c_str(), line.length(), 0);
	line = ":127.0.0.1 004 " + this->_nickname + " 127.0.0.1 1.0 o i\r\n";
	send(this->_userFd, line.c_str(), line.length(), 0);
	line = ":127.0.0.1 375 " + this->_nickname + " :- 127.0.0.1 Message of the day - \r\n";
	send(this->_userFd, line.c_str(), line.length(), 0);
	line = ":127.0.0.1 372 " + this->_nickname + " :- WELCOME LES BB ! \r\n";
	send(this->_userFd, line.c_str(), line.length(), 0);
	line = ":127.0.0.1 376 " + this->_nickname + " :End of MOTD command\r\n";
	send(this->_userFd, line.c_str(), line.length(), 0);


}