#include "User.hpp"



void User::listCmd(Server& server, User& user, std::vector<std::string> &channels_string)
{
    std::string before = ":127.0.0.1 ";
    std::string lineSend = before + "321 " + user._username + " Channel :Users  Name\r\n";
    send(user.getUserFd(), lineSend.c_str() ,lineSend.length(), 0);
    for (size_t i = 0; i < server._chanVector.size(); i++)
    {
        lineSend = before + "322 " +user._username + " " + server._chanVector[i].getName() + " ";
        lineSend+= server._chanVector[i].getUsers().size()+ " :" + server._chanVector[i].getTopic() + "\r\n";
        send(user.getUserFd(), lineSend.c_str() ,lineSend.length(), 0);
    }
    lineSend = before + "323 " + user._username + " :End of /LIST \r\n";
}



