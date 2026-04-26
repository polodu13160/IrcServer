#include "User.hpp"

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

void	User::noticeCmd(Server &server, const std::vector<std::string>& arg){
	if (this->checkRegistration(server) == false)
		return;
	if(arg.size() < 1)
		return;
	else if(arg.size() < 2)
		return;
	else{
		std::vector<std::string> split = argSplit(arg[0]);
		for(size_t i = 0; i < split.size(); i++){
			if(split[i][0] == '#' || split[i][0] == '&'){
				Channel *channel = server.findChannel(split[i]);
				if(!channel)
					return;
				else if(!channel->checkUser(*this))
					return;
				else{
					std::string line = ":" + this->getNickname() + "!" + this->getUsername() + "@" + this->_ip + " NOTICE " + split[i] + " " + arg[1] + "\r\n";
					channel->sendMsgUserForOthersUsersChannel(*this, line);
				}
			}
			else{
				User *user = server.getUserbyNickname(split[i]);
				if(!user)
					return;
				const std::string line = ":" + this->getNickname() + "!" + this->getUsername() + "@" + this->_ip +  " NOTICE " + split[i] + " " + arg[1] + "\r\n";
				Server::sendCheck(user->getUserFd(), line.c_str(), line.size(), 0);
			}
		}
	}
}
