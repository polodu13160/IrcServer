#include "CmdDispatch.hpp"
#include <sstream>
#include <ctime>

void User::topicCmd(Server &server, const std::vector<std::string> &args)
{
    if (this->checkRegistration(server) == false)
        return;
    std::string nameServer = ":" + server._ip;
    std::string sendMessage;
    if (args.size() < 1)
    {
        sendMessage = nameServer + " 461 " + this->_nickname + " TOPIC" + " :Not enough parameters [#channel] optionnel: :NewTopic \r\n";
        Server::sendCheck(this->getUserFd(), sendMessage.c_str(), sendMessage.size(), 0); 
        return;
    }
    Channel *channel = server.findChannel(args[0]);
    if (channel == NULL)
    {
        sendMessage = nameServer + " 403 " + this->_nickname + " " + args[0] + " :Channel not found \r\n";
        Server::sendCheck(this->getUserFd(), sendMessage.c_str(), sendMessage.size(), 0); 
        return;
    }
    if (channel->checkUser(*this) == false)
    {
        sendMessage = nameServer + " 442 " + this->_nickname + " " + channel->getName() + " :You are not part of the channel \r\n";
        Server::sendCheck(this->getUserFd(), sendMessage.c_str(), sendMessage.size(), 0); 
        return;
    }
    if (args.size() >= 2)
    {
        std::string tmp = args[1];
        if (tmp[0] == ':')
            tmp.erase(0, 1);

        if (checkMode(channel->_modeStock, MODE_TOPIC_RESTRICT) == true && channel->checkUserAdmin(*this) == false)
        {
            
            sendMessage = nameServer + " 482 " + this->_nickname + " " + channel->getName() + " :You are not operator of this channel \r\n";
            Server::sendCheck(this->getUserFd(), sendMessage.c_str(), sendMessage.size(), 0); 
            return;
        }
        if (tmp[0] == ':' && tmp.size() == 1)
            channel->setTopic("");
        else
            channel->setTopic(tmp.c_str());

        sendMessage = this->_nickname + "!" + this->getUsername() + "@" + this->_ip + " TOPIC " + channel->getName() + " :" + channel->getTopic() + "\r\n";
        if (sendMessage.size() >= MAX_SIZE_MESSAGE)
        {
            sendMessage.erase(511);
            sendMessage += "\r\n";
        }
        channel->sendMsgUserForOthersUsersChannel(*this, sendMessage);
        Server::sendCheck(this->getUserFd(), sendMessage.c_str(), sendMessage.size(), 0);
        channel->setNickNameModifTopicLast(this->_nickname);
        channel->setTimeUnixModifTopicLast(server.timeNow());
    }
    else
    {
        if (channel->getTopic().empty() == true)
        {
            
            sendMessage = nameServer + " 331 " + this->_nickname + " " + channel->getName() + " :" + "There is nothing to see here this channel is meaningless" + "\r\n";

            Server::sendCheck(this->getUserFd(), sendMessage.c_str(), sendMessage.size(), 0);
        }
        else
        {
            sendMessage = nameServer + " 332 " + this->_nickname + " " + channel->getName() + " :" + channel->getTopic() + "\r\n";
            Server::sendCheck(this->getUserFd(), sendMessage.c_str(), sendMessage.size(), 0);
            sendMessage = nameServer + " 333 " + this->_nickname + " " + channel->getName() + " " + channel->getNickNameModifTopicLast() + " " + channel->getTimeUnixModifTopicLast() + "\r\n";
            Server::sendCheck(this->getUserFd(), sendMessage.c_str(), sendMessage.size(), 0);
        }
    }
}
