#include "cmd.hpp"

cmd::cmd(void){
	this->_cmdMap["KICK"] = &cmd::kick;
	this->_cmdMap["INVITE"] = &cmd::invite;
	this->_cmdMap["TOPIC"] = &cmd::topic;
	this->_cmdMap["MODE"] = &cmd::mode;
}

void	cmd::kick(void){
	std::cout << "user has been kicked" <<std::endl;
}

void	cmd::invite(void){
	std::cout << "user has been invited" <<std::endl;
}

void	cmd::topic(void){
	std::cout << "user changed topic" <<std::endl;
}

void	cmd::mode(void){
	std::cout << "mode activated" <<std::endl;
}

void	cmd::join(void){
	std::cout << "user has joined [channel]" <<std::endl;
}

void	cmd::part(void){
	std::cout << "user left [channel]" <<std::endl;
}

void	cmd::msg(void){
	std::cout << "user sent a message" <<std::endl;
}

void	cmd::nick(User &user, std::string nickname){
	user.setNickname(nickname);
	std::cout << "user changed nickname to " << nickname << std::endl;
}

void	cmd::quit(void){
	std::cout << "user left the server" <<std::endl;
}

void	cmd::help(void){
	std::cout << "[help]" <<std::endl;
}
