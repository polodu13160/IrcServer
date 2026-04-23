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


Bot::Bot(std::ifstream &stream) : _botPassword("123456789") {

	std::string newInsult;

	while (getline(stream, newInsult)) {

		if (newInsult.find('\n')) {

			newInsult = newInsult.erase(newInsult.size());

		}
		hash(newInsult);
	}

	std::string tmp = "Salut connard espece de con sale fdp";

	unhash(tmp);
}

Bot::Bot(const Bot &other) {
	_botPassword = "123456789";
}

Bot &Bot::operator=(const Bot &other) {
	_botPassword = "123456789";
}

Bot::~Bot() {

}
