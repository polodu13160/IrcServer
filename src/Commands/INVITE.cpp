#include "User.hpp"
#include "Channel.hpp"

void User::inviteCmd(Server &server, std::vector<std::string> &arg)
{
    std::string nameServer = ":";
    nameServer += HOST;
    std::string sendMessage;
    if (arg.size() < 2)
    {
        sendMessage += nameServer + " 461 " + this->getNickname() + " INVITE :Not enough parameters\r\n";
        Server::sendCheck(this->_userFd, sendMessage.c_str(), sendMessage.size(), 0); // RPL = ERR_NEEDMOREPARAMS (461)
        return;
    }
    Channel *findChannel = server.findChannel(arg[1]);
    if (findChannel == NULL)
    {
        sendMessage = nameServer + " 403 " + this->_nickname + " " + arg[1] + " :Channel Not Found \r\n";
        Server::sendCheck(this->_userFd, sendMessage.c_str(), sendMessage.size(), 0); // RPL = ERR_NOSUCHCHANNEL (403)
        return;
    }
    if (findChannel->checkUser(*this) == false)
    {
        sendMessage = nameServer + " 442 " + this->_nickname + " " + findChannel->getName() + " :You are not part of the channel \r\n";
        Server::sendCheck(this->getUserFd(), sendMessage.c_str(), sendMessage.size(), 0); // ERR_NOTONCHANNEL 442
        return;
    }
    if (findChannel->getInviteOnly() == true && findChannel->checkUserAdmin(*this) == false)
    {
        sendMessage = nameServer + " 482 " + this->_nickname + " " + findChannel->getName() + " :You are not operator of this channel \r\n";
        Server::sendCheck(this->getUserFd(), sendMessage.c_str(), sendMessage.size(), 0); // ERR_CHANOPRIVSNEEDED
        return;
    }
    sendMessage = nameServer + " 341 " + this->_nickname + " " + arg[0] + " " + arg[1] + "\r\n"; //RPL_INVITING (341) 
    findChannel->addInviteUser(arg[0]);
    Server::sendCheck(this->getUserFd(), sendMessage.c_str(), sendMessage.size(), 0);


}
