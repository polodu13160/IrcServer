#include "Channel.hpp"
#include "namespaces.hpp"
#include "numeric"

const std::string Channel::TYPEMODE("itkol");


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
    utilsMessage::messageToServer(name.c_str(), "channel created");
    this->_inviteOnly = false;
    this->_topicRestrictions = false;
	this->_userLimit = (size_t)-1;
}

Channel::~Channel() {}

void Channel::kick(User &user, User &userKick) {
    if (this->checkUser(user) == true) {
	if (this->checkUserAdmin(user) == true) {
	    if (this->checkUser(userKick) == true) {
		// TODO: faire le message a envoyer a luser kick
		for (int i = 0; this->_users.size() > i; i++) {
		    // TODO: faire le message a envoyer a tout les utilisateurs
		    // qu'il a ete kick par user;
		}
	    } else {
		// TODO: faire le message a envoyer a l'utilisateur qu'il ne
		// peut pas kick car utilisateur n'est pas trouvé;
	    }
	} else {
	    // TODO faire un message a envoyer a l'utilisateur pour dire qu'il
	    // n'a pas les droits
	}
    } else {
	// Ne rien faire
    }
}

void Channel::invite(User &user, User &userInvite) {
    if (this->checkUser(user) == true) {
	// utilsMessage::messageToClient(user.getUserFd(),NULL,user.getNickname(),&(this->_name),"KICK",NULL);
	// TODO: faire le message a envoyer au client pour confirmer linvit;
	// TODO: faire le message a envoyer au client inviter pour lui dire
	// qu'il a ete invite;
		this->_usersInvite.insert(&userInvite);
    } else {
	// ne rien faire
    }
}

void Channel::topic(User &user, std::string topic) {
    if (this->checkUser(user) == true) {
	if (this->checkUserAdmin(user) == true) {
	    // TODO: faire le message a envoyer au channel pour modifier le
	    // channel;
	    // TODO: faire le message a envoyer au client pour confirmer que le
	    // channel a ete modifie
	} else {
	    if (this->_topicRestrictions == true) {
		for (int i = 0; this->_users.size() > i; i++) {
		    // TODO: faire le message a envoyer au channel pour modifier
		    // le channel;
		}
	    } else {
		// TODO: faire le message pour dire a l'utilisateur qu'il ne
		// peut pas modifier le topic
	    }
	}
    } else {
	// ne rien faire
    }
}

void Channel::msg(User &user, std::string &text) {
    if (checkUser(user) == true) {
	for (int i = 0; this->_users.size() > i; i++) {
	    // TODO: faire le message a envoyer a tous les utilisateurs du
	    // channel
	}

    } else {
	// ne rien faire
    }
}





	void Channel::join(User & user, std::string _password) 
	{
		if (this->_usersInvite)
	}

	// Don't use
	Channel::Channel(const Channel &other) {}

	Channel::Channel() {}

	Channel &Channel::operator=(const Channel &other) {}

	