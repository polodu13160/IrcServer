
#include <signal.h>
#include <stdio.h>
#include <strings.h>
#include "Bot.hpp"

void sigint_handler(const int signal)
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

int	main() {


	std::ifstream file("insult");
	if (!file.is_open()) {
		std::cerr << "Error opening the file" << std::endl;
		return 1;
	}
	try {
		set_signal_action();
		Bot bot(file);
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}