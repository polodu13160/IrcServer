#include "Channel.hpp"
#include "string"

void Channel::printChannelOperator() {
	std::map<User *,bool>::iterator it = this->_users.begin();
	for (; it != this->_users.end(); it++) {
		if (it->second == true)
			std::cout << "Operator : " << it->first->getNickname() << std::endl;
	}
}

void Channel::sendMsgUserForOthersUsersChannel(User &user, std::string &msg) const
{
	if (msg[0] != ':')
	{
		msg.insert(0,":");
	}
	std::vector<User *> usersChannel = this->allUsersInVector();
	for (size_t i = 0; i < usersChannel.size(); i++)
	{
		if (user.getNickname() != usersChannel[i]->getNickname())
		{
			#if (DEBUG==1)
				Server::messageToServer(msg.c_str(), NULL);
			#endif //DEBUG

			Server::sendCheck(usersChannel[i]->getUserFd(), msg.c_str(), msg.size(), 0);
		}

	}

}

const std::string Channel::getNickNameModifTopicLast() const
{
    return this->_nickNameLastModifTopic;
}

void Channel::setNickNameModifTopicLast(std::string &lastNickName)
{
	this->_nickNameLastModifTopic = lastNickName;
}

const std::string Channel::getTimeUnixModifTopicLast() const
{
    return this->_lastTimeUnixModifTopic;
}

void Channel::setTimeUnixModifTopicLast(const std::string &time_val)
{
	this->_lastTimeUnixModifTopic = time_val;
}

void Channel::setTopic(const char *value)
{
	this->_topic = value;
}

void Channel::deletedUser(User &user)
{
	std::map<User *, bool>::const_iterator itUser = this->_users.find(&user);
	this->_users.erase(itUser->first);
}

const std::vector<User *> Channel::allUsersInVector() const
{
	std::vector<User *> allUsers;
	std::map<User *, bool>::const_iterator itUser;
	for (itUser= this->_users.begin(); itUser != this->_users.end(); itUser++)
	{
		// Server::messageToServer(itUser->first->getUsername().c_str(), NULL);
		allUsers.push_back(itUser->first);
	}
	return allUsers;
}

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

void Channel::addInviteUser(std::string user)
{
	this->_usersInvite.insert(user);
}

bool Channel::getInInviteUsers(std::string user)
{
	if (this->_usersInvite.find(user) != this->_usersInvite.end())
		return true;
    return false;
}

Channel::Channel(std::string name) : _name(name){
	this->_userLimit = -1;
	this->_inviteOnly = false;
	this->_topicRestrictions = false;
}

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
	std::pair<User *, bool> insertUser(&user, admin);
	this->_users.insert(insertUser);
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

void Channel::changeUserOp(User &user, bool sign) {
	if (sign == true)
		this->_users[&user] = true;
	else
		this->_users[&user] = false;
}

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


