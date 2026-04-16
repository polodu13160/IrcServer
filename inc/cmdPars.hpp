#ifndef CMDPARS_HPP
#define CMDPARS_HPP
#include <iostream>
#include "User.hpp"
#include <map>

class User;

class cmdPars
{
public:
	cmdPars(void);
	~cmdPars(void);

	void cmdParser(Server &server, User &user, std::string cmd, std::vector<std::string> args);

	std::map<std::string, void (cmdPars::*)(Server &, User &, std::vector<std::string>)> _handlerTab;

	void handleKick(Server &server, User &user, std::vector<std::string> args);
	void handleMode(Server &server, User &user, std::vector<std::string> args);
	void handleInvite(Server &server, User &user, std::vector<std::string> args);
	void handleTopic(Server &server, User &user, std::vector<std::string> args);
	void handlePart(Server &server, User &user, std::vector<std::string> args);
	void handleNick(Server &server, User &user, std::vector<std::string> args);
	void handleQuit(Server &server, User &user, std::vector<std::string> args);
	void handleJoin(Server &server, User &user, std::vector<std::string> args);
	void handleHelp(Server &server, User &user, std::vector<std::string> args);
	void handleUser(Server &server, User &user, std::vector<std::string> arg);
	void handleList(Server &server, User &user, std::vector<std::string> arg);
	void handlePass(Server &server, User &user, std::vector<std::string> arg);
};
#endif
