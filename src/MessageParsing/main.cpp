#include <iostream>
#include "../../inc/User.hpp"
#include "../../inc/cmdPars.hpp"
#include "../../inc/Message.hpp"

void	tokenizeParams(Message *message, std::string msg, int start, int end){
	std::string	tmp;
	while(msg[end] && !message->fullParams){
		// std::cout << "c = <" << msg[end] << ">" << std::endl;
		if(msg[end] == ':'){
			start = end;
			for(; msg[end]; end++){}
			tmp = msg.substr(start, end - start);
			// std::cout << "endparam : " << tmp << std::endl;
			message->pushBackParam(tmp);
			return ;
		}
		else{
			for(; msg[end] && msg[end] != ' '; end++){}
			tmp = msg.substr(start, end - start);
			// std::cout << "param = <" << tmp  << ">" << std::endl;
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
			std::cout << "Incomplete message1" << std::endl;
			return;
		}
		tmp = msg.substr(0, end);
		message.setPrfx(tmp);
		std::cout << "Prefix : " << message.getPrfx() << std::endl;
		end++;
	}
	start = end;
	for(; end < msg.size() && msg[end] != ' '; end++){}
	tmp = msg.substr(start, end - start);
	message.setCmd(tmp);
	// std::cout << "Command : " << message.getCmd() << std::endl;
	end++;
	start = end;
	if(end < msg.size()){
		tokenizeParams(&message, msg, start, end);
	}
	message.printParams();
	cmdPars parser;
	parser.cmdParser(server, user, message.getCmd(), message.getParam());
}

void	getMsg(Server &server, std::string msg, int userFd){

	server.printUsers();

	User	*user = server.getUser(userFd, server);
	if(!user) {
		return;
	}
	user->setMessage(msg);
	std::string finalMsg = user->getMessage();
	if(!finalMsg.empty())
		TokenizeMsg(server, finalMsg, *user);
}

// int	main(int argc, char **argv){
// 	(void)argc;
// 	std::string msg = argv[1];
// 	TokenizeMsg(msg);
// }
