#include "User.hpp"

std::vector<std::string>	getChannels(const std::vector<std::string> &arg){
	std::vector<std::string>	chanTab;
	size_t	start = 0;
	size_t	i = 0;

	for(; i < arg[0].size(); i++){
		if(arg[0][i] == ','){
			chanTab.push_back(arg[0].substr(start, i - start));
			start = i + 1;
		}
	}
	chanTab.push_back(arg[0].substr(start, i - start));
	return chanTab;
}

void	User::partCmd(Server &server, const std::vector<std::string> &arg){
	if (this->checkRegistration(server) == false)
		return;
	if(arg.size() < 1){
		std::string	line = ":" + server.getIp() + " 461 " + this->getNickname() + " PART :Not enough parameters\r\n";
		Server::sendCheck(this->getUserFd(), line.c_str(), line.size(), 0);
		return;
	}
	std::vector<std::string>	channel;
	channel = getChannels(arg);
	for(size_t i = 0; i < channel.size(); i++){
		if((channel[i][0] != '#' && channel[i][0] != '&') || channel[i].find(" ") != std::string::npos || channel[i].size() > 50){
			const std::string	line = ":" + server.getIp() + " 403 " + channel[i] + " :No such channel\r\n";
			Server::sendCheck(this->getUserFd(), line.c_str(), line.size(), 0);
		}
		else{
			Channel	*chan = server.findChannel(channel[i]);
			if(chan){
				if(!chan->checkUser(*this)){
					const std::string	line = ":" + server.getIp()+ " 442 " + channel[i] + " : You're not on that channel\r\n";
					Server::sendCheck(this->getUserFd(), line.c_str(), line.size(), 0);
				}
				else{
					std::string line;
					if(arg.size() > 1)
						line = ":" + this->getNickname() + "!" + this->getUsername() + "@" + this->_ip + " PART " + channel[i] + " " + arg[1] + "\r\n";
					else
						line = ":" + this->getNickname() + "!" + this->getUsername() + "@" + this->_ip + " PART " + channel[i] + "\r\n";
					Server::sendCheck(this->getUserFd(), line.c_str(), line.size(), 0);
					chan->sendMsgUserForOthersUsersChannel(*this, line);
					chan->deletedUser(*this);
					if(chan->getUsers().size() < 1){
						server._chanMap.erase(chan->getName());
						delete chan;
					}
				}
			}
			else{
				const std::string	line = ":" + server.getIp() + " 403 " + channel[i] + " :No such channel\r\n";
				Server::sendCheck(this->getUserFd(), line.c_str(), line.size(), 0);
			}
		}
	}
}
