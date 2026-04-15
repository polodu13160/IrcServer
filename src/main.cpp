#include "../inc/Define.hpp"
#include "../inc/Server.hpp"
#include <sstream>
#include <cstring>
#include <sys/epoll.h>

#include "../inc/User.hpp"

typedef struct sockaddr SOCKADDR;


void  initializeServer(Server &server, char **args) {
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

	int clientFd = 0;

	while (true) {
		const int ready = epoll_wait(epollInstance, userEvent, 64, -1);

		for (int i = 0; i < ready; i++) {
			if (userEvent[i].data.fd == server.getServerId()) {
				struct sockaddr_in clientAddr;
				socklen_t clientAddrLen = sizeof(clientAddr);

				clientFd = accept(server.getServerId(), reinterpret_cast<struct sockaddr*>(&clientAddr), &clientAddrLen);

				if (clientFd != -1) {
					fcntl(clientFd, F_SETFL, fcntl(clientFd, F_GETFL) | O_NONBLOCK);

					struct epoll_event ev;
					std::memset(&ev, 0, sizeof(ev));
					ev.events = EPOLLIN;
					ev.data.fd = clientFd;
					epoll_ctl(epollInstance, EPOLL_CTL_ADD, clientFd, &ev);
					server.setUserfd(clientFd);
					std::cout << "Connexion acceptée Nouveau FD client : " << clientFd << std::endl;
				}
			}
			else {
				char buffer[128];

				std::memset(buffer, 0, 128);

				recv(userEvent[i].data.fd, &buffer, 128, 0);

				int i = 0;
				while (buffer[i]) {
					if (buffer[i] == '0')
						buffer[i] = '8';
					i++;
				}
				getMsg(server, buffer, clientFd);
				// TokenizeMsg(buffer);
				std::cout << buffer << std::endl;
				// if (std::strstr(buffer, "\r\n") ) {
				// 	std::cout << "YES" << std::endl;
				// }


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
