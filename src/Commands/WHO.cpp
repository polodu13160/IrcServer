#include "User.hpp"

void	User::whoCmd(Server &server, const std::vector<std::string>& arg){

	if (this->checkRegistration(server) == false)
		return;
	if(arg.size() == 0){
		std::map<int, User>::iterator it;
		std::stringstream line;
		int	index = 0;
		for(it = server._users.begin(); it != server._users.end(); it++){
			line << ":" << server._ip << " 352 " << this->getNickname() << " :" << ++index << " " << it->second.getRealname() << "\r\n";
			std::string sendLine;
			line >> sendLine;
			Server::sendCheck(this->getUserFd(), sendLine.c_str(), sendLine.size(), 0);
		}
		// RPL_ENDOFWHO (315)
		std::string sendLine = ":" + server._ip + " 315 " + this->getNickname() + " " + " :End of /WHO list\r\n";
		Server::sendCheck(this->getUserFd(), sendLine.c_str(), sendLine.size(), 0);
	}
	else{
		Channel *channel = server.findChannel(arg[0]);
		if(!channel){
			// 403 ERR_NOSUCHCHANNEL
			const std::string	line = ":" + server._ip + " 403 " + arg[0] + " :No such channel\r\n";
			Server::sendCheck(this->getUserFd(), line.c_str(), line.size(), 0);
			return;
		}
		std::vector<User *> cpyUsersVector =  channel->allUsersInVector();
		std::vector<User*>::const_iterator	it = cpyUsersVector.begin();
		std::string line = ":" + server._ip + " 352 " + this->getNickname() + " " + channel->getName() + " : " + (*it)->getRealname() + "\r\n";
		// std::cout << "about to send : [" << line << "]" << std::endl;
		Server::sendCheck(this->getUserFd(), line.c_str(), line.size(), 0);
		it++;
		for(;it !=cpyUsersVector.end(); it++){
			std::string line = ":" + server._ip + " 352 " + this->getNickname() + " " + channel->getName() + " : " + (*it)->getRealname() + "\r\n";
			Server::sendCheck(this->getUserFd(), line.c_str(), line.size(), 0);
		}
		// RPL_ENDOFWHO (315)
		line = ":" + server._ip + " 315 " + this->getNickname() + " " + channel->getName() + " :End of /WHO list\r\n";
		Server::sendCheck(this->getUserFd(), line.c_str(), line.size(), 0);
	}
}
