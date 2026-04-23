#include "cmdPars.hpp"
#include <sstream>
#include <ctime>



void User::topicCmd(Server &server, std::vector<std::string> args)
{

    std::string nameServer = HOST;
    nameServer.insert(0, ":");
    std::string sendMessage;
    if (args[0].empty())
    {
        // si pas d'arguments ce fou envoie juste topic sans rien
        sendMessage = nameServer + " 461 " + this->_nickname + " TOPIC" + " :Pas assez de parametres ptn [#channel] optionnel: :NewTopic";
        Server::sendCheck(this->getUserFd(), sendMessage.c_str(), sendMessage.size(), 0); // ERR_NEEDMOREPARAMS
        return;
    }
    Channel *channel = server.findChannel(args[0]);
    if (channel == NULL)
    {
        //si le channel n'est pas trouve
        sendMessage = nameServer + " 403 " + this->_nickname + " " + args[0] + " :Channel not found \r\n";
        Server::sendCheck(this->getUserFd(), sendMessage.c_str(), sendMessage.size(), 0); // ERR_NOSUCHCHANNEL (403)
        return;
    }
    if (channel->checkUser(*this) == false)
    {
        //si l'utilisateur n'est pas dans le channel
        sendMessage = nameServer + " 442 " + this->_nickname + " " + channel->getName() + " :You are not part of the channel \r\n";
        Server::sendCheck(this->getUserFd(), sendMessage.c_str(), sendMessage.size(), 0); // ERR_NOTONCHANNEL
        return;
    }
    if (args.size() >= 2)
    {
        //si il veut modifier le topic
        if (args[1][0] == ':')
            args[1].erase(0,1);

        if (checkMode(channel->_modeStock, MODE_TOPIC_RESTRICT) == true && channel->checkUserAdmin(*this) == false)
        {
            //si ya des permissions et que l'utilisateur n'est pas admin
            sendMessage = nameServer + " 482 " + this->_nickname + " " + channel->getName() + " :You are not operator of this channel \r\n";
            Server::sendCheck(this->getUserFd(), sendMessage.c_str(), sendMessage.size(), 0); // ERR_CHANOPRIVSNEEDED
            return;
        }
        // si il envoie rien donc juste : (si c lutilisateur qui met :)
        if (args[1][0] == ':' && args[1].size() == 1)
            channel->setTopic("");
        else
            channel->setTopic(args[1].c_str());
        //preparation de la modif a envoyer a tout le monde
        sendMessage = this->_nickname + "!" + this->getUsername() + " TOPIC " + channel->getName() + " :" + channel->getTopic() + "\r\n";
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

        // c ici que tu rentreras lucas pour recup topic
        if (channel->getTopic().empty() == true)
        {
            //si pas de topic sur le server
            sendMessage = nameServer + " 331 " + this->_nickname + " " + channel->getName() + " :" + "Il n'y a rien a voir ici ce channel est vide de sens" + "\r\n";
            //RPL_NOTOPIC
            Server::sendCheck(this->getUserFd(), sendMessage.c_str(), sendMessage.size(), 0);
        }
        else
        {
            //si pas topic sur le server
            sendMessage = nameServer + " 332 " + this->_nickname + " " + channel->getName() + " :" + channel->getTopic() + "\r\n";
            //RPL_TOPIC
            Server::sendCheck(this->getUserFd(), sendMessage.c_str(), sendMessage.size(), 0);
            sendMessage = nameServer + " 333 " + this->_nickname + " " + channel->getName() + " " + channel->getNickNameModifTopicLast() + " " + channel->getTimeUnixModifTopicLast() + "\r\n";
            //RPL_TOPICWHOTIME
            Server::sendCheck(this->getUserFd(), sendMessage.c_str(), sendMessage.size(), 0);

        }
    }
}
