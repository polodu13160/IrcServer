#include "User.hpp"

// :expediteur!Username@Host PRIVMSG <target> :message\r\n
// 411 ERR_NORECIPIENT		412 ERR_NOTEXTTOSEND
// 401 ERR_NOSUCHNICK		404 ERR_CANNOTSENDTOCHAN

// PRIVMSG <target> <message>

void	User::privMsgCmd(Server &server, std::vector<std::string> arg){
	if(arg.size() < 1){
		// 411 ERR_NORECIPIENT
		const std::string line = ":127.0.0.1 411 " + this->getNickname() + " :No recipient given\r\n";
		send(this->getUserFd(), line.c_str(), line.size(), 0);
	}
	else if(arg.size() < 2){
		// 412 ERR_NOTEXTTOSEND
		const std::string line = ":127.0.0.1 412 " + this->getNickname() + " :No text to send\r\n";
		send(this->getUserFd(), line.c_str(), line.size(), 0);
	}
	else{
		if(arg[0][0] == '#' || arg[0][0] == '&'){

		}
		else{

		}
	}
}
