#include "../../inc/User.hpp"

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

void	User::partCmd(Server &server, std::vector<std::string> &arg){
	if(arg.size() < 1){
		// 461 ERR_NEEDMOREPARAMS
		std::string	line = ":" + server.getIp() + " 461 " + this->getNickname() + " PART :Not enough parameters\r\n";
		Server::sendCheck(this->getUserFd(), line.c_str(), line.size(), 0);
		return;
	}
	std::vector<std::string>	channel;
	channel = getChannels(arg);
	for(size_t i = 0; i < channel.size(); i++){
		if((channel[i][0] != '#' && channel[i][0] != '&') || channel[i].find(" ") != std::string::npos || channel[i].size() > 50){
			// 403 ERR_NOSUCHCHANNEL
			const std::string	line = ":" + server.getIp() + " 403 " + channel[i] + " :No such channel\r\n";
			Server::sendCheck(this->getUserFd(), line.c_str(), line.size(), 0);
		}
		else{
			Channel	*chan = server.findChannel(channel[i]);
			if(chan){
				if(!chan->checkUser(*this)){
					// 442 ERR_NOTONCHANNEL
					const std::string	line = ":" + server.getIp()+ " 442 " + channel[i] + " : You're not on that channel\r\n";
					Server::sendCheck(this->getUserFd(), line.c_str(), line.size(), 0);
				}
				else{
					std::string line;
					if(arg.size() > 1)
						line = ":" + this->getNickname() + "!" + this->getUsername() + "@" + this->_ip + " PART " + channel[i] + " :" + arg[1] + "\r\n";
					else
						line = ":" + this->getNickname() + "!" + this->getUsername() + "@" + this->_ip + " PART " + channel[i] + "\r\n";
					Server::sendCheck(this->getUserFd(), line.c_str(), line.size(), 0);
					chan->sendMsgUserForOthersUsersChannel(*this, line);
					chan->deletedUser(*this);
					// if(chan->getUsers().size() < 1){
					// 	server._chanMap.erase(chan->getName());
					// 	delete chan;
					// }
					this->nbChannelRegistered--;
				}
			}
			else{
				// 403 ERR_NOSUCHCHANNEL
				const std::string	line = ":" + server.getIp() + " 403 " + channel[i] + " :No such channel\r\n";
				Server::sendCheck(this->getUserFd(), line.c_str(), line.size(), 0);
			}
		}
	}
}

// ERR_NEEDMOREPARAMS (X)             ERR_NOSUCHCHANNEL (X)
// 442 ERR_NOTONCHANNEL
