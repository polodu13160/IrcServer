#include "User.hpp"

void User::quitCmd(Server &server, const std::vector<std::string> &arg)
{
    std::string explainMsg;
    if (arg.size() > 0)
    {
        explainMsg = arg[0];
        explainMsg.erase(0, 1);
    }
    std::string messageSend = "ERROR :You left the server";
    if (explainMsg.empty() == false)
    {
        messageSend += " because you said : " + explainMsg;
    }
    messageSend += "\r\n";
    if (messageSend.size() > MAX_SIZE_MESSAGE)
    {
        messageSend.erase(510);
        messageSend += "\r\n";
    }
    Server::sendCheck(this->_userFd, messageSend.c_str(), messageSend.size(), 0);
    std::set<User *> concernedUsers;

    std::map<std::string, Channel *>::iterator it = server._chanMap.begin();
    while (it != server._chanMap.end())
    {
        Channel *currentChan = it->second;

        if (currentChan->checkUser(*this) == true)
        {
            std::vector<User *> usersChannel = currentChan->allUsersInVector();
            for (std::vector<User *>::const_iterator it2 = usersChannel.begin(); it2 != usersChannel.end(); ++it2)
            {
                if ((*it2) != this)
                    concernedUsers.insert(*it2);
            }
            currentChan->deletedUser(*this);
            if (currentChan->getUsers().empty())
            {
                delete currentChan;
                server._chanMap.erase(it++);
                continue;
            }
        }
        ++it;
    }
    messageSend = ":" + this->_nickname + "!" + this->_username + "@" + this->_ip + " QUIT" + " : Good Bye";
    if (explainMsg.empty() == false)
    {
        messageSend += " and he said :" + explainMsg;
    }
    messageSend += " \r\n";
    if (messageSend.size() > MAX_SIZE_MESSAGE)
    {
        messageSend.erase(510);
        messageSend += " \r\n";
    }
    for (std::set<User *>::iterator it = concernedUsers.begin(); it != concernedUsers.end(); it++)
    {
        Server::sendCheck((*it)->_userFd, messageSend.c_str(), messageSend.size(), 0);
    }

    this->_hasDisconnected = true;
}
