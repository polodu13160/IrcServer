#include "../../inc/User.hpp"
#include <bitset>

struct s_parseMode {
	mode_t mode;
	std::string arg;
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

// void	handleOperatorMode(Server &server, User &user, bool sign) {
//
// 	Channel	*chann = server.findChannel(modeStr[1]);
// 	if (chann == NULL) {
// 		std::cout << "Channel doesn't exist" << std::endl;
// 		return;
// 	}
// 	/*
// 	 * if (sign == true)
// 	 *	chann.addOperator(User)
// 	 *
// 	 * else
// 	 *	non
// 	 */
// }

void	handleInviteMode(Server &server, Channel &chann, const bool sign) {

	if (sign == true)
		changeMode(chann._modeStock, MODE_INVITE_O, true);
	else
		changeMode(chann._modeStock, MODE_INVITE_O, false);
}

void	handleTopicMode(Server &server, Channel &chann, const bool sign, std::vector<std::string> &modeStr) {

	if (sign == true) 
		changeMode(chann._modeStock, MODE_TOPIC_RESTRICT, true);
	else
		changeMode(chann._modeStock, MODE_TOPIC_RESTRICT, false);
}

void	handleKeyMode(Server &server, Channel &chann, const bool sign, std::string &modeStr) {

	if (modeStr.size() > 23)
		return;
	for (size_t i = 0; i < modeStr.size(); i++) {
		if (modeStr[i] == ':' || modeStr[i] == ',' || modeStr[i] <= 32) {

			std::string line = ":127.0.0.1 696 ";
			return;
		}
	}
	if (sign == true) {


		changeMode(chann._modeStock, MODE_KEY_SET, true);
		chann.setPassword(modeStr[2]);
	}
	else {
		changeMode(chann._modeStock, MODE_KEY_SET, false);
	}
}

void	handleLimitMode(Server &server, Channel &chann, const bool sign, std::vector<std::string> &modeStr) {

	if (sign == true)
		chann.setUserLimit(true);
	else
		chann.setUserLimit(false);
}

std::vector<std::string> parseArgsNb(std::vector<std::string> &modeStr) {

	int nb = 0;
	int start = 2;
	bool sign = true;
	std::vector<std::string> args;
	for (int i = 0; i < modeStr[1].size(); i++) {
		if (modeStr[1][i] == '+')
			sign = true;
		if (modeStr[1][i] == '-')
			sign = false;
		if (modeStr[1][i] == 'k' || modeStr[1][i] == 'o') {
			if (start < modeStr.size()) {
				args.push_back(modeStr[start++]);
				++nb;
			}
			else
				std::cerr << "no args" << std::endl;
		}
		if (modeStr[1][i] == 'l' && sign == true) {
			if (start < modeStr.size()) {
				args.push_back(modeStr[start++]);
				++nb;
			}
			else
				std::cerr << "no args" << std::endl;
		}
	}
	if (nb == modeStr.size() - 2)
		return args;
	return NULL;
}



void User::modeCmd(Server& server, std::vector<std::string> &modeStr) {

	bool	sign = true;
	const std::string	str = modeStr[0];


	Channel	*chann = server.findChannel(modeStr[1]);
	if (chann == NULL) {
		const std::string line = ":127.0.0.1 403 " + this->_nickname + " " + modeStr[1] + " :No such channel\r\n";
		send(this->_userFd, line.c_str(), line.size(), 0);
		return;
	}
	if (chann->checkUserAdmin(*this) == false) {
		const std::string line = ":127.0.0.1 482 " + this->_nickname + " " + modeStr[1] + " :You're not channel operator\r\n";
		send(this->_userFd, line.c_str(), line.size(), 0);
		return;
	}
	std::vector<std::string> args = parseArgsNb(modeStr);
	if (args.empty()) {
		std::cout << "Not good args" << std::endl;
		return;
	}
	int size = 0;
	for (size_t i = 0; i < str.size(); i++) {

		if (str[i] == '+')
			sign = true;
		if (str[i] == '-')
			sign = false;
		else {
			e_modes mode = charToMode(str[i]);

			switch (mode) {

				case MODE_INVITE_O :
					if (size < args.size())
					handleInviteMode(server, *chann, sign);
					break;
				case MODE_KEY_SET :
					if (size < args.size())
						handleKeyMode(server, *chann, sign, args[size++]);
					break;
				case MODE_LIMIT_SET :
					handleLimitMode(server, *chann, sign, modeStr);
					break;
				case MODE_OPERATOR :
					if (size < args.size())
						// handleOperatorMode(server, sign, modeStr);
					break;
				case MODE_TOPIC_RESTRICT :
					handleTopicMode(server, *chann, sign, modeStr);
					break;
				case MODE_BAD :
					// send err_badmod
			}
		}

	}

}
