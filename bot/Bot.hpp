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
#include <exception>

struct s_msg {
	std::string name;
	std::string channel;
	std::string line;
};


#define SERVER_PASS "tete"
#define	BOT_NAME "bot"
#define MAX_SIZE_MSG 1024

class Bot {
public:

	Bot();
	void hash(const std::string &str);
	bool unhash(const std::string &str);
	void checkMsg(const s_msg &msg);
	void runBot();

	void init();

	static void sendMsg(const int fd, const char *str, const size_t size, const int flag);

	Bot(const Bot &other);
	Bot& operator=(const Bot &other);
	~Bot();


	class errorBadFile : public std::exception {
		virtual const char *what(void)const throw();
	};

	class errorSocket : public std::exception {
		virtual const char *what(void)const throw();
	};

	class errorConnect : public std::exception {
		virtual const char *what(void)const throw();
	};

	class errorSend : public std::exception {
		virtual const char *what(void)const throw();
	};


private :
	std::string					_botPassword;
	std::list<std::string>      _insultTable[1000];
	std::vector<std::string>	_sixseven;
	int							_botSocket;
	sockaddr_in					_serverInfo;


};


#endif
