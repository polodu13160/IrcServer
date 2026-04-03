
#include <cstdarg>
#include <string>
#include <iostream>


//finir par null dans le text a push
//ex = messageToServer("tutu","toto",NULL);
void messageToServer(const char* text, ...)
{
    if (text == NULL)
        return ;
    std::va_list args;
    std::cout << text;
    va_start(args, text);
    const char* val = va_arg(args, const char*);
    while (val != NULL)
    {
        std::cout << val;
        val = va_arg(args, const char*);
    }
    va_end(args);
    std::cout << std::endl;
}

void messageToClient(int fdClient, )