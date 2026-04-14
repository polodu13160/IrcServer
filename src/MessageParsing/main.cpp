#include <iostream>
#include "../../inc/User.hpp"
#include "../../inc/cmdPars.hpp"
#include "../../inc/Message.hpp"
#include <vector>

// void	tokenizeParams(Message *message, std::string msg, int start, int end){
// 	std::string	tmp;
// 	while(msg[end] && !message->fullParams){
// 		// std::cout << "c = <" << msg[end] << ">" << std::endl;
// 		if(msg[end] == ':'){
// 			start = end;
// 			for(; msg[end]; end++){}
// 			tmp = msg.substr(start, end - start);
// 			// std::cout << "endparam : " << tmp << std::endl;
// 			message->pushBackParam(tmp);
// 			return ;
// 		}
// 		else{
// 			for(; msg[end] && msg[end] != ' '; end++){}
// 			tmp = msg.substr(start, end - start);
// 			// std::cout << "param = <" << tmp  << ">" << std::endl;
// 			message->pushBackParam(tmp);
// 			if(!msg[end])
// 				return;
// 			end++;
// 			start = end;
// 		}
// 	}
// }

// void	TokenizeMsg(Server &server, std::string msg, User &user){
// 	Message	message;
// 	std::string	tmp;
// 	unsigned long	start;
// 	unsigned long	end = 0;

// 	if(msg[end] == ':'){
// 		for(; end < msg.size() && msg[end] != ' '; end++){}
// 		if(end == msg.size()){
// 			std::cout << "Incomplete message1" << std::endl;
// 			return;
// 		}
// 		tmp = msg.substr(0, end);
// 		message.setPrfx(tmp);
// 		// std::cout << "Prefix : " << message.getPrfx() << std::endl;
// 		end++;
// 	}
// 	start = end;
// 	for(; end < msg.size() && msg[end] != ' '; end++){}
// 	tmp = msg.substr(start, end - start);
// 	message.setCmd(tmp);
// 	// std::cout << "Command : " << message.getCmd() << std::endl;
// 	end++;
// 	start = end;
// 	if(end < msg.size()){
// 		tokenizeParams(&message, msg, start, end);
// 	}
// 	// message.printParams();
// 	cmdPars parser;
// 	parser.cmdParser(server, user, message.getCmd(), message.getParam());
// }

// void	getMsg(Server &server, std::string msg, int userFd){
// 	User	*user = server.getUser(userFd, server);

// 	std::string result;
// 	// for (size_t i = 0; i < msg.length(); ++i) {
// 	// 	if (msg[i] == '\r') result += "\\r";
// 	// 	else if (msg[i] == '\n') result += "\\n";
// 	// 	else result += msg[i];
// 	// }

// 	if(!user) {
// 		std::cout << "caca";
// 		return;
// 	}
// 	user->setMessage(msg);
// 	std::string finalMsg = user->getMessage();
// 	while (!finalMsg.empty()) {
// 		TokenizeMsg(server, finalMsg, *user);
// 		finalMsg = user->getMessage();
// 	}
// }

void	printVector(std::vector<std::string> arg){
	for(int i = 0; i < arg.size(); i++){
		std::cout << "Arg number " << i << " : " << arg[i] << std::endl;
	}
}

void	validChannelName(std::vector<std::string> arg){
	for(int i = 0; i < arg.size(); i++){
		if((arg[i][0] != '#' && arg[i][0] != '&') || arg[i].find(" ") != std::string::npos){
			std::string	line = ":127.0.0.1 403 [channelName] :No such channel";
			//send
		}
	}
}

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
	printVector(chanTab);
	return chanTab;
}

int	main(int argc, char **argv){
	(void)argc;
	std::vector<std::string>	arg;
	for(int i = 1; argv[i]; i++){
		std::cout << "arg number " << i << " : " << argv[i] << std::endl;
		arg.push_back(argv[i]);
	}
	getChannels(arg);
	validChannelName(arg);
}
