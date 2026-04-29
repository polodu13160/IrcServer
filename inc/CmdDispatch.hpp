#ifndef CMDDISPATCH_HPP
#define CMDDISPATCH_HPP
#include "User.hpp"


class User;

namespace CmdDispatch
{
	void cmdDispatcher(Server &server, User &user, std::string cmd, std::vector<std::string> args);
};
#endif
