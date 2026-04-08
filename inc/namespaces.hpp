#ifndef _NAMESPACES_H
# define _NAMESPACES_H

#include <string>

namespace utilsMessage
{
    void messageToClient(int fdClientReception, std::string *numericsCode, std::string &sender, std::string *channel, std::string command, ...);
    void messageToServer(const char *text, ...);
}



#endif // _NAMESPACES_H