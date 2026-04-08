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

	listen(server.getServerId(), 3);

	socklen_t addrlen = sizeof(server.getServerSin());

	int new_socket = accept(server.getServerId(),  reinterpret_cast<sockaddr *>(&server.getServerSin()), &addrlen);

	std::cout << "New client is connect with fd : " << new_socket <<std::endl;
	std::cout << server;

	std::string msg[1024];
	size_t value = read(new_socket, msg, -1);
	std::cout << msg << std::endl;

	int epfd = epoll_create1(EPOLL_CLOEXEC);

	epoll_event epEvent = {};

	epoll_ctl(epfd, EPOLL_CTL_ADD, new_socket, &epEvent);
	epoll_wait(epfd, &epEvent,1000, 0);

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
