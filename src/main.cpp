#include "../Define.hpp"
#include "../Server.hpp"

typedef struct sockaddr SOCKADDR;

void  initializeServer(Server &server) {

	const SOCKET serverId = socket(AF_INET, SOCK_STREAM, 0);
	if (serverId == SOCKET_ERROR) {
		throw Server::errorServerSocket();
	}
	std::cout << "Socket crée : " << serverId << std::endl;
	server.setServerId(serverId);

}




int main () {

	Server  server;

	initializeServer(server);

	SOCKADDR_IN sin;

	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(6697);
}