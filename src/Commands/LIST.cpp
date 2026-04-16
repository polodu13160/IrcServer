#include "User.hpp"

void User::listCmd(Server &server, std::vector<std::string> channels_string)
{

    std::string serverName = HOST;
    serverName.insert(0,":");
    std::string lineSend = serverName + " 321 " + this->_nickname + " Channel :Users  Name\r\n";
    send(this->getUserFd(), lineSend.c_str(), lineSend.length(), 0); // RPL_LISTSTART
    if (channels_string.empty() == true)
    {
        std::map<std::string, Channel>::iterator it;

        for (it = server._chanMap.begin(); it != server._chanMap.end(); it++)
        {
            std::stringstream prepareSend;
            prepareSend << serverName << " 322 " << this->_nickname
                        << " " << it->second.getName()
                        << " " << it->second.getUsers().size()
                        << " :" << it->second.getTopic() << "\r\n";

            lineSend = prepareSend.str();
            send(this->getUserFd(), lineSend.c_str(), lineSend.length(), 0); // RPL_LIST
        }
    }
    else
    {
        for (size_t i = 0; i < channels_string.size(); i++)
        {
            Channel *channelFind = server.findChannel(channels_string[i]);
            if (channelFind != NULL)
            {
                std::stringstream prepareSend;
                prepareSend << serverName << " 322 " << this->_nickname
                            << " " << channelFind->getName()
                            << " " << channelFind->getUsers().size()
                            << " :" << channelFind->getTopic() << "\r\n";
                lineSend = prepareSend.str();
                send(this->getUserFd(), lineSend.c_str(), lineSend.length(), 0); // RPL_LIST
            }
        }
    }
    lineSend = serverName + " 323 " + this->_nickname + " :End of /LIST \r\n";
    send(this->getUserFd(), lineSend.c_str(), lineSend.length(), 0); // RPL_LISTEND
}
