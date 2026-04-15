#include "User.hpp"

void User::listCmd(Server &server, std::vector<std::string> channels_string)
{
    std::string serverName = ":127.0.0.1";
    std::string lineSend = serverName + " 321 " + this->_nickname + " Channel :Users  Name\r\n";
    Server::messageToServer("0", NULL);
    send(this->getUserFd(), lineSend.c_str(), lineSend.length(), 0); // RPL_LISTSTART
    if (channels_string.empty() == true)
    {
        Server::messageToServer("1", NULL);
        for (size_t i = 0; i < server._chanVector.size(); i++)
        {
            Server::messageToServer("2", NULL);
            std::stringstream prepareSend;
            prepareSend << serverName << " 322 " << this->_nickname
                        << " " << server._chanVector[i].getName()
                        << " " << server._chanVector[i].getUsers().size()
                        << " :" << server._chanVector[i].getTopic() << "\r\n";

            lineSend = prepareSend.str();
            send(this->getUserFd(), lineSend.c_str(), lineSend.length(), 0); // RPL_LIST
        }
    }
    else 
    {
        Server::messageToServer("ttiti", NULL);
        Server::messageToServer(channels_string[0].c_str(), NULL);
    }
    Server::messageToServer("3", NULL);
    lineSend = serverName + " 323 " + this->_nickname + " :End of /LIST \r\n";
    send(this->getUserFd(), lineSend.c_str(), lineSend.length(), 0); // RPL_LISTEND
}
