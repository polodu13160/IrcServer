

#include "bot.hpp"

int	main() {


	std::ifstream file("insult");
	if (!file.is_open()) {
		std::cerr << "Error opening the file" << std::endl;
		return 1;
	}
	Bot bot(file);


	return 0;
}