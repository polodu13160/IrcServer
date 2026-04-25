#include "User.hpp"

void User::quitCmd(Server &server, const std::vector<std::string>& arg)
{
    std::string explainMsg;
    if (arg.size() > 0)
    {
        arg[0].erase(0, 1);
        explainMsg = arg[0];
    }
    std::string messageSend = "ERROR :You left the server";
    if (explainMsg.empty() == false)
    {
        messageSend +=" because you said : " + explainMsg;
    }
    messageSend += "\r\n";
    if (messageSend.size() > MAX_SIZE_MESSAGE)
    {
        messageSend.erase(510);
        messageSend += "\r\n";
    }
    Server::sendCheck(this->_userFd, messageSend.c_str(), messageSend.size(), 0);
    std::set<User *> concernedUsers;
    for (std::map<std::string, Channel*>::iterator it = server._chanMap.begin(); it != server._chanMap.end(); it++)
    {
        if (it->second->checkUser(*this) == true)
        {
            std::vector<User *> usersChannel = it->second->allUsersInVector();
            for (std::vector<User *>::const_iterator it2 = usersChannel.begin(); it2 != usersChannel.end(); ++it2)
            {
                if ((*it2) != this)
                    concernedUsers.insert(*it2);
            }
            it->second->deletedUser(*this);

        }
    }
    messageSend = ":" + this->_nickname  + "!" + this->_username + "@" + this->_ip + " QUIT" + " : Good Bye";
    if (explainMsg.empty() == false)
    {
        messageSend +=" and he said :" + explainMsg;
    }
    messageSend += " \r\n";
    if (messageSend.size() > MAX_SIZE_MESSAGE)
    {
        messageSend.erase(510);
        messageSend += " \r\n";
    }
    for (std::set<User *>::iterator it = concernedUsers.begin(); it != concernedUsers.end(); it++)
        Server::sendCheck((*it)->_userFd, messageSend.c_str(), messageSend.size(), 0);

    //Kaissot supprime utilisateur du channel
}
