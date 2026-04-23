#include "User.hpp"

// :expediteur!Username@Host PRIVMSG <target> :message\r\n
// 411 ERR_NORECIPIENT		412 ERR_NOTEXTTOSEND
// 401 ERR_NOSUCHNICK		404 ERR_CANNOTSENDTOCHAN

// PRIVMSG <target> <message>

static std::vector<std::string>	argSplit(std::string arg){
	std::vector<std::string>	tab;
	size_t	start = 0;
	size_t	i = 0;

	for(; i < arg.size(); i++){
		if(arg[i] == ','){
			tab.push_back(arg.substr(start, i - start));
			start = i + 1;
		}
	}
	tab.push_back(arg.substr(start, i - start));
	return tab;
}

void	User::privMsgCmd(Server &server, std::vector<std::string> arg){
	if(arg.size() < 1){
		// 411 ERR_NORECIPIENT
		const std::string line = ":" + server._ip + " 411 " + this->getNickname() + " :No recipient given\r\n";
		Server::sendCheck(this->getUserFd(), line.c_str(), line.size(), 0);
	}
	else if(arg.size() < 2){
		// 412 ERR_NOTEXTTOSEND
		const std::string line = ":" + server._ip + " 412 " + this->getNickname() + " :No text to send\r\n";
		Server::sendCheck(this->getUserFd(), line.c_str(), line.size(), 0);
	}
	else{
		std::vector<std::string>	split = argSplit(arg[0]);
		for(size_t i = 0; i < split.size(); i++){
			if(split[i][0] == '#' || split[i][0] == '&'){
				Channel *channel = server.findChannel(split[i]);
				if(!channel){
					// 403 ERR_NOSUCHCHANNEL
					const std::string	line = ":" + server._ip + " 403 " + split[i] + " :No such channel\r\n";
					Server::sendCheck(this->getUserFd(), line.c_str(), line.size(), 0);
				}
				else if(!channel->checkUser(*this)){
					// 404 ERR_CANNOTSENDTOCHAN
					const std::string	line = ":" + server._ip + " 404 " + split[i] + " :Cannot send to channel\r\n";
					Server::sendCheck(this->getUserFd(), line.c_str(), line.size(), 0);
				}
				else{
					std::string line = ":" + this->getNickname() + "!" + this->getUsername() + "@" + this->_ip +  " PRIVMSG " + split[i] +" "+ arg[1] + "\r\n";
					channel->sendMsgUserForOthersUsersChannel(*this, line);
				}
			}
			else{
				User *user = server.getUserbyNickname(split[i]);
				if(!user){
					// 401 ERR_NOSUCHNICK
					const std::string line = ":" + server._ip + " 401 " + split[i] + " :No such Nickname\r\n";
					Server::sendCheck(this->getUserFd(), line.c_str(), line.size(), 0);
					return;
				}
				const std::string line = ":" + this->getNickname() + "!" + this->getUsername() + "@" + this->_ip +  " PRIVMSG " + split[i] +" "+  arg[1] + "\r\n";
				Server::sendCheck(user->getUserFd(), line.c_str(), line.size(), 0);
			}
		}
	}
}
