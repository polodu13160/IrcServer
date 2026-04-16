#include "Channel.hpp"
#include "string"




bool Channel::checkUser(User &user) const
{
	const std::map<User *, bool>::const_iterator itUser = this->_users.find(&user);
	if (itUser == this->_users.end())
		return false;
	else
		return true;
}

bool Channel::checkUserAdmin(User &user) const
{
	if (checkUser(user) == true)
	{
		std::map<User *, bool>::const_iterator itUser = this->_users.find(&user);
		if (itUser->second == true)
			return true;
		else
			return false;
	}

	else
		return false;
}

const std::map<User *, bool> &Channel::getUsers() const
{
    return this->_users;
}

Channel::Channel(std::string name, std::string password) : _name(name), _password(password) {}

Channel::Channel(const Channel &other)
{
	*this = other;
}

Channel &Channel::operator=(const Channel &other)
{
	(void)other;
	return *this;
}

Channel::~Channel() {}

void Channel::setName(std::string name)
{
	this->_name = name;
}

void Channel::setInviteOnly(bool val)
{
	this->_inviteOnly = val;
}

void Channel::setPassword(std::string password)
{
	this->_password = password;
}

void Channel::setUserLimit(unsigned int val)
{
	this->_userLimit = val;
}

void Channel::addUser(User &user, bool admin)
{
	std::pair<User *, bool>insertUser(&user,admin);
	this->_users.insert(insertUser);
}

void Channel::addUserInvite(User &user)
{
	this->_usersInvite.insert(&user);
}

const std::string &Channel::getName(void) const
{
	return this->_name;
}

const std::string &Channel::getPassword(void) const
{
	return this->_password;
}

const std::string &Channel::getTopic(void) const
{
    return this->_topic;
}

bool Channel::getInviteOnly(void) const
{
	return this->_inviteOnly;
}

bool Channel::getTopicRestrictions(void) const
{
	return this->_topicRestrictions;
}

unsigned int Channel::getUserLimit() const
{
	return this->_userLimit;
}

bool Channel::checkPassword(std::string &password) const
{
	return (password == this->_password ? true : false);
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

User *Channel::getUserByNickname(const std::string &nickname){
	std::map<User *, bool>::iterator	it;
	for(it = this->_users.begin(); it != this->_users.end(); ++it){
		if(it->first->getNickname() == nickname) {

			User *usr = it->first;
			return usr;
		}
	}
	return NULL;
}


