
#include "namespaces.hpp"
#include <cstdarg>
#include <string>
#include <iostream>
#include <sys/socket.h>

/**
 * @brief send message for terminal of server
 * 
 * @param text first message followed by a space (THE SPACE IS INCLUDED IN FUNC)
 * @param ... others messages followed by  spaces, 
 * @attention the last param must to  be NULL 
 */
void utilsMessage::messageToServer(const char *text, ...)
{
    if (text == NULL)
        return;
    std::va_list args;
    std::cout << text;
    va_start(args, text);
    const char *val = va_arg(args, const char *);
    const char *valNext;
    while (val != NULL)
    {
        if ((valNext = va_arg(args, const char *)) == NULL)
            std::cout << val;
        else 
            std::cout << val << " ";
        val = valNext;
    }
    va_end(args);
    std::cout << std::endl;
}


/**
 * @brief message send to Irc Client FD;
 * 
 * @param fdClientReception the IRC client Socket
 * @param numericsCode The addr of numerics Error Protocol IRC (NULL if not used)
 * @param sender The name of the sender (Don't forget the @ if operateur of channel)
 * @param channel The addr of name of the Channel (Don't forget the #) (NULL if not used)
 * @param command The command ex : JOIN PRVMSG...
 * @param ... the param and for the penultimate the message to send 
 * @attention Don't forget the NULL for the end of variadics arguments
 * @return possible throw if send doesn't worked
 */
void utilsMessage::messageToClient(int fdClientReception, std::string *numericsCode, std::string sender, std::string *channel, std::string command, ...)
{
    std::string header;
    std::string msg;
    header.append(":");
    header.append(sender + " ");
    if (numericsCode != NULL)
        header.append(*numericsCode + " ");
    header.append(command);
    if (channel != NULL)
        header.append("#"+*channel + " ");
    std::va_list args;
    va_start(args, command);
    const char *text = va_arg(args, const char *);
    const char *nextText;
    while (text != NULL)
    {
        if ((nextText = va_arg(args, const char *)) == NULL)
        {
            msg.append(":");
            msg.append(text);
        }
        else
        {
            msg.append(text);
            msg.append(" ");
        }
        text = nextText;
    }
    msg.append("\r\n");
    va_end(args);
    if (msg.length() + header.length() > 510)
    {
        size_t posCut = 0;
        std::string cutMsg;
        size_t posSpaceInMsg;
        while (msg.length() + header.length() > 510)
        {
            posSpaceInMsg = msg.find_last_of(" ", 300);
            if (posSpaceInMsg + header.length() > 510)
            {
                cutMsg = msg.substr(posCut, 510 - header.length());
                posCut += 510 - header.length() + 1;
            }
            else
            {
                cutMsg = msg.substr(posCut, posSpaceInMsg);
                posCut += posSpaceInMsg + 1;
            }
            cutMsg.insert(0, header);
            send(fdClientReception, (void *)cutMsg.c_str(), cutMsg.length(), MSG_DONTWAIT);
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                // TODO: FAIRE MESSAGE ERREUR AVEC THROW
            }
        }
    }
    else
        send(fdClientReception, (void *)msg.c_str(), msg.length(), MSG_DONTWAIT);
    if (errno == EAGAIN || errno == EWOULDBLOCK)
    {
        // TODO: FAIRE MESSAGE ERREUR AVEC THROW
    }
}