#include <sys/socket.h>
#include "../inc/Channel.hpp"
#include "../Server/Server.hpp"
#include "../MessageParsing/User.hpp"

cmd::cmd(void){
	this->_cmdMap["KICK"] = &cmd::kick;
	this->_cmdMap["INVITE"] = &cmd::invite;
	this->_cmdMap["TOPIC"] = &cmd::topic;
	this->_cmdMap["MODE"] = &cmd::mode;
	this->_cmdMap["JOIN"] = &cmd::join;
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

Channel	*findChannel(Server server, std::string channel){
	vector<Channel>::iterator it;
	for(it = server.chanVector.begin(); it != server.chanVector.end(); it++){
		if(it->getName() == channel)
			return it.base();
	}
	return NULL;
}

bool	isMember(Channel *channel, User &user){
	std::map<User*, bool>::iterator	it;
	for(it = channel->_users.begin(); it != channel->_users.end(); it++){
		if(it->first->getUserFd() == user.getUserFd())
			return 1;
	}
	return 0;
}

void	cmd::join(Server server, User &user, std::string channel, std::string pass){
	// std::cout << "user has joined [channel]" <<std::endl;
	// Format : :Pseudo!Username@Host JOIN #nom_du_channel
	// Exemple : :karamire!karamire@127.0.0.1 JOIN #lol

	Channel	*dest = findChannel(server, channel);
	if(dest){
		if(!dest->getPassword().empty() && dest->getPassword().compare(pass)){
				//bad password
				return;
		}
		if(isMember(dest, user))
			return;
		dest->_users.insert(std::pair<User*, bool>(&user,0));
	}
	else{
		Channel newChan("channel", "");
		server.chanVector.push_back(newChan);
	}
	const std::string line = ":" + user.getNickname() + "!" + user.getUsername() + "@127.0.0.1 JOIN " + "#" + channel;
	send(user.getUserFd(), line.c_str(), line.size(), 0);
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
