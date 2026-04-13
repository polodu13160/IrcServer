#include "../../inc/User.hpp"

// int	wordCountInUser(const std::vector<std::string> &ref) {
//
// 	std::istringstream	tmp(ref);
// 	std::string			params;
// 	int					mode;
//
//
// 	std::string invalidChar = "\0 @\n\r";
//
// 	tmp >> params;
// 	if (params.find_first_of(invalidChar))
// 		return false;
//
// 	// Verif charactere valid [0]
//
// 	// Verif bon int [1]
//
// 	//	Verif Unused + :
//
// 	// Verif REal NAme
// }

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
	// if (wordCountInUser(userName) < 4) {
	// 	const std::string line = "127.0.0.1 461 " + name + "USER :Not enough parameters";
	// 	send(this->_userFd, line.c_str(), line.length(), 0);
	// 	return;
	// }
	this->_username = userName[0];
	const std::string line = "Welcome to the Internet Relay Network " + this->_nickname + "!" + this->_username + "@" + "127.0.0.1";
	send(this->_userFd, line.c_str(), line.length(), 0);


}