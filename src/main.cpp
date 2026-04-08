#include "../Define.hpp"
#include "../Server.hpp"

typedef struct sockaddr SOCKADDR;

void  initializeServer(Server &server) {

	const SOCKET serverId = socket(AF_INET, SOCK_STREAM, 0);
	if (serverId == SOCKET_ERROR) {
		throw Server::errorServerSocket();
	}
	server.setServerId(serverId);

	std::cout << server;

}


int main () {

	Server  server;

	initializeServer(server);
}