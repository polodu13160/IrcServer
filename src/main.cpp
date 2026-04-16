#include "../inc/Define.hpp"
#include "../inc/Server.hpp"
#include <sstream>
#include <cstring>
#include <fcntl.h>

#include "../inc/User.hpp"

typedef struct sockaddr SOCKADDR;


int main (const int ac, char **av) {
	if (ac == 3) {

		try {
			Server  server(av[1], av[2]);
		}
		catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
	else
		std::cerr << "Please provide 2 Arguments as : ./IrcServer [PORT] [PASSWORD]" << std::endl;
}
