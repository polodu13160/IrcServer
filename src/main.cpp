#include "../inc/Define.hpp"
#include "../inc/Server.hpp"
#include <sstream>
#include <cstring>
#include <fcntl.h>

#include "../inc/User.hpp"

typedef struct sockaddr SOCKADDR;


int main (int ac, char **av) {
	if (ac == 3) {

		try {
			Server  server(av[2], av[1]);
		}
		catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}

	}
}
