#include "User.hpp"


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
	// Format : :Pseudo!Username@Host JOIN #nom_du_channel
	// Exemple : :karamire!karamire@127.0.0.1 JOIN #lol

	// 461 ERR_NEEDMOREPARAMS
	if(arg[0].empty()){
		std::string	line = ":127.0.0.1 461 " + this->getNickname() + " JOIN :Not enough parameters\r\n";
		return;
	}
	std::vector<std::string>	channel;
	channel = getChannels(arg);
	for(size_t i = 0; i < channel.size(); i++){
		if((channel[i][0] != '#' && channel[i][0] != '&') || channel[i].find(" ") != std::string::npos || channel[i].size() > 50){
			// 403 ERR_NOSUCHCHANNEL
			const std::string	line = ":127.0.0.1 403 " + channel[i] + " :No such channel\r\n";
			send(this->getUserFd(), line.c_str(), line.size(), 0);
		}
		Channel	*dest = server.findChannel(channel[i]);
		if(dest){
			// 473 ERR_INVITEONLYCHAN
			if(dest->getInviteOnly()){
				const std::string line = ":127.0.0.1 473 " + this->getNickname() + " #" + channel[i] + " : Cannot join channel (invite only)\r\n";
				send(this->getUserFd(), line.c_str(), line.size(), 0);
			}
			// 471 ERR_CHANNELISFULL
			else if(dest->getUsers().size() == dest->getUserLimit()){
				const std::string line = ":127.0.0.1 471 " + this->getNickname() + " #" + channel[i] + " : Cannot join channel (Channel is full)\r\n";
				send(this->getUserFd(), line.c_str(), line.size(), 0);
			}
			// 475 ERR_BADCHANNELKEY
			else if(!dest->getPassword().empty() && dest->getPassword().compare(arg[1])){
				const std::string	line = ":127.0.0.1 475 " + this->getNickname() + " #" + channel[i] + " : Cannot join channel\r\n";
				send(this->getUserFd(), line.c_str(), line.size(), 0);
			}
			else if(dest->checkUser(*this))
				;
			else
				dest->addUser(*this, 0);
		}
		else{
			// 405 ERR_TOOMANYCHANNELS
			if(this->nbChannelRegistered == server._maxChanPerUser){
				const std::string line = ":127.0.0.1 405 " + this->getNickname() + " #" + channel[i] + " : You have joined too many channels\r\n";
			}
			Channel newChan(channel[i], "");
			server._chanMap.insert(std::pair<std::string,Channel>(newChan.getName(),newChan));
			newChan.addUser(*this, 1);
		}
		this->nbChannelRegistered++;
		// RPL_TOPIC
		// RPL_NAMREPLY
		const std::string line = ":" + this->getNickname() + "!" + this->getUsername() + "@127.0.0.1 JOIN " + "#" + channel[i] + "\r\n";
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
