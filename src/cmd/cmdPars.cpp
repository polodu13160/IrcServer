#include "../MessageParsing/User.hpp"
#include "../MessageParsing/cmdPars.hpp"
#include <functional>

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
}

cmdPars::~cmdPars(){}

std::string	removeChannelHashtag(std::string *arg, int i){
	std::string newStr;

	newStr = arg[i].substr(1, arg[i].size() - 1);
	arg[i] = newStr;
}

void	cmdPars::handleInvite(User &user, std::string *arg){
	// INVITE (nickname) (channel)
	if(arg[1].empty()){
		std::cout << "There must be 2 parameters for this command" << std::endl;
		return;
	}
	if(arg[1][0] != '#'){
		std::cout << "Channel name must begin with '#'" << std::endl;
		return;
	}
	removeChannelHashtag(arg, 1);
	// arg[0] rejoint le channel arg[1]
	std::cout << arg[0] << " has joined " << arg[1] << std::endl;
}

void	cmdPars::handleKick(User &user, std::string *arg){
	// KICK (channel) (nickname) [comment]
	if(!arg || arg[1].empty()){
		std::cout << "There must be 2 or 3 parameters for this command" << std::endl;
		return;
	}
	if(arg[0][0] != '#'){
		std::cout << "Channel name must begin with '#'" << std::endl;
		return;
	}
	removeChannelHashtag(arg, 0);
	// kick arg[1] de channel arg[0] en laissant un message arg[2]
	std::cout << arg[1] << " has been kicked of channel " << arg[0] << std::endl;
	if(!arg[2].empty())
		std::cout << arg[2] << std::endl;
}

void	cmdPars::handleMode(User &user, std::string *arg){
	// MODE (channel/user) (mode : -i, -o...) (param)
	if(arg[1].empty()){
		std::cout << "There must be 2 or 3 parameters for this command" << std::endl;
		return;
	}
	if(arg[0][0] == '#'){
		if(arg[1][0] != '+' && arg[1][0] != '-')
			std::cout << "Second parameter must begin with '+' or '-' (set/remove)" << std::endl;
		else if(arg[1][1] != 'i' && arg[1][1] != 't' && arg[1][1] != 'k' && arg[1][1] != 'o' && arg[1][1] != 'l')
			std::cout << "available modes : -i, -t, -k, -o, -l" << std::endl;
		else{
			removeChannelHashtag(arg, 0);
			// exec MODE
		}
	}
	else{
		std::cout << "First parameter must be a channel beginning with '#'" << std::endl;
	}
}

void	cmdPars::handleTopic(User &user, std::string *arg){
	// TOPIC (channel) [newtopic]
	if(arg[0].empty()){
		std::cout << "There must be 1 or 2 parameters for this command" << std::endl;
		return;
	}
	if(arg[0][0] != '#'){
		std::cout << "Channel name must begin with '#'" << std::endl;
		return;
	}
	removeChannelHashtag(arg, 0);
	if(arg[1].empty()){
		// voir le topic
		std::cout << "[Topic Name]" << std::endl;
	}
	else{
		 // changer topic par arg[1]
		std::cout << arg[0] << " topic [Current topic name] has changed to " << arg[1] << std::endl;
	}
}

void	cmdPars::handlePart(User &user, std::string *arg){
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
		removeChannelHashtag(arg, i);
		// partir du channel arg[i]
		std::cout << "[User] has left channel " << arg[i] << std::endl;
	}
}

void	cmdPars::handleNick(User &user, std::string *arg){
	// NICK (new nickname)
	if(arg[0].empty()){
		std::cout << "There must be 1 parameter for this command" << std::endl;
		return;
	}
	// changer nickname
	std::cout << "[User] has changed nickname to " << arg[0] << std::endl;
}

void	cmdPars::handleQuit(User &user, std::string *arg){
	// QUIT [message]
	if(!arg[0].empty()){
		// laisse un message de depart arg[0]
		std::cout << arg[0] << std::endl;
	}
	//quitte IRC
	std::cout << "[User] has left the server" << std::endl;
}

void	cmdPars::handleJoin(User &user, std::string *arg){
	//JOIN (channel) [mdp]
	if(arg[0].empty()){
		std::cout << "There must be 1 or 2 parameters for this command" << std::endl;
		return;
	}
	removeChannelHashtag(arg, 0);
	// check si mdp
	// si channel non existant : nouveau channel avec : user=>operateur du channel
	std::cout << "[User] has joined " << arg[0] << std::endl;
}

void	cmdPars::handleHelp(User &user, std::string *arg){
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

void	cmdPars::cmdParser(User &user, std::string cmd, std::string *args){
	std::map<std::string, void (cmdPars::*)(User&, std::string*)>::iterator it = this->_handlerTab.find(cmd);
	if(it != this->_handlerTab.end()){
		(this->*(it->second))(user, args);
	}
	else{
		std::cout << "This command does not exist here" << std::endl;
	}
}


