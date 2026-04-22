#include "../../inc/User.hpp"
#include "Server.hpp"
#include "../../inc/cmdPars.hpp"
#include <functional>
#include "../../inc/User.hpp"

cmdPars::cmdPars(void)
{
	this->_handlerTab["KICK"] = &cmdPars::handleKick;
	this->_handlerTab["INVITE"] = &cmdPars::handleInvite;
	this->_handlerTab["TOPIC"] = &cmdPars::handleTopic;
	this->_handlerTab["MODE"] = &cmdPars::handleMode;
	this->_handlerTab["PART"] = &cmdPars::handlePart;
	this->_handlerTab["NICK"] = &cmdPars::handleNick;
	this->_handlerTab["QUIT"] = &cmdPars::handleQuit;
	this->_handlerTab["JOIN"] = &cmdPars::handleJoin;
	this->_handlerTab["HELP"] = &cmdPars::handleHelp;
	this->_handlerTab["USER"] = &cmdPars::handleUser;
	this->_handlerTab["LIST"] = &cmdPars::handleList;
	this->_handlerTab["PING"] = &cmdPars::handlePong;
	this->_handlerTab["WHO"] = &cmdPars::handleWho;
	this->_handlerTab["who"] = &cmdPars::handleWho;
	this->_handlerTab["PRIVMSG"] = &cmdPars::handlePrivmsg;
	this->_handlerTab["NOTICE"] = &cmdPars::handleNotice;
}

cmdPars::~cmdPars() {}

void cmdPars::handlePass(Server &server, User &user, std::vector<std::string> arg)
{
	user.passCmd(server, arg);
}

std::string removeFirstChar(std::vector<std::string> arg, int i)
{
	std::string newStr;

	newStr = arg[i].substr(1, arg[i].size() - 1);
	arg[i] = newStr;
	return "";
}

void cmdPars::handleNotice(Server &server, User &user, std::vector<std::string> arg)
{
	user.noticeCmd(server, arg);
}

void cmdPars::handlePrivmsg(Server &server, User &user, std::vector<std::string> arg)
{
	user.privMsgCmd(server, arg);
}

void cmdPars::handleUser(Server &server, User &user, std::vector<std::string> arg)
{
	user.userCmd(server, arg);
}

void cmdPars::handleWho(Server &server, User &user, std::vector<std::string> arg)
{
	user.whoCmd(server, arg);
}

void cmdPars::handleInvite(Server &server, User &user, std::vector<std::string> arg)
{
	user.inviteCmd(server, arg);
}

void cmdPars::handleKick(Server &server, User &user, std::vector<std::string> arg)
{
	user.kickCmd(server,arg);
}

void cmdPars::handleMode(Server &server, User &user, std::vector<std::string> arg)
{
	user.modeCmd(server, arg);
}

void cmdPars::handlePong(Server &server, User &user, std::vector<std::string> arg)
{
	(void)server;
	user.pongCmd(arg);
}

void cmdPars::handleTopic(Server &server, User &user, std::vector<std::string> arg)
{
	user.topicCmd(server, arg);
}

void cmdPars::handleList(Server &server, User &user, std::vector<std::string> arg)
{
	user.listCmd(server, arg);
}

void cmdPars::handlePart(Server &server, User &user, std::vector<std::string> arg)
{
	user.partCmd(server,arg);
}

void cmdPars::handleNick(Server &server, User &user, std::vector<std::string> arg)
{
	user.nickCmd(server, arg);
}

void cmdPars::handleQuit(Server &server, User &user, std::vector<std::string> arg)
{
	user.quitCmd(server, arg);
}

void cmdPars::handleJoin(Server &server, User &user, std::vector<std::string> arg)
{
	user.joinCmd(server, arg);
}

void cmdPars::handleHelp(Server &server, User &user, std::vector<std::string> arg)
{
	(void)user;
	(void)server;
	// HELP [cmd]
	if (!arg[0].empty())
	{
		// aide sur cmd arg[0]
		std::cout << "[How to use] [cmd]" << arg[0] << std::endl;
	}
	else
	{
		// liste des commandes
		std::cout << "[CMDLIST]" << std::endl;
	}
}

void cmdPars::cmdParser(Server &server, User &user, std::string cmd, std::vector<std::string> args)
{
	std::cout << "cmd : " << cmd << std::endl;
	if (args.size() > 0)
	{
		for (size_t i = 0; i < args.size(); i++)
		{
			std::cout << "args : " << i << " : " << args[i].c_str() << std::endl;
		}
		std::cout << "user : " << " : " << user.getNickname() << std::endl;
	}
	std::cout << "-------------------------------------------------------------" << std::endl;


	std::map<std::string, void (cmdPars::*)(Server &, User &, std::vector<std::string>)>::iterator it = this->_handlerTab.find(cmd);
	if (it != this->_handlerTab.end())
	{
		(this->*(it->second))(server, user, args);
	}
	else
	{
		// std::cout << "This command does not exist here" << std::endl;
	}
}
