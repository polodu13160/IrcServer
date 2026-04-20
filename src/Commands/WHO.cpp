#include "User.hpp"

void	User::whoCmd(Server &server, std::vector<std::string> arg){

	if(arg.size() == 0){
		std::map<int, User>::iterator it;
		std::stringstream line;
		int	index = 0;
		for(it = server._users.begin(); it != server._users.end(); it++){
			line << ":127.0.0.1 352 " << this->getNickname() << " :" << ++index << " " << it->second.getRealname() << "\r\n";
			std::string sendLine;
			line >> sendLine;
			send(this->getUserFd(), sendLine.c_str(), sendLine.size(), 0);
		}
		// RPL_ENDOFWHO (315)
		std::string sendLine = ":127.0.0.1 315 " + this->getNickname() + " " + " :End of /WHO list\r\n";
		send(this->getUserFd(), sendLine.c_str(), sendLine.size(), 0);
	}
	else{
		Channel *channel = server.findChannel(arg[0]);
		if(!channel){

		}
		std::vector<User *> cpyUsersVector =  channel->allUsersInVector();
		std::vector<User*>::const_iterator	it = cpyUsersVector.begin();
		std::string line = ":127.0.0.1 352 " + this->getNickname() + " " + channel->getName() + " : " + (*it)->getRealname() + "\r\n";
		send(this->getUserFd(), line.c_str(), line.size(), 0);
		it++;
		for(;it !=cpyUsersVector.end(); it++){
			std::string line = ":127.0.0.1 352 " + this->getNickname() + " " + channel->getName() + " : " + (*it)->getRealname() + "\r\n";
			send(this->getUserFd(), line.c_str(), line.size(), 0);
		}
		// RPL_ENDOFWHO (315)
		line = ":127.0.0.1 315 " + this->getNickname() + " " + channel->getName() + " :End of /WHO list\r\n";
		send(this->getUserFd(), line.c_str(), line.size(), 0);
	}
}
