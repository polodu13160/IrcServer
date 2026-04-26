#include "../../inc/User.hpp"
#include <bitset>

bool checkAndSetMode(int mode, unsigned int &refUserMode)
{

	if (mode < 0)
		return false;
	std::bitset<32> checkMode(mode);
	std::bitset<32> reelMode(refUserMode);

	for (size_t i = 0; i < checkMode.size(); i++)
	{
		if (checkMode.test(i))
			reelMode.set(i);
	}
	refUserMode = static_cast<u_int32_t>(reelMode.to_ulong());
#if (DEBUG == 1)
// std::cout << "Mode passé = " << mode << " Mode du user = " << refUserMode << std::endl;
#endif // DEBUG

	return true;
}

int wordCountInUser(const std::vector<std::string> &ref, unsigned int &refUserMode)
{

	std::string params;

	std::string invalidChar = " @\n\r";

	if (ref[0].find_first_of(invalidChar) != std::string::npos)
	{

		return false;
	}
	std::istringstream ss(ref[1]);
	std::string garbage;
	int mode;

	if (!(ss >> mode) || !checkAndSetMode(mode, refUserMode))
		return false;

	//	Verif Unused + :

	// Verif REal NAme
	return 4;
}

void User::userCmd(Server &server, const std::vector<std::string> &userName)
{

	std::string name = this->_nickname;
	if (name.empty())
		name = "*";
	if (this->registered == true)
	{
		const std::string line = ":" + server._ip + " 462 " + name + " :Unauthorized command (already registered) \r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	if (wordCountInUser(userName, this->_userMode) < 4)
	{
		const std::string line = ":" + server._ip + " 461 " + name + "USER :Not enough parameters \r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	this->_realname = "caca";
	this->_username = userName[0];
	setUserRegistration(server);
}
