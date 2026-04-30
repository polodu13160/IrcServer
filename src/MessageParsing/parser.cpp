#include <iostream>
#include "User.hpp"
#include "CmdDispatch.hpp"
#include "Message.hpp"

void	tokenizeParams(Message *message, std::string msg, int start, int end){
	std::string	tmp;
	while(msg[end] && !message->fullParams){
		if(msg[end] == ':'){
			start = end;
			for(; msg[end]; end++){}
			tmp = msg.substr(start, end - start);
			message->pushBackParam(tmp);
			return ;
		}
		else{
			for(; msg[end] && msg[end] != ' '; end++){}
			tmp = msg.substr(start, end - start);
			message->pushBackParam(tmp);
			if(!msg[end])
				return;
			end++;
			start = end;
		}
	}
}

void	TokenizeMsg(Server &server, std::string msg, User &user){
	Message	message;
	std::string	tmp;
	unsigned long	start;
	unsigned long	end = 0;
	if(msg[end] == ':'){
		for(; end < msg.size() && msg[end] != ' '; end++){}
		if(end == msg.size()){
			return;
		}
		tmp = msg.substr(0, end);
		message.setPrfx(tmp);
		end++;
	}
	start = end;
	for(; end < msg.size() && msg[end] != ' '; end++){}
	tmp = msg.substr(start, end - start);
	message.setCmd(tmp);
	end++;
	start = end;
	if(end < msg.size()){
		tokenizeParams(&message, msg, start, end);
	}
	CmdDispatch::cmdDispatcher(server, user, message.getCmd(), message.getParam());
}



void	Server::getMsgFD(Server &server, std::string msg, int userFd){
	User	*user = server.getUser(userFd, server);

	std::string result;

	if (user->getHasDisconnected() == true) {
		epoll_ctl(server._epollInstance , EPOLL_CTL_DEL, user->_userFd, NULL);
		close(user->_userFd);
		server._users.erase(user->_userFd);
		return;
	}

	if(!user) {
		std::cout << "caca";
		return;
	}
	user->setMessage(msg);
	std::string finalMsg = user->getMessage();
	while (!finalMsg.empty()) {
		TokenizeMsg(server, finalMsg, *user);
		finalMsg = user->getMessage();
	}
}


void	printVector(std::vector<std::string> arg){
	for(size_t i = 0; i < arg.size(); i++){
		std::cout << "Arg number " << i << " : " << arg[i] << std::endl;
	}
}
