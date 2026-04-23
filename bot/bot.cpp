#include "bot.hpp"
#include <fcntl.h>


Bot::Bot() : _botPassword("123456789") {

}


Bot::Bot(std::ifstream &stream) : _botPassword("123456789") {

	std::string line = "salut con test";

	std::string newInsult;

	while (getline(stream, newInsult)) {

		_insult.push_back(newInsult);
	}

}

Bot::Bot(const Bot &other) {
	_botPassword = "123456789";
}

Bot &Bot::operator=(const Bot &other) {
	_botPassword = "123456789";
}

Bot::~Bot() {

}
