

#include "bot.hpp"

int	main() {


	std::ifstream file("insult");
	if (!file.is_open()) {
		std::cerr << "Error opening the file" << std::endl;
		return 1;
	}
	try {
		Bot bot(file);
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}


	return 0;
}