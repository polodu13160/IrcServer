#include "User.hpp"



void User::listCmd(Server& server, User& user, std::vector<std::string> &channels_string)
{
    (void)channels_string;
    std::string serverName = ":127.0.0.1";
    std::string lineSend = serverName + " 321 " + user._nickname + " Channel :Users  Name\r\n"; 
    send(user.getUserFd(), lineSend.c_str() ,lineSend.length(), 0); //RPL_LISTSTART
    for (size_t i = 0; i < server._chanVector.size(); i++)
    {
        std::stringstream prepareSend;
        prepareSend << serverName << " 322 " << user._nickname 
        << " " << server._chanVector[i].getName() 
        << " " << server._chanVector[i].getUsers().size()
        << " :" << server._chanVector[i].getTopic() << "\r\n";

        lineSend = prepareSend.str();
        send(user.getUserFd(), lineSend.c_str() ,lineSend.length(), 0); //RPL_LIST
    }
    lineSend = serverName + " 323 " + user._nickname + " :End of /LIST \r\n";
    send(user.getUserFd(), lineSend.c_str() ,lineSend.length(), 0); //RPL_LISTEND
}



