#ifndef BOT_CPP
#define BOT_CPP


#include <fstream>
#include <vector>
#include <list>
#include <iostream>

class Bot {
public:

	Bot();

	void hash(const std::string &str);

	void unhash(const std::string &str);

	Bot(std::ifstream &stream);
	Bot(const Bot &other);
	Bot& operator=(const Bot &other);
	~Bot();


private :
	std::string					_botPassword;
	std::list<std::string>      _insultTable[1000];

};


#endif
