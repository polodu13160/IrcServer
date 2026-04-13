#include "Channel.hpp"
#include "numeric"




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



bool Channel::checkUser(User &user) {
    std::map<User *, bool>::iterator itUser = this->_users.find(&user);
    if (itUser == this->_users.end())
	return false;
    else
	return true;
}

bool Channel::checkUserAdmin(User &user) {
    std::map<User *, bool>::iterator itUser = this->_users.find(&user);
    if (itUser->second == true)
	return true;
    else
	return false;
}


Channel::Channel(std::string &name) : _name(name) {
   // utilsMessage::messageToServer(name.c_str(), "channel created");
    this->_inviteOnly = false;
    this->_topicRestrictions = false;
	this->_userLimit = (size_t)-1;
}

Channel::~Channel() {}


	// Don't use
	Channel::Channel(const Channel &other) {}

	Channel::Channel() {}

	Channel &Channel::operator=(const Channel &other) {}

	