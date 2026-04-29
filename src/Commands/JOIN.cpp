#include "User.hpp"

static std::vector<std::string>	argSplit(const std::string &arg){
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

static void	nameReply(Channel &channel, User &user, Server &server){
	std::string line = ":" + server.getIp() +  " 353 " + user.getNickname() + " = " + channel.getName() + " :";
	std::vector<User*> cpyUsersVector =  channel.allUsersInVector();
	std::vector<User*>::const_iterator	it = cpyUsersVector.begin();

	if(channel.checkUserAdmin(*(*it)))
		line += "@";
	line += (*it)->getNickname();
	line += "\r\n";
	Server::sendCheck(user.getUserFd(), line.c_str(), line.size(), 0);
	it++;
	for(;it !=cpyUsersVector.end(); it++){
		line = ":" + server.getIp() + " 353 " + user.getNickname() + " = " + channel.getName() + " :";
		if(channel.checkUserAdmin(*(*it)))
			line += "@";
		line.insert(line.size(), (*it)->getNickname());
		line += "\r\n";
		Server::sendCheck(user.getUserFd(), line.c_str(), line.size(), 0);
	}
	line = ":" + server.getIp()+ " 366 "  + user.getNickname() + " " + channel.getName() +  " :End of /NAMES list\r\n";
	// RPL_ENDOFNAMES (366)
	Server::sendCheck(user.getUserFd(), line.c_str(), line.size(), 0);
}

static void	channelCreation(std::map<std::string, Channel *>& chanMap, std::vector<std::string> channel, std::vector<std::string> pass, size_t i, Server &server, User &user){
	Channel *newChan = new Channel(channel[i]);
	if(pass.size() > i)
		newChan->setPassword(pass[i]);
	chanMap.insert(std::pair<std::string,Channel*>(newChan->getName(),newChan));
	newChan->addUser(user, 1);
	std::string line = ":" + user.getNickname() + "!" + user.getUsername() + "@" + user.getIp() + " JOIN " + channel[i] + "\r\n";
	Server::sendCheck(user.getUserFd(), line.c_str(), line.size(), 0);
	// RPL_TOPIC
	std::vector<std::string> topicArg;
	topicArg.push_back(channel[i]);
	user.topicCmd(server, topicArg);
	nameReply(*newChan, user, server);
}

static void	addUserHandler(Server &server, User &user, Channel *dest){
	dest->addUser(user, 0);
	std::string line = ":" + user.getNickname() + "!" + user.getUsername() + "@" + user.getIp() +  " JOIN " + dest->getName() + "\r\n";
	Server::sendCheck(user.getUserFd(), line.c_str(), line.size(), 0);
	dest->sendMsgUserForOthersUsersChannel(user, line);
	// RPL_TOPIC
	std::vector<std::string> topicArg;
	topicArg.push_back(dest->getName());
	user.topicCmd(server, topicArg);
	nameReply(*dest, user, server);
}

static void	channelCheck(Server& server, Channel *dest, User &user, std::vector<std::string> pass, size_t i){
	if(checkMode(dest->_modeStock, MODE_INVITE_O) && !dest->getInInviteUsers(user.getNickname())){
	const std::string line = ":" + server.getIp()+ " 473 " + user.getNickname() + " " + dest->getName() + " :Cannot join channel (invite only)\r\n";
		Server::sendCheck(user.getUserFd(), line.c_str(), line.size(), 0);
	}
	else if(checkMode(dest->_modeStock, MODE_LIMIT_SET) && dest->getUsers().size() >= dest->getUserLimit()){
		const std::string line = ":" + server.getIp()+ " 471 " + user.getNickname() + " " + dest->getName() + " :Cannot join channel (Channel is full)\r\n";
		Server::sendCheck(user.getUserFd(), line.c_str(), line.size(), 0);
	}
	else if(checkMode(dest->_modeStock, MODE_KEY_SET) && ((!dest->getPassword().empty() && pass.size() > i && dest->getPassword().compare(pass[i])) || (!dest->getPassword().empty() && pass.size() <= i))){
		const std::string	line = ":" + server.getIp()+ " 475 " + user.getNickname() + " " + dest->getName() + " :Cannot join channel\r\n";
		Server::sendCheck(user.getUserFd(), line.c_str(), line.size(), 0);
	}
	else if(dest->checkUser(user))
		return;
	else
		addUserHandler(server, user, dest);
	dest->printChannelOperator();

}

void	User::joinCmd(Server &server, const std::vector<std::string>& arg){
	if (this->checkRegistration(server) == false)
		return;
	if(arg.size() < 1){
		std::string	line = ":" + server.getIp()+ " 461 " + this->getNickname() + " JOIN :Not enough parameters\r\n";
		Server::sendCheck(this->getUserFd(), line.c_str(), line.size(), 0);
		return;
	}
	std::vector<std::string>	channel;
	channel = argSplit(arg[0]);
	std::vector<std::string>	pass;
	if(arg.size() > 1)
		pass = argSplit(arg[1]);
	for(size_t i = 0; i < channel.size(); i++){
		if((channel[i][0] != '#' && channel[i][0] != '&') || channel[i].find(" ") != std::string::npos || channel[i].size() > 50 || channel[i].size() < 2){
			const std::string	line = ":" + server.getIp()+ " 403 " + channel[i] + " :No such channel\r\n";
			Server::sendCheck(this->getUserFd(), line.c_str(), line.size(), 0);
		}
		else{
			Channel	*dest = server.findChannel(channel[i]);
			if(dest){
				channelCheck(server, dest, *this, pass, i);
			}
			else{
				channelCreation(server._chanMap, channel, pass, i, server, *this);
			}
		}
	}
}
