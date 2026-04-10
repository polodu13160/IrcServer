#include "User.hpp"
#include "cmdPars.hpp"

cmdPars::cmdPars(void){
	this->_handlerTab["KICK"] = &cmdPars::handleKick;
	this->_handlerTab["INVITE"] = &cmdPars::handleInvite;
	this->_handlerTab["TOPIC"] = &cmdPars::handleTopic;
	this->_handlerTab["MODE"] = &cmdPars::handleMode;
}

void	cmdPars::handleInvite(std::string *arg){
	// INVITE (nickname) (channel)
	if(arg[1].empty()){
		std::cout << "There must be 2 parameters for this command" << std::endl;
	}
	if(arg[1][0] != '#'){
		std::cout << "Channel name must begin with '#'" << std::endl;
	}

}

void	cmdPars::handleKick(std::string *arg){
	// KICK (channel) (nickname) [comment]
	if(arg[1].empty()){
		std::cout << "There must be 2 or 3 parameters for this command" << std::endl;
	}
	if(arg[0][0] != '#'){
		std::cout << "Channel name must begin with '#'" << std::endl;
	}
}

void	cmdPars::handleMode(std::string *arg){
	// MODE (channel/user) (mode : -i, -o...) (param)
	if(arg[1].empty()){
		std::cout << "There must be 2 or 3 parameters for this command" << std::endl;
	}
	if(arg[0][0] == '#'){
		//channel
	}
	else{
		//user
	}
}

void	cmdPars::handleTopic(std::string *arg){
	// TOPIC (channel) [newchannel]
	if(arg[0].empty()){
		std::cout << "There must be 1 or 2 parameters for this command" << std::endl;
	}
	if(arg[0][0] != '#'){
		std::cout << "Channel name must begin with '#'" << std::endl;
	}
	if(arg[1].empty()){
		// voir le topic
	}
	else{
		 // changer topic par arg[1]
		 if(arg[1][0] != '#'){
		std::cout << "Channel name must begin with '#'" << std::endl;
	}
	}
}

void	cmdPars::cmdParser(std::string cmd){
	std::map<std::string, void (cmdPars::*)(std::string*)>::iterator it = this->_handlerTab.find(cmd);
	if(it != this->_handlerTab.end()){
	}
}
