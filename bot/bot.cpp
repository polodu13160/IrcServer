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

void Bot::unhash(const std::string &str) {



	std::stringstream ss(str);
	std::string		word;
	int i = 0;


	while (ss >> word ) {

		i = 0;
		unsigned long hash = 5381;
		while (word[i]) {
			hash = ((hash << 5) + hash) + word[i++];
		}

		const unsigned long index = hash % 1000;

		// std::cout << "hash de : " << word << " = " << index << std::endl;

		std::list<std::string>::iterator it;

		for (it = _insultTable[index].begin(); it != _insultTable[index].end(); ++it) {

			if (*it == word) {
				std::cout << "Mot trouve : " << *it << std::endl;
				break;
			}
		}

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
	std::string	passLine = "PASS " + password + "\r\n";

	send(this->_botSocket, passLine.c_str(), passLine.size(), 0);

	const std::string botName(BOT_NAME);
	std::string	nickName = "NICK " + botName + "\r\n";
	send(this->_botSocket, nickName.c_str(), nickName.size(), 0);

	std::string userName = "USER " + botName + " 0 * :" + botName + "\r\n";

	send(this->_botSocket, userName.c_str(), userName.size(), 0);


	std::string newInsult;

	while (getline(stream, newInsult)) {

		if (newInsult.find('\n')) {

			newInsult = newInsult.erase(newInsult.size());

		}
		hash(newInsult);
	}

	std::string tmp = "Salut connard espece de con sale fdp";


	unhash(tmp);

	while (1);
}

Bot::Bot(const Bot &other) {
	_botPassword = "123456789";
}

Bot &Bot::operator=(const Bot &other) {
	_botPassword = "123456789";
}

Bot::~Bot() {

}
