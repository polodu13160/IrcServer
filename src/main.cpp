#include "../Define.hpp"
#include "Server/Server.hpp"
#include <sstream>

typedef struct sockaddr SOCKADDR;

int	convertPort(const char *arg, Server *server) {

	std::stringstream	ss;
	int					tmp = 0;
	char				rest;
	ss << arg;

	if (!(ss >> tmp) || (ss >> rest))
		return -1;
	if (tmp < 1024 || tmp > 65535)
		return -1;
	server->setServerPort(tmp);
	return 0;
}

void  initializeServer(Server &server, char **args) {

	const SOCKET serverId = socket(AF_INET, SOCK_STREAM, 0);
	if (serverId == SOCKET_ERROR) {
		throw Server::errorServerSocket();
	}
	server.setServerId(serverId);

	const int opt = 1;
	if (setsockopt(server.getServerId(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) != 0)
		throw Server::errorServerSocket();
	if (convertPort(args[2], &server) == -1)
		throw Server::errorServerSocket();
	std::cout << server << std::endl;

}


int main (int ac, char **av) {
	if (ac == 3) {

		try {
			Server  server;
			initializeServer(server, av);
		}
		catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}

	}
}
