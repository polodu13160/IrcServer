#include "../../inc/User.hpp"
#include <bitset>


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
				s_parseMode tmp;
				tmp.mode = charToMode(modeStr[1][i]);
				tmp.sign = sign;
			if (start < modeStr.size())
				tmp.arg = modeStr[start++];
			args.push_back(tmp);
		}
		else if (modeStr[1][i] == 'l') {
			s_parseMode tmp;
			tmp.mode = charToMode(modeStr[1][i]);
			tmp.sign = sign;
			if (start < modeStr.size()) {
				if (sign == true)
					tmp.arg = modeStr[start++];
			}
			args.push_back(tmp);
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

	if (this->checkRegistration(server) == false)
		return;
	Channel	*channel = server.findChannel(modeStr[0]);
	if (channel == NULL) {
		const std::string line = ":" + this->_ip + " 403 " + this->_nickname + " " + modeStr[0] + " :No such channel\r\n";
		Server::sendCheck(this->_userFd, line.c_str(), line.size(), 0);
		return;
	}
	if (channel->checkUserAdmin(*this) == false) {
		const std::string line = ":" + this->_ip + " 482 " + this->_nickname + " " + modeStr[0] + " :You're not channel operator\r\n";
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
				handleKeyMode(*channel, args[i], *this, server);
				break;
			case MODE_LIMIT_SET :
				handleLimitMode(*channel, args[i], *this, server);
				break;
			case MODE_OPERATOR :
				handleOperatorMode(*channel, args[i], *this, server);
				break;
			case MODE_TOPIC_RESTRICT :
				handleTopicMode(*channel, args[i]);
				break;
			default :
				std::string line = ":" + this->_ip + " 472 " + this->_nickname + " " + modeStr[0] + " :Bad MODE parameter\r\n";
				Server::sendCheck(this->_userFd, line.c_str(), line.size(), 0);
		}
	}
}
