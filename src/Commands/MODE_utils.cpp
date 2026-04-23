#include "../../inc/User.hpp"
#include <bitset>


static bool	checkArgs(const Channel &channel, const s_parseMode &mode, const User &userSend, char c) {
	if (mode.arg.empty()) {
		const std::string signStr = mode.sign ? "+" : "-";
		const std::string line = ":192.0.0.1 461 " + userSend.getNickname() + " " + c + " MODE " + channel.getName() + " " + signStr + c + " : Not enough parameter\r\n";
		send(userSend.getUserFd(), line.c_str(), line.size(), 0);
		return false;
	}
	return true;
}

// CHANNEL INVITE ONLY HANDLE


void	handleInviteMode(Channel &channel, const s_parseMode &mode) {

	if (mode.sign == true)
		changeMode(channel._modeStock, MODE_INVITE_O, true);
	else
		changeMode(channel._modeStock, MODE_INVITE_O, false);
}

// CHANNEL TOPC HANDLE


void	handleTopicMode(Channel &channel, const s_parseMode &mode) {

	if (mode.sign == true)
		changeMode(channel._modeStock, MODE_TOPIC_RESTRICT, true);
	else
		changeMode(channel._modeStock, MODE_TOPIC_RESTRICT, false);
}

// CHANNEL PASSWORD HANDLE

void	handleKeyMode(Channel &channel, const s_parseMode &mode, User &userSend) {

	if (!checkArgs(channel, mode, userSend, 'k'))
		return;
	if (mode.arg.size() > 23)
		return;
	for (size_t i = 0; i < mode.arg.size(); i++) {
		if (mode.arg[i] == ':' || mode.arg[i] == ',' || mode.arg[i] <= 32) {
			std::string line = ":127.0.0.1 696 ";
			//err return SEND
			return;
		}
	}
	if (mode.sign == true) {
		changeMode(channel._modeStock, MODE_KEY_SET, true);
		channel.setPassword(mode.arg);
	}
	else {
		changeMode(channel._modeStock, MODE_KEY_SET, false);
	}
}

// CHANNEL LIMIT HANDLE


void	handleLimitMode(Channel &channel, const s_parseMode &mode) {

	std::stringstream ss;
	std::string			rest;
	ss << mode.arg;

	unsigned int tmp;

	ss >> tmp;
	if (!tmp || (ss >> rest)) {
		// Bad User Lmit
		return;
	}
	if (mode.sign == true) {
		channel.setUserLimit(tmp);
		changeMode(channel._modeStock, MODE_LIMIT_SET, true);
	}
	else
		changeMode(channel._modeStock, MODE_LIMIT_SET, false);
}


// OPERATOR HANDLE

void	handleOperatorMode(Channel &channel, const s_parseMode &mode, User &userSend) {
	User *user = channel.getUserByNickname(mode.arg);

	if (!user) {
		std::cout << "Y A PAS " << std::endl;
		std::string	signStr = mode.sign ? "+" : "-";
		const std::string line = ":192.0.0.1 441 " + userSend.getNickname() + " " + mode.arg + " " + channel.getName() + " :They aren't on that channel\r\n";
		send(userSend.getUserFd(), line.c_str(), line.size(), 0);
		return;
	}
	if (mode.sign == true)
		channel.changeUserOp(*user, true);
	else
		channel.changeUserOp(*user, false);

	const std::string signStr = mode.sign ? "+" : "-";
	std::string line = ":" + userSend.getNickname() + " MODE " + channel.getName() + " " + signStr + "o " + user->getNickname() + "\r\n";
	channel.sendMsgUserForOthersUsersChannel(userSend, line);
	send(userSend.getUserFd(), line.c_str(), line.size(), 0);
}