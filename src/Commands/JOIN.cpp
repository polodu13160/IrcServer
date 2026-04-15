#include "../../inc/User.hpp"

Channel	*findChannel(std::string channel, std::vector<Channel> &channels){
	std::vector<Channel>::iterator it;
	for(it = channels.begin(); it != channels.end(); it++){
		if(it->getName() == channel)
			return it.base();
	}
	return NULL;
}

// bool	isMember(Channel *channel, User &user){
// 	std::map<User*, bool>::iterator	it;
// 	for(it = channel->_users.begin(); it != channel->_users.end(); it++){
// 		if(it->first->getUserFd() == user.getUserFd())
// 			return 1;
// 	}
// 	return 0;
// }

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
	chanTab.push_back(arg[0].substr(start, i - start - 1));
	return chanTab;
}

void	User::joinCmd(Server &server, const std::vector<std::string>& arg){
	// std::cout << "user has joined [channel]" <<std::endl;
	// Format : :Pseudo!Username@Host JOIN #nom_du_channel
	// Exemple : :karamire!karamire@127.0.0.1 JOIN #lol

	if(arg[0].empty()){
		std::string	line = ":127.0.0.1 461 " + this->getNickname() + " JOIN :Not enough parameters";
		return;
	}
	std::vector<std::string>	channel;
	channel = getChannels(arg);
	// std::string	channel = arg[0];
	// std::string	pass = arg[1];
	for(size_t i = 0; i < arg.size(); i++){
		if((arg[i][0] != '#' && arg[i][0] != '&') || arg[i].find(" ") != std::string::npos || arg[i].size() > 50){
			const std::string	line = ":127.0.0.1 403 " + channel[i] + " :No such channel";
			send(this->getUserFd(), line.c_str(), line.size(), 0);
		}
		Channel	*dest = findChannel(channel[i], server._chanVector);
		if(dest){
			// check si invite only chan quand les getters sont fait dans channel X
			if(dest->getInviteOnly()){
				const std::string line = ":127.0.0.1 473 " + this->getNickname() + " #" + channel[i] + " : Cannot join channel (invite only)";
				send(this->getUserFd(), line.c_str(), line.size(), 0);
			}
			// check si full channel
			else if(dest->getUsers().size() == dest->getUserLimit()){
				const std::string line = ":127.0.0.1 471 " + this->getNickname() + " #" + channel[i] + " : Cannot join channel (Channel is full)";
				send(this->getUserFd(), line.c_str(), line.size(), 0);
			}
			else if(!dest->getPassword().empty() && dest->getPassword().compare(arg[1])){
				const std::string	line = ":127.0.0.1 475 " + this->getNickname() + " #" + channel[i] + " : Cannot join channel";
				send(this->getUserFd(), line.c_str(), line.size(), 0);
			}
			else if(dest->checkUser(*this))
				;
			else
				dest->addUser(*this, 0);
		}
		else{
			//check si user a atteint maxChanRegistered
			if(this->nbChannelRegistered == server._maxChanPerUser){
				const std::string line = ":127.0.0.1 405 " + this->getNickname() + " #" + channel[i] + " : You have joined too many channels";
			}
			Channel newChan("channel", "");
			server._chanVector.push_back(newChan);
			newChan.addUser(*this, 1);
		}
		this->nbChannelRegistered++;
		// RPL_TOPIC
		// RPL_NAMREPLY
		const std::string line = ":" + this->getNickname() + "!" + this->getUsername() + "@127.0.0.1 JOIN " + "#" + channel[i];
		send(this->getUserFd(), line.c_str(), line.size(), 0);
	}
}


// 461 ERR_NEEDMOREPARAMS (X)             474 ERR_BANNEDFROMCHAN ()
// 473 ERR_INVITEONLYCHAN (X)             475 ERR_BADCHANNELKEY (X)
// 471 ERR_CHANNELISFULL (X)              476 ERR_BADCHANMASK ()
// 403 ERR_NOSUCHCHANNEL (x)              405 ERR_TOOMANYCHANNELS (X)
// 407 ERR_TOOMANYTARGETS (?)             437 ERR_UNAVAILRESOURCE (?)
// 332 RPL_TOPIC ()

//:<nom_serveur> 475 <pseudonyme> #canal :Cannot join channel


// gerer plusieurs channel en parametre separes par virgules ex : JOIN #salon1,#salon2
