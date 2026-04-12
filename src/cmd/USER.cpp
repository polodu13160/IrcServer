#include "cmd.hpp"

void	userCmd(User *user, std::string userName) {
	user->setUsername(userName);
}