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
			Channel *channel = server.findChannel(arg[0]);
			if(!channel){
				// 403 ERR_NOSUCHCHANNEL
				const std::string	line = ":127.0.0.1 403 " + arg[0] + " :No such channel\r\n";
				send(this->getUserFd(), line.c_str(), line.size(), 0);
				return;
			}
			std::string line = ":" + this->getNickname() + "!" + this->getUsername() + "@127.0.0.1 PRIVMSG " + arg[0] + " :" + arg[1] + "\r\n";
			channel->sendMsgUserForOthersUsersChannel(*this, line);
		}
		else{
			User *user = server.getUserbyNickname(arg[0]);
			if(!user){
				// 401 ERR_NOSUCHNICK
				const std::string line = ":127.0.0.1 401 " + arg[1] + " :No such Nickname\r\n";
				send(this->getUserFd(), line.c_str(), line.size(), 0);
			}
			const std::string line = ":" + this->getNickname() + "!" + this->getUsername() + "@127.0.0.1 PRIVMSG " + arg[0] + " :" + arg[1] + "\r\n";
			send(user->getUserFd(), line.c_str(), line.size(), 0);
		}
	}
}
