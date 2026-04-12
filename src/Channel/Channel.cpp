#include "Channel.hpp"


Channel::Channel(std::string name, std::string password) : _name(name), _password(password){}

Channel::~Channel() {}

void	Channel::setName(std::string name){
	this->_name = name;
}

void	Channel::setPassword(std::string password){
	this->_password = password;
}

const std::string	&Channel::getName(void)const{
	return this->_name;
}

const std::string	&Channel::getPassword(void)const{
	return this->_password;
}

// void Channel::kick(User &user, User &userKick)
// {
// }

// void Channel::invite(User &user, User &userInvite)
// {
// }

// void Channel::topic(User &user, std::string topic)
// {
// }

// void Channel::mode(char type, User &user)
// {
// }

// void Channel::join(User &user, std::string _password)
// {
// }



// //Don't use
// Channel::Channel(const Channel &other)
// {
// }

// Channel::Channel()
// {
// }

// Channel &Channel::operator=(const Channel &other)
// {
// }
