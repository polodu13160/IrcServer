#include "../MessageParsing/User.hpp"

int	wordCount(const std::string &ref) {
	std::istringstream ss(ref);
	std::string garbage;
	int wordCount = 0;

	while (ss >> garbage)
		wordCount++;
	return wordCount;
}

void	User::userCmd(Server& server, const std::string& userName) {

	std::string name = this->_nickname;
	if (name.empty())
		name = "*";

	if (this->registered == true) {
		const std::string line = ":127.0.0.1 462 " + name + " :Unauthorized command (already registered)";
		send(this->_userFd, line.c_str(), line.length(), 0);
		return;
	}
	if (wordCount(userName) != 4) {
		const std::string line = "127.0.0.1 461 " + name + "USER :"
	}
}