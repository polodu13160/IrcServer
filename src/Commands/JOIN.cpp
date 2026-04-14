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

// void	validChannelName(std::vector<std::string> arg){
// 	for(int i = 0; i < arg.size(); i++){
// 		if((arg[i][0] != '#' && arg[i][0] != '&') || arg[i].find(" ") != std::string::npos){
// 			std::string	line = ":127.0.0.1 403 [channelName] :No such channel";
// 			//send
// 		}
// 	}
// }

std::vector<std::string>	getChannels(const std::vector<std::string> &arg){
	std::vector<std::string>	chanTab;
	int	start = 0;
	int	i = 0;

	for(; i < arg[0].size(); i++){
		if(arg[0][i] == ','){
			chanTab.push_back(arg[0].substr(start, i - start));
			start = i + 1;
		}
	}
	chanTab.push_back(arg[0].substr(start, i - start - 1));
	return chanTab;
}

void	User::joinCmd(Server &server, User &user, const std::vector<std::string>& arg){
	// std::cout << "user has joined [channel]" <<std::endl;
	// Format : :Pseudo!Username@Host JOIN #nom_du_channel
	// Exemple : :karamire!karamire@127.0.0.1 JOIN #lol

	std::vector<std::string>	channel;
	channel = getChannels(arg);
	std::string	channel = arg[0];
	std::string	pass = arg[1];
	for(int i = 0; i < arg.size(); i++){
		if((arg[i][0] != '#' && arg[i][0] != '&') || arg[i].find(" ") != std::string::npos){
			const std::string	line = ":127.0.0.1 403 " + channel[i] + " :No such channel";
			send(user.getUserFd(), line.c_str(), line.size(), 0);
		}
		Channel	*dest = findChannel(channel[i], server._chanVector);
		if(dest){
			// check si invite only chan quand les getters sont fait dans channel
			// check si full channel
			// check si ban du chan
			if(!dest->getPassword().empty() && dest->getPassword().compare(pass)){
				const std::string	line = ":127.0.0.1 475 " + user.getNickname() + " #" + channel[i] + " : Cannot join channel";
				send(user.getUserFd(), line.c_str(), line.size(), 0);
			}
			else if(isMember(dest, user))
				;
			else
				dest->_users.insert(std::pair<User*, bool>(&user,0));
		}
		else{
			//check si nb de channel full
			Channel newChan("channel", "");
			server._chanVector.push_back(newChan);
		}
		const std::string line = ":" + user.getNickname() + "!" + user.getUsername() + "@127.0.0.1 JOIN " + "#" + channel[i];
		send(user.getUserFd(), line.c_str(), line.size(), 0);
	}
}


// 461 ERR_NEEDMOREPARAMS (X)             474 ERR_BANNEDFROMCHAN ()
// 473 ERR_INVITEONLYCHAN ()             475 ERR_BADCHANNELKEY (X)
// 471 ERR_CHANNELISFULL ()              476 ERR_BADCHANMASK ()
// 403 ERR_NOSUCHCHANNEL (x)              405 ERR_TOOMANYCHANNELS ()
// 407 ERR_TOOMANYTARGETS (?)             437 ERR_UNAVAILRESOURCE (?)
// 332 RPL_TOPIC ()

//:<nom_serveur> 475 <pseudonyme> #canal :Cannot join channel (+k)


// gerer plusieurs channel en parametre separes par virgules ex : JOIN #salon1,#salon2
