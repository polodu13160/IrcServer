#include "User.hpp"

std::vector<std::string>	argSplit(std::string arg){
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

void	nameReply(Channel &channel, User &user){
	// RPL_NAMREPLY
	std::string line = ":127.0.0.1 353 " + user.getNickname() + " = #" + channel.getName() + " :";
	std::vector<User*>::const_iterator	it = channel.allUsersInVector().begin();
	if(channel.checkUserAdmin(*(*it)))
		line += "@";
	line += (*it)->getNickname();
	for(;it != channel.allUsersInVector().end(); it++){
		line += " ";
		if(channel.checkUserAdmin(*(*it)))
			line += "@";
		line += (*it)->getNickname();
	}
	line += "\r\n";
	send(user.getUserFd(), line.c_str(), line.size(), 0);
}

void	channelCheck(Server& server, Channel *dest, User &user, std::vector<std::string> channel, std::vector<std::string> pass, size_t i){
	// 473 ERR_INVITEONLYCHAN
	if(dest->getInviteOnly()){
	const std::string line = ":127.0.0.1 473 " + user.getNickname() + " #" + channel[i] + " : Cannot join channel (invite only)\r\n";
		send(user.getUserFd(), line.c_str(), line.size(), 0);
	}
	// 471 ERR_CHANNELISFULL
	else if(dest->getUsers().size() == dest->getUserLimit()){
		const std::string line = ":127.0.0.1 471 " + user.getNickname() + " #" + channel[i] + " : Cannot join channel (Channel is full)\r\n";
		send(user.getUserFd(), line.c_str(), line.size(), 0);
	}
	// 475 ERR_BADCHANNELKEY
	else if((!dest->getPassword().empty() && pass.size() > i && dest->getPassword().compare(pass[i])) || (!dest->getPassword().empty() && pass.size() <= i)){
		const std::string	line = ":127.0.0.1 475 " + user.getNickname() + " #" + channel[i] + " : Cannot join channel\r\n";
		send(user.getUserFd(), line.c_str(), line.size(), 0);
	}
	else if(dest->checkUser(user))
		;
	else{
		dest->addUser(user, 0);
		std::string line = ":" + user.getNickname() + "!" + user.getUsername() + "@127.0.0.1 JOIN " + "#" + channel[i] + "\r\n";
		send(user.getUserFd(), line.c_str(), line.size(), 0);
		dest->sendMsgUserForOthersUsersChannel(user, line);
		// RPL_TOPIC
		std::vector<std::string> topicArg;
		topicArg.push_back(channel[i]);
		user.topicCmd(server, topicArg);
		nameReply(*dest, user);
		user.setNbChannelRegistered(user.getnbChannelRegistered() + 1);
	}
}

void	User::joinCmd(Server &server, const std::vector<std::string>& arg){
	// Format : :Pseudo!Username@Host JOIN #nom_du_channel
	// Exemple : :karamire!karamire@127.0.0.1 JOIN #lol

	// 461 ERR_NEEDMOREPARAMS
	if(arg[0].empty()){
		std::string	line = ":127.0.0.1 461 " + this->getNickname() + " JOIN :Not enough parameters\r\n";
		send(this->getUserFd(), line.c_str(), line.size(), 0);
		return;
	}
	std::vector<std::string>	channel;
	channel = argSplit(arg[0]);
	std::vector<std::string>	pass;
	if(!arg[1].empty())
		pass = argSplit(arg[1]);
	for(size_t i = 0; i < channel.size(); i++){
		if(this->nbChannelRegistered == server._maxChanPerUser){
			// 405 ERR_TOOMANYCHANNELS
				const std::string line = ":127.0.0.1 405 " + this->getNickname() + " #" + channel[i] + " : You have joined too many channels\r\n";
		}
		else if((channel[i][0] != '#' && channel[i][0] != '&') || channel[i].find(" ") != std::string::npos || channel[i].size() > 50){
			// 403 ERR_NOSUCHCHANNEL
			const std::string	line = ":127.0.0.1 403 " + channel[i] + " :No such channel\r\n";
			send(this->getUserFd(), line.c_str(), line.size(), 0);
		}
		else{
			Channel	*dest = server.findChannel(channel[i]);
			if(dest){
				channelCheck(server, dest, *this, channel, pass, i);
			}
			else{
				// 405 ERR_TOOMANYCHANNELS
				if(this->nbChannelRegistered == server._maxChanPerUser){
					const std::string line = ":127.0.0.1 405 " + this->getNickname() + " #" + channel[i] + " : You have joined too many channels\r\n";
				}
				else{
					Channel newChan(channel[i], "");
					server._chanMap.insert(std::pair<std::string,Channel*>(newChan.getName(),&newChan));
					newChan.addUser(*this, 1);
					this->nbChannelRegistered++;
				}
			}
		}
	}
}


// 461 ERR_NEEDMOREPARAMS (X)             474 ERR_BANNEDFROMCHAN ()
// 473 ERR_INVITEONLYCHAN (X)             475 ERR_BADCHANNELKEY (X)
// 471 ERR_CHANNELISFULL (X)              476 ERR_BADCHANMASK ()
// 403 ERR_NOSUCHCHANNEL (x)              405 ERR_TOOMANYCHANNELS (X)
// 407 ERR_TOOMANYTARGETS (?)             437 ERR_UNAVAILRESOURCE (?)
// 332 RPL_TOPIC ()						  353 RPL_NAMREPLY
// 336 RPL_ENDOFNAMES

//:<nom_serveur> 475 <pseudonyme> #canal :Cannot join channel


// gerer plusieurs channel en parametre separes par virgules ex : JOIN #salon1,#salon2
