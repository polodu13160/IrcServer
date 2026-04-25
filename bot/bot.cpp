#include "bot.hpp"
#include <fcntl.h>
#include <sstream>



Bot::Bot() : _botPassword("123456789") {

}

void Bot::hash(const std::string &str) {

	unsigned long hash = 5381;
	int i = 0;

	while (str[i]) {
		hash = ((hash << 5) + hash) + str[i++];
	}
	hash = hash % 1000;

	// std::cout << "hash de : " << str << " = " << hash << std::endl;

	_insultTable[hash].push_back(str);
}

bool Bot::unhash(const std::string &str) {

	std::stringstream ss(str);
	std::string		word;
	int i = 0;


	if (!str.empty()){
		while (ss >> word ) {
			i = 0;
			unsigned long hash = 5381;
			while (word[i]) {
				hash = ((hash << 5) + hash) + word[i++];
			}
			const unsigned long index = hash % 1000;

			if (_insultTable[index].size() == 1)
				if (*_insultTable[index].begin() == word)
					return true;

			std::list<std::string>::iterator it;
			for (it = _insultTable[index].begin(); it != _insultTable[index].end(); ++it) {
				if (*it == word) {
					std::cout << "Mot trouve : " << *it << std::endl;
					return true;
				}
			}
		}
	}
	return false;
}

void Bot::checkMsg(s_msg &msg) {

	if (unhash(msg.line) == true) {

		std::string channelName = msg.channel;
		std::string userTo = msg.name;
		if (!channelName.empty() && !userTo.empty()) {
			std::string line = "KICK " + channelName + " " + userTo + "\r\n";
			send(this->_botSocket, line.c_str(), line.size(), 0);
		}

		std::ifstream	sixsev("67");

		std::string meme;
		std::string tmp;
		std::string line2 = "PRIVMSG " + msg.name + " :T'ES KICK \r\n";
		send(this->_botSocket, line2.c_str(), line2.size(), 0);

		while (getline(sixsev, tmp)) {
			std::string fullLine = "PRIVMSG " + msg.name + " :" + tmp + "\r\n";
			send(this->_botSocket, fullLine.c_str(), fullLine.size(), 0);
		}
	}
}

s_msg	parseMsg(std::string &handleLine) {

	std::stringstream ss(handleLine);
	std::string tmp;
	s_msg	msg;

	int pos = -1;

	ss >> tmp;
	if (!tmp.empty() && tmp[0] == ':'){
		if ((pos = tmp.find('!')) != std::string::npos) {
			msg.name = tmp.substr(1, pos - 1);
		}
	}
	ss >> tmp;
	ss >> tmp;
	if (!tmp.empty() && tmp[0] == '#')
		msg.channel = tmp.substr(0);

	pos = -1;
	if (getline(ss, tmp)) {
		std::cout << tmp << std::endl;
		if ((pos = tmp.find(':')) != std::string::npos) {
			msg.line = tmp.substr(pos + 1);
		}
	}
	std::cout << "Name = " << msg.name << " Channel = " << msg.channel << " Line = " << msg.line << std::endl;
	return msg;
}


void	Bot::runBot() {

	char buffer[MAX_SIZE_MSG];
	std::string handleLine;

	while (1) {

		std::memset(buffer, 0, MAX_SIZE_MSG);
		size_t	bytes = recv(this->_botSocket, buffer, 1023, 0);
		if (bytes == 0) {
			std::cerr << "Server Disconnected" << std::endl;
			return ;
		}

		std::cout << buffer << std::endl;


		handleLine += buffer;

		size_t index;

		if ((index = handleLine.find("\r\n")) != std::string::npos) {
			s_msg msg = parseMsg(handleLine);
			checkMsg(msg);
		}
		handleLine = "";
	}
}


Bot::Bot(std::ifstream &stream) : _botPassword("123456789"), _serverInfo() {


	this->_botSocket = socket(AF_INET, SOCK_STREAM, 0);

	std::cout << this->_botSocket << std::endl;

	this->_serverInfo.sin_family = AF_INET;
	this->_serverInfo.sin_port = htons(6679);
	this->_serverInfo.sin_addr.s_addr = INADDR_ANY;


	if (connect(this->_botSocket, reinterpret_cast<struct sockaddr*>(&_serverInfo), sizeof(this->_serverInfo)) < 0) {
		std::cerr << "Bot can't connect : Server isn't on" << std::endl;
		return;
	}

	const std::string password(SERVER_PASS);
	const std::string	passLine = "PASS " + password + "\r\n";

	send(this->_botSocket, passLine.c_str(), passLine.size(), 0);

	const std::string botName(BOT_NAME);
	const std::string	nickName = "NICK " + botName + "\r\n";
	send(this->_botSocket, nickName.c_str(), nickName.size(), 0);

	const std::string userName = "USER " + botName + " 0 * :" + botName + "\r\n";

	send(this->_botSocket, userName.c_str(), userName.size(), 0);

	// const std::string join = "JOIN #tutu\r\n";
	// send(this->_botSocket, join.c_str(), join.size(), 0);
	//

	std::string newInsult;

	while (getline(stream, newInsult)) {

		if (newInsult.find('\n')) {

			newInsult = newInsult.erase(newInsult.size());

		}
		hash(newInsult);
	}
	runBot();

}

Bot::Bot(const Bot &other) {
	_botPassword = "123456789";
}

Bot &Bot::operator=(const Bot &other) {
	_botPassword = "123456789";
}

Bot::~Bot() {

}
