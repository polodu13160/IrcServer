#include "../../inc/User.hpp"
#include "Server.hpp"
#include "../../inc/cmdDispatch.hpp"
#include <functional>
#include "../../inc/User.hpp"

void	getTab(std::map<std::string, void (User::*)(Server &, const std::vector<std::string>&)>& functionTab)
{
	functionTab["KICK"] = &User::kickCmd;
	functionTab["INVITE"] = &User::inviteCmd;
	functionTab["TOPIC"] = &User::topicCmd;
	functionTab["MODE"] = &User::modeCmd;
	functionTab["PART"] = &User::partCmd;
	functionTab["NICK"] = &User::nickCmd;
	functionTab["QUIT"] = &User::quitCmd;
	functionTab["JOIN"] = &User::joinCmd;
	functionTab["USER"] = &User::userCmd;
	functionTab["LIST"] = &User::listCmd;
	functionTab["PING"] = &User::pongCmd;
	functionTab["WHO"] = &User::whoCmd;
	functionTab["PRIVMSG"] = &User::privMsgCmd;
	functionTab["NOTICE"] = &User::noticeCmd;
	functionTab["PASS"] = &User::passCmd;
}

// void	cmdSpecialKit(Server &server, User &user, std::string cmd, const std::vector<std::string> args){

// }

void cmdDispatcher(Server &server, User &user, std::string cmd, const std::vector<std::string> args)
{
	if (DEBUG == true) {
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
	}
	std::map<std::string, void (User::*)(Server &, const std::vector<std::string>&)>	functionTab;
	getTab(functionTab);

	if (functionTab.count(cmd))
	{
		void (User::*func)(Server&, const std::vector<std::string>&) = functionTab[cmd];
		(user.*func)(server, args);
	}
	else
	{
		// 421 ERR_UNKNOWNCOMMAND
		std::string	line = ":" + server.getIp()+ " 421 " + user.getNickname() + " " + cmd + " :Unknown command\r\n";
		Server::sendCheck(user.getUserFd(), line.c_str(), line.size(), 0);
	}
}
