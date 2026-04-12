#include "../Define.hpp"
#include "Server/Server.hpp"
#include <sstream>
#include <fcntl.h>
#include <cstring>

#include "MessageParsing/User.hpp"

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
	server.sockaddrInit();
	if (bind(server.getServerId(), reinterpret_cast<sockaddr *>(&server.getServerSin()), sizeof(SOCKADDR)) == -1)
		throw Server::errorServerSocket();
	listen(server.getServerId(), SOMAXCONN);
	int tmp = fcntl(server.getServerId(), F_GETFL);
	tmp = tmp | O_NONBLOCK;
	fcntl(server.getServerId(), F_SETFL, tmp);
	int epollInstance = epoll_create1(EPOLL_CLOEXEC);
	epoll_event serverEvent = {};
	serverEvent.events = EPOLLIN;
	serverEvent.data.fd = server.getServerId();

	epoll_ctl(epollInstance ,EPOLL_CTL_ADD, server.getServerId(), &serverEvent);

	epoll_event userEvent[64];
	std::cout << server << std::endl;

	while (true) {
		int ready = epoll_wait(epollInstance, userEvent, 64, -1);

		for (int i = 0; i < ready; i++) {
			if (userEvent[i].data.fd == server.getServerId()) {
				struct sockaddr_in clientAddr;
				socklen_t clientAddrLen = sizeof(clientAddr);

				int clientFd = accept(server.getServerId(), reinterpret_cast<struct sockaddr*>(&clientAddr), &clientAddrLen);

				if (clientFd != -1) {
					fcntl(clientFd, F_SETFL, fcntl(clientFd, F_GETFL) | O_NONBLOCK);

					struct epoll_event ev;
					std::memset(&ev, 0, sizeof(ev));
					ev.events = EPOLLIN;
					ev.data.fd = clientFd;

					epoll_ctl(epollInstance, EPOLL_CTL_ADD, clientFd, &ev);
					std::cout << "Connexion acceptée Nouveau FD client : " << clientFd << std::endl;
				}
			}
			else {
				char buffer[128];

				std::memset(buffer, 0, 128);

				recv(userEvent[i].data.fd, &buffer, 128, 0);
				server.createUserInstance(3, buffer);
				std::cout << buffer << std::endl;
				if (std::strstr(buffer, "\r\n") ) {
					std::cout << "YES" << std::endl;
				}


			}
		}
	}
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
