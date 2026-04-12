#include "../../inc/User.hpp"

Channel	*findChannel(std::string channel, std::vector<Channel> &channels){
	std::vector<Channel>::iterator it;
	for(it = channels.begin(); it != channels.end(); it++){
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

void	User::joinCmd(Server &server, User &user, std::string channel, std::string pass){
	// std::cout << "user has joined [channel]" <<std::endl;
	// Format : :Pseudo!Username@Host JOIN #nom_du_channel
	// Exemple : :karamire!karamire@127.0.0.1 JOIN #lol

	Channel	*dest = findChannel(channel, server._chanVector);
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
		server._chanVector.push_back(newChan);
	}
	const std::string line = ":" + user.getNickname() + "!" + user.getUsername() + "@127.0.0.1 JOIN " + "#" + channel;
	send(user.getUserFd(), line.c_str(), line.size(), 0);
}