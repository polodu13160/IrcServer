#include "../../inc/Message.hpp"

#include <cstring>
// #include "../cmd/cmd.hpp"

Message::Message(void) : fullParams(0){}

Message::~Message(void){}

void	Message::setCmd(std::string cmd){
	this->_cmd = cmd;
}

void	Message::setPrfx(std::string prefix){
	this->_prfx = prefix;
}

void	Message::pushBackParam(std::string param){
	this->_params.push_back(param);
	if(this->_params.size() == 15)
		this->fullParams = 1;
}

const std::string	&Message::getPrfx(void)const{
	return this->_prfx;
}

const std::string	&Message::getCmd(void)const{
	return this->_cmd;
}

std::vector<std::string>	Message::getParam(void)const{
	return this->_params;
}

void	Message::printParams(void){
	std::cout << "printParams" << std::endl;



	for(int i = 0; !this->_params[i].empty(); i++){
		std::cout << "Param number " << i << " : " << this->_params[i] << std::endl;
	}
}
