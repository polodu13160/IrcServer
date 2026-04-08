#include "../Define.hpp"
#include "../Server.hpp"

typedef struct sockaddr SOCKADDR;

void  initializeServer(Server &server, char **args) {

	const SOCKET serverId = socket(AF_INET, SOCK_STREAM, 0);
	if (serverId == SOCKET_ERROR) {
		throw Server::errorServerSocket();
	}
	server.setServerId(serverId);

	server.setServerPass(std::string(args[2]));
	server.sockaddrInit(std::string(args[1]));
	std::cout << server;

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
