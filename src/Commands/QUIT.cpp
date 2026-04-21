#include "User.hpp"

void User::quitCmd(Server &server)
{
    std::string messageSend = "ERROR :Tu as quitté le serveur fdp\r\n";
    send(this->_userFd, messageSend.c_str(), messageSend.size(), 0);
    std::set<User *> concernedUsers;
    for (std::map<std::string, Channel>::iterator it = server._chanMap.begin(); it != server._chanMap.end(); it++)
    {
        if (it->second.checkUser(*this) == true)
        {
            it->second.deletedUser(*this);
            for (std::vector<User *>::const_iterator it2 = it->second.allUsersInVector().begin(); it2 != it->second.allUsersInVector().end(); ++it2)
                concernedUsers.insert(*it2);
        }
    }
    messageSend = ":" + this->_nickname + "!" + this->_username + " QUIT" + " : Vous pouvez enfin le critiquer, il est enfin parti \r\n";
    for (std::set<User *>::iterator it = concernedUsers.begin(); it != concernedUsers.end(); it++)
        send((*it)->_userFd, messageSend.c_str(), messageSend.size(), 0);
    
    
    //Kaissot supprime utilisateur du channel
}