#ifndef CMDDISPATCH_HPP
#define CMDDISPATCH_HPP
#include <iostream>
#include "User.hpp"
#include <map>

class User;

class cmdDispatch
{
public:
	cmdDispatch(void);
	~cmdDispatch(void);

	void cmdDispatcher(Server &server, User &user, std::string cmd, std::vector<std::string> args);
};
#endif
