#ifndef BOT_CPP
#define BOT_CPP


#include <fstream>
#include <vector>
#include <list>
#include <iostream>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_PASS "67"
#define	BOT_NAME "bot"
#define MAX_SIZE_MSG 1024

class Bot {
public:

	Bot();

	void hash(const std::string &str);

	bool unhash(const std::string &str);

	void checkMsg(std::string &msg);

	void runBot();

	Bot(std::ifstream &stream);
	Bot(const Bot &other);
	Bot& operator=(const Bot &other);
	~Bot();


private :
	std::string					_botPassword;
	std::list<std::string>      _insultTable[1000];
	int							_botSocket;
	sockaddr_in					_serverInfo;


};


#endif
