#include <iostream>
#include "Message.hpp"

void	tokenizeParams(Message *message, std::string msg, int start, int end){
	std::string	tmp;
	int	idx_param = 0;
	while(msg[end]){
		std::cout << "c = <" << msg[end] << ">" << std::endl;
		if(msg[end] == ':'){
			end++;
			start = end;
			for(; msg[end]; end++){}
			tmp = msg.substr(start, end - start);
			std::cout << "endparam : " << tmp << std::endl;
			message->setParam(tmp, idx_param);
			return ;
		}
		else{
			for(; msg[end] && msg[end] != ' '; end++){}
			tmp = msg.substr(start, end - start);
			std::cout << "param = <" << tmp  << ">" << std::endl;
			message->setParam(tmp, idx_param);
			if(!msg[end])
				return;
			end++;
			start = end;
			idx_param++;
		}
	}
}

void	TokenizeMsg(std::string msg){
	Message	message;
	std::string	tmp;
	int	start;
	int	end = 0;

	if(msg[end] == ':'){
		for(; msg[end] && msg[end] != ' '; end++){}
		if(!msg[end]){
			std::cout << "Incomplete message1" << std::endl;
			return;
		}
		tmp = msg.substr(0, end);
		message.setPrfx(tmp);
		std::cout << "Prefix : " << message.getPrfx() << std::endl;
		end++;
	}
	start = end;
	for(; msg[end] && msg[end] != ' '; end++){}
	if(!msg[end + 1]){
		std::cout << "Incomplete message2" << std::endl;
		return;
	}
	tmp = msg.substr(start, end - start);
	message.setCmd(tmp);
	std::cout << "Command : " << message.getCmd() << std::endl;
	end++;
	start = end;
	tokenizeParams(&message, msg, start, end);
	message.printParams();
}

int	main(int argc, char **argv){
	(void)argc;
	std::string msg = argv[1];
	TokenizeMsg(msg);
}
