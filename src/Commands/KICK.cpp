#include "User.hpp"

static std::vector<std::string> argSplit(std::string arg)
{
    std::vector<std::string> tab;
    size_t start = 0;
    size_t i = 0;

    for (; i < arg.size(); i++)
    {
        if (arg[i] == ',')
        {
            tab.push_back(arg.substr(start, i - start));
            start = i + 1;
        }
    }
    tab.push_back(arg.substr(start, i - start));
    return tab;
}

void User::kickCmd(Server &server, std::vector<std::string> &arg)
{
    std::string nameServer = ":";
    nameServer += server._ip;
    std::string sendMessage;

    if (arg.size() < 2)
    {
        sendMessage += nameServer + " 461 " + this->getNickname() + " QUICK :Not enough parameters\r\n";
        Server::sendCheck(this->_userFd, sendMessage.c_str(), sendMessage.size(), 0); // RPL = ERR_NEEDMOREPARAMS (461)
        return;
    }

    Channel *findChannel = server.findChannel(arg[0]);
    if (findChannel == NULL)
    {
        sendMessage = nameServer + " 403 " + this->_nickname + " " + arg[0] + " :Channel Not Found \r\n";
        Server::sendCheck(this->_userFd, sendMessage.c_str(), sendMessage.size(), 0); // RPL = ERR_NOSUCHCHANNEL (403)
        return;
    }
    if (findChannel->checkUser(*this) == false)
    {
        sendMessage = nameServer + " 442 " + this->_nickname + " " + findChannel->getName() + " :You are not part of the channel \r\n";
        Server::sendCheck(this->getUserFd(), sendMessage.c_str(), sendMessage.size(), 0); // ERR_NOTONCHANNEL 442
        return;
    }
    if (findChannel->checkUserAdmin(*this) == false)
    {
        sendMessage = nameServer + " 482 " + this->_nickname + " " + findChannel->getName() + " :You are not operator of this channel \r\n";
        Server::sendCheck(this->getUserFd(), sendMessage.c_str(), sendMessage.size(), 0); // ERR_CHANOPRIVSNEEDED
        return;
    }

    std::vector<std::string> usersKick = argSplit(arg[1]);
    for (size_t i = 0; i < usersKick.size(); i++)
    {
        User *findUser = findChannel->getUserByNickname(arg[1]);
        if (findUser == NULL)
        {
            sendMessage = nameServer + " 441 " + this->_nickname + " " + usersKick[i] + " " + findChannel->getName() + " :this user does not exist on this channel \r\n";
            Server::sendCheck(this->getUserFd(), sendMessage.c_str(), sendMessage.size(), 0);
            // :pol1212!pol@127.0.0.1 KICK #tutu pol13 :T'es moche
        }
        else
        {
            sendMessage = ":";
            sendMessage += this->_nickname + "!" + this->_username + "@" + this->_ip + " KICK " + arg[0] + " " + findUser->_nickname;
            if (arg.size() <= 3)
                sendMessage += " :kick looser \r\n";
            else
                sendMessage += " " + arg[2] + "\r\n";
            findChannel->sendMsgUserForOthersUsersChannel(*this, sendMessage);
            findChannel->deletedUser(*findUser);
            Server::sendCheck(this->_userFd, sendMessage.c_str(), sendMessage.size(), 0);
        }
        
        
    }
}
