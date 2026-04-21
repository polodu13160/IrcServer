#include "../../inc/User.hpp"
#include "Server.hpp"
#include "../../inc/cmdPars.hpp"
#include <functional>
#include "../../inc/User.hpp"

cmdPars::cmdPars(void){
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
	this->_handlerTab["PRIVMSG"] = &cmdPars::handlePrivmsg;
	this->_handlerTab["NOTICE"] = &cmdPars::handleNotice;
}

cmdPars::~cmdPars(){}

std::string	removeFirstChar(std::vector<std::string> arg, int i){
	std::string newStr;

	newStr = arg[i].substr(1, arg[i].size() - 1);
	arg[i] = newStr;
	return "";
}

void	cmdPars::handleNotice(Server &server, User &user, std::vector<std::string> arg){
	user.noticeCmd(server, arg);
}

void	cmdPars::handlePrivmsg(Server &server, User &user, std::vector<std::string> arg){
	user.privMsgCmd(server, arg);
}

void	cmdPars::handleUser(Server &server, User &user, std::vector<std::string> arg){
	if(arg[0].empty()){
		std::cout << "There must be at least 1 parameter for this command" << std::endl;
		return;
	}
	user.userCmd(server, arg);
}

void	cmdPars::handleWho(Server &server, User &user, std::vector<std::string> arg){
	user.whoCmd(server, arg);
}

void	cmdPars::handleInvite(Server &server, User &user, std::vector<std::string> arg){
	// INVITE (nickname) (channel)
	(void)user;
	(void)server;
	if(arg[1].empty()){
		std::cout << "There must be 2 parameters for this command" << std::endl;
		return;
	}
	if(arg[1][0] != '#'){
		std::cout << "Channel name must begin with '#'" << std::endl;
		return;
	}
	removeFirstChar(arg, 1);
	// arg[0] rejoint le channel arg[1]
	std::cout << arg[0] << " has joined " << arg[1] << std::endl;
}

void	cmdPars::handleKick(Server &server, User &user, std::vector<std::string> arg){
	(void)user;
	(void)server;
	// KICK (channel) (nickname) [comment]
	if(arg.empty() || arg[1].empty()){
		std::cout << "There must be 2 or 3 parameters for this command" << std::endl;
		return;
	}
	if(arg[0][0] != '#'){
		std::cout << "Channel name must begin with '#'" << std::endl;
		return;
	}
	removeFirstChar(arg, 0);
	// kick arg[1] de channel arg[0] en laissant un message arg[2]
	std::cout << arg[1] << " has been kicked of channel " << arg[0] << std::endl;
	if(!arg[2].empty())
		std::cout << arg[2] << std::endl;
}

void	cmdPars::handleMode(Server &server, User &user, std::vector<std::string> arg){
	user.modeCmd(server, arg);
}

void cmdPars::handlePong(Server &server, User &user, std::vector<std::string> arg)
{
	(void)server;
	(void)user;
	user.pongCmd(arg);
}

void	cmdPars::handleTopic(Server &server, User &user, std::vector<std::string> arg){
	user.topicCmd(server, arg);
}

void cmdPars::handleList(Server &server, User &user, std::vector<std::string> arg)
{
	user.listCmd(server,arg);
}

void	cmdPars::handlePart(Server &server, User &user, std::vector<std::string> arg){
	(void)user;
	(void)server;
	// PART (channel) [channel] ...
	if(arg[0].empty()){
		std::cout << "There must be at least 1 parameter for this command" << std::endl;
		return;
	}
	for(int i = 0; i < 15 && !arg[i].empty(); i++){
		if(arg[i][0] != '#'){
			std::cout << "Channel name must begin with '#'" << std::endl;
			return;
		}
		removeFirstChar(arg, i);
		// partir du channel arg[i]
		std::cout << "[User] has left channel " << arg[i] << std::endl;
	}
}

void	cmdPars::handleNick(Server &server, User &user, std::vector<std::string> arg){
	(void)user;
	// NICK (new nickname)
	if(arg[0].empty()){
		std::cout << "There must be 1 parameter for this command" << std::endl;
		return;
	}
	// changer nickname
	user.nickCmd(server, arg);
}

void	cmdPars::handleQuit(Server &server, User &user, std::vector<std::string> arg){
	(void)arg;

	user.quitCmd(server);
}

void	cmdPars::handleJoin(Server &server, User &user, std::vector<std::string> arg){
	(void)user;
	//JOIN (channel) [mdp]
	// Server::messageToServer(arg[0].c_str(), NULL);
	user.joinCmd(server, arg);
}

void	cmdPars::handleHelp(Server &server, User &user, std::vector<std::string> arg){
	(void)user;
	(void)server;
	// HELP [cmd]
	if(!arg[0].empty()){
		// aide sur cmd arg[0]
		std::cout << "[How to use] [cmd]" << arg[0] << std::endl;

	}
	else{
		//liste des commandes
		std::cout << "[CMDLIST]" << std::endl;
	}
}

void	cmdPars::cmdParser(Server &server, User &user, std::string cmd, std::vector<std::string> args){
	std::cout << "cmd : " << cmd << std::endl;
	std::map<std::string, void (cmdPars::*)(Server&, User&, std::vector<std::string>)>::iterator it = this->_handlerTab.find(cmd);
	if(it != this->_handlerTab.end()){
		(this->*(it->second))(server, user, args);
	}
	else{
		std::cout << "This command does not exist here" << std::endl;
	}
}


