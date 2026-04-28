#include "Bot.hpp"
#include "Bot.hpp"
#include <fcntl.h>
#include <sstream>



void Bot::sendMsg(const int fd, const char *str, const size_t size, const int flag) {
	if (send(fd, str, size, flag) == -1)
		throw Bot::errorSend();
}

void Bot::hash(const std::string &str) {

	unsigned long hash = 5381;
	int i = 0;

	while (str[i]) {
		hash = ((hash << 5) + hash) + str[i++];
	}
	hash = hash % 1000;
	_insultTable[hash].push_back(str);
}

bool Bot::unhash(const std::string &str) {

	std::stringstream ss(str);


	if (!str.empty()) {
		int i = 0;
		std::string word;
		while (ss >> word ) {
			i = 0;
			unsigned long hash = 5381;
			while (word[i]) {
				word[i] = std::tolower(word[i]);
				hash = ((hash << 5) + hash) + word[i++];
			}
			const unsigned long index = hash % 1000;

			if (_insultTable[index].size() == 1)
				if (*_insultTable[index].begin() == word)
					return true;

			std::list<std::string>::iterator it;
			for (it = _insultTable[index].begin(); it != _insultTable[index].end(); ++it) {
				if (*it == word) {
					return true;
				}
			}
		}
	}
	return false;
}

void Bot::checkMsg(const s_msg &msg) {

	if (unhash(msg.line) == true) {

		if (!msg.channel.empty() && !msg.name.empty()) {
			 std::string line = "KICK " + msg.channel + " " + msg.name + "\r\n";
			sendMsg(this->_botSocket, line.c_str(), line.size(), 0);
			line = "PRIVMSG " + msg.name + " :You've been kicked from channel " + msg.channel + " \r\n";
			sendMsg(this->_botSocket, line.c_str(), line.size(), 0);

			for (std::vector<std::string>::iterator it = this->_sixseven.begin(); it != this->_sixseven.end(); ++it) {
				line = "PRIVMSG " + msg.name + " " + *it + "\r\n";
				sendMsg(this->_botSocket, line.c_str(), line.size(), 0);
			}
		}
		else {
			std::cerr << "Error\nBad information provided" << std::endl;
		}
	}
}

s_msg	parseMsg(std::string &handleLine) {

	std::stringstream ss(handleLine);
	std::string tmp;
	s_msg	msg;

	size_t pos = 0;

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

	pos = 0;
	if (getline(ss, tmp)) {
		if ((pos = tmp.find(':')) != std::string::npos) {
			msg.line = tmp.substr(pos + 1);
		}
	}
	return msg;
}


void	Bot::runBot() {

	char buffer[MAX_SIZE_MSG];
	std::string handleLine;

	while (true) {

		std::memset(buffer, 0, MAX_SIZE_MSG);
		size_t	bytes = recv(this->_botSocket, buffer, 1023, 0);
		if (bytes == 0) {
			std::cerr << "Server Disconnected" << std::endl;
			return ;
		}
		handleLine += buffer;

		size_t index;

		if ((index = handleLine.find("\r\n")) != std::string::npos) {
			s_msg msg = parseMsg(handleLine);
			checkMsg(msg);
		}
		handleLine = "";
	}
}

void Bot::init() {

	this->_botSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_botSocket < 0)
		throw Bot::errorSocket();
	this->_serverInfo.sin_family = AF_INET;
	this->_serverInfo.sin_port = htons(SERVER_PORT);
	this->_serverInfo.sin_addr.s_addr = INADDR_ANY;

	if (connect(this->_botSocket, reinterpret_cast<struct sockaddr*>(&_serverInfo), sizeof(this->_serverInfo)) < 0)
		throw Bot::errorConnect();

	const std::string password(SERVER_PASS);
	const std::string	passLine = "PASS " + password + "\r\n";

	sendMsg(this->_botSocket, passLine.c_str(), passLine.size(), 0);

	const std::string botName(BOT_NAME);
	const std::string	nickName = "NICK " + botName + "\r\n";
	sendMsg(this->_botSocket, nickName.c_str(), nickName.size(), 0);

	const std::string userName = "USER " + botName + " 0 * :" + botName + "\r\n";

	sendMsg(this->_botSocket, userName.c_str(), userName.size(), 0);

	std::ifstream stream("bot/insult");
	if (!stream.is_open()) {
		std::cerr << "Error opening the file" << std::endl;
		throw Bot::errorBadFile();
	}
	std::string newInsult;
	while (getline(stream, newInsult)){
		if (newInsult.find('\n'))
			newInsult = newInsult.erase(newInsult.size());
		hash(newInsult);
	}

	std::ifstream	meme("bot/botResponse");
	if (!meme.is_open()) {
		stream.close();
		throw Bot::errorBadFile();
	}
	std::string tmp;
	while (getline(meme, tmp)) {
		this->_sixseven.push_back(tmp);
	}

	meme.close();
	stream.close();
}


Bot::Bot() : _botPassword("123456789"), _botSocket(-1), _serverInfo() {

}

Bot::~Bot() {
	close(this->_botSocket);
}


