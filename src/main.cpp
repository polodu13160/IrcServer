#include "../inc/Define.hpp"
#include "../inc/Server.hpp"
#include <sstream>
#include <cstring>
#include <fcntl.h>

#include "../inc/User.hpp"
#include <stdexcept>


#include <signal.h>
#include <stdio.h>
#include <strings.h>

typedef struct sockaddr SOCKADDR;

void sigint_handler(int signal)
{
 if (signal == SIGINT)
	throw std::runtime_error("\nStop");
}

void set_signal_action(void)
{
 
 struct sigaction act;
 bzero(&act, sizeof(act));
 act.sa_handler = &sigint_handler;
 sigaction(SIGINT, &act, NULL);
}

int main (const int ac, char **av) {
	if (ac == 3 && ac != 2) {

		try {
			set_signal_action();
			Server  server(av[1], av[2]);
			server.setSocketParams();
			server.EpollInstance();
		}
		catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
	else
		std::cerr << "Please provide 2 Arguments as : ./IrcServer [PORT] [PASSWORD]" << std::endl;
}
