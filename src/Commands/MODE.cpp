#include "../../inc/User.hpp"
#include <bitset>

struct s_parseMode {
	mode_t mode;
	std::string arg;
	bool sign;
};

bool	checkMode(const unsigned int &checkedMode, const e_modes MODE){

	const std::bitset<32>	tmp(checkedMode);
	if (tmp.test(MODE))
		return true;
	return false;
}

void	changeMode(unsigned int &checkedMode, const e_modes MODE, bool sign) {
	std::bitset<32>	tmp(checkedMode);

	if (sign == NEG_SIGN)
		tmp.set(MODE, false);
	else if (sign == POS_SIGN)
		tmp.set(MODE, true);
	checkedMode = static_cast<unsigned int>(tmp.to_ulong());
}

e_modes	charToMode(const char c) {
	switch (c) {

		case 't' :
			return MODE_TOPIC_RESTRICT;
		case 'k' :
			return MODE_KEY_SET;
		case 'o' :
			return MODE_OPERATOR;
		case 'i' :
			return MODE_INVITE_O;
		case 'l' :
			return MODE_LIMIT_SET;
		default :
			return MODE_BAD;
	}
}

void	handleInviteMode(Channel &channel, const s_parseMode &mode) {

	if (mode.sign == true)
		changeMode(channel._modeStock, MODE_INVITE_O, true);
	else
		changeMode(channel._modeStock, MODE_INVITE_O, false);
}

void	handleTopicMode(Channel &channel, const s_parseMode &mode) {

	if (mode.sign == true)
		changeMode(channel._modeStock, MODE_TOPIC_RESTRICT, true);
	else
		changeMode(channel._modeStock, MODE_TOPIC_RESTRICT, false);
}

void	handleKeyMode(Channel &channel, const s_parseMode &mode) {

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

void	handleOperatorMode(Channel &channel, const s_parseMode &mode, User &userSend) {
	User *user = channel.getUserByNickname(mode.arg);

	if (!user) {
		// send + return
		return;
	}
	if (mode.sign == true)
		channel.changeUserOp(*user, true);
	else
		channel.changeUserOp(*user, false);

	std::string signStr = mode.sign ? "+" : "-";
	std::string line = ":" + userSend.getNickname() + " MODE " + channel.getName() + " " + signStr + "o " + user->getNickname() + "\r\n";
	channel.sendMsgUserForOthersUsersChannel(userSend, line);
	send(userSend.getUserFd(), line.c_str(), line.size(), 0);
}

std::vector<s_parseMode> parseArgsNb(const std::vector<std::string> &modeStr) {

	size_t start = 2;
	bool sign = true;
	std::vector<s_parseMode> args;
	if (modeStr.size() == 1)
		return args;
	for (size_t i = 0; i < modeStr[1].size(); i++) {
		std::cout << "Current mode  : " << modeStr[1][i] << std::endl;
		if (modeStr[1][i] == '+')
			sign = true;
		else if (modeStr[1][i] == '-')
			sign = false;
		else if (modeStr[1][i] == 'k' || modeStr[1][i] == 'o') {
			if (start < modeStr.size()) {
				s_parseMode tmp;
				tmp.mode = charToMode(modeStr[1][i]);
				tmp.sign = sign;
				tmp.arg = modeStr[start++];
				args.push_back(tmp);
			}
			// else {
			// 	std::string line = ":192.0.0.1 431 " + this->_nickName + " " +	modeStr[0] + ": Not enought arguments\r\n";
			// 	Server::sendCheck(this->userFd, line, line.size(), 0);
			// }
		}
		else if (modeStr[1][i] == 'l') {
			if (start < modeStr.size()) {
				s_parseMode tmp;
				tmp.mode = charToMode(modeStr[1][i]);
				tmp.sign = sign;
				if (sign == true)
					tmp.arg = modeStr[start++];
				args.push_back(tmp);
				// else {
				// 	std::string line = ":192.0.0.1 431 " + this->_nickName + " " +	modeStr[0] + ": Not enought arguments\r\n";
				// 	Server::sendCheck(this->userFd, line, line.size(), 0);
				// }
			}
		}
		else if (modeStr[1][i] == 't' || modeStr[1][i] == 'i') {
			s_parseMode tmp;
			tmp.mode = charToMode(modeStr[1][i]);
			tmp.sign = sign;
			args.push_back(tmp);
		}
		else {
			s_parseMode tmp;
			tmp.mode = MODE_BAD;
			args.push_back(tmp);
		}
	}
	return args;
}



void User::modeCmd(Server& server, const std::vector<std::string> &modeStr) {

	Channel	*channel = server.findChannel(modeStr[0]);
	if (channel == NULL) {
		const std::string line = ":127.0.0.1 403 " + this->_nickname + " " + modeStr[0] + " :No such channel\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.size(), 0);
		return;
	}
	if (channel->checkUserAdmin(*this) == false) {
		const std::string line = ":127.0.0.1 482 " + this->_nickname + " " + modeStr[0] + " :You're not channel operator\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.size(), 0);
		return;
	}
	const std::vector<s_parseMode> args = parseArgsNb(modeStr);
	if (args.empty()) {
		std::cout << "Not good args" << std::endl;
		return;
	}
	std::cout << "Arguments is : " << args[0].arg << std::endl;
	for (size_t i = 0; i < args.size(); i++) {
		switch (args[i].mode) {
			case MODE_INVITE_O :
				handleInviteMode(*channel, args[i]);
				break;
			case MODE_KEY_SET :
				handleKeyMode(*channel, args[i]);
				break;
			case MODE_LIMIT_SET :
				handleLimitMode(*channel, args[i]);
				break;
			case MODE_OPERATOR :
				handleOperatorMode(*channel, args[i], *this);
				break;
			case MODE_TOPIC_RESTRICT :
				handleTopicMode(*channel, args[i]);
				break;
			default :
				std::string line = ":127.0.0.1 400 " + this->_nickname + " " + modeStr[0] + " :Bad MODE parameter\r\n";
		}
	}
}
