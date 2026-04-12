#include "cmd.hpp"

void	nickCmd(User *user, std::string nickName) {
	user->setNickname(nickName);


}