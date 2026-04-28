#include "../../inc/User.hpp"
#include <bitset>

int wordCountInUser(const std::vector<std::string> &ref, User &thisUsr)
{
	if (ref.size() != 4)
		return 0;

	const std::string invalidChar(" @\n\r\0", 5);

	if (ref[0].empty() || ref[0].size() > 10 || ref[0].find_first_of(invalidChar) != std::string::npos)
		return 0;
	thisUsr.setUsername(ref[0]);
	if (ref[1].size() != 1 || ref[1][0] != '0')
		return 0;
	if (ref[2].size() != 1 || ref[2][0] != '*')
		return 0;
	if (ref[3].empty() || ref[3][0] != ':' || ref[3].size() < 2)
		return 0;
	thisUsr.setRealname(ref[3].substr(1));
	return 4;
}

void User::userCmd(Server &server, const std::vector<std::string> &userName)
{

	if (this->passMatch == false) {

		const std::string line = ":" + server.getIp() + " 431 * :Can't connect without password\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	std::string name = this->_nickname;
	if (name.empty())
		name = "*";
	if (this->registered == true)
	{
		const std::string line = ":" + server._ip + " 462 " + name + " :Unauthorized command (already registered) \r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	if (wordCountInUser(userName, *this) < 4)
	{
		const std::string line = ":" + server._ip + " 461 " + name + " USER :Not enough parameters \r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	setUserRegistration(server);
}
