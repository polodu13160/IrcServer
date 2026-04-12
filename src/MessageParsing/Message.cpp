#include "../../inc/Message.hpp"

#include <cstring>
// #include "../cmd/cmd.hpp"

Message::Message(void){}

Message::~Message(void){}

void	Message::setCmd(std::string cmd){
	this->_cmd = cmd;
}

void	Message::setPrfx(std::string prefix){
	this->_prfx = prefix;
}

void	Message::setParam(std::string param, int i){
	this->_param[i] = param;
}

const std::string	&Message::getPrfx(void)const{
	return this->_prfx;
}

const std::string	&Message::getCmd(void)const{
	return this->_cmd;
}

const std::string	*Message::getParam(void)const{
	return this->_param;
}

void	Message::printParams(void){
	std::cout << "printParams" << std::endl;



	for(int i = 0; !this->_param[i].empty(); i++){
		if (std::strstr(this->_param[i].c_str(), "NICK"))

		std::cout << "Param number " << i << " : " << this->_param[i] << std::endl;
	}
}
