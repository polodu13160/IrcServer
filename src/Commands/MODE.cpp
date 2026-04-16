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

void	handleInviteMode(Server &server, Channel &chann, bool sign, std::vector<std::string> &modeStr) {

	if (sign == true)
		changeMode(chann._modeStock, MODE_INVITE_O, true);
	else
		changeMode(chann._modeStock, MODE_INVITE_O, false);
}

void	handleTopicMode(Server &server, Channel &chann, bool sign, std::vector<std::string> &modeStr) {

	if (sign == true) 
		changeMode(chann._modeStock, MODE_TOPIC_RESTRICT, true);
	else
		changeMode(chann._modeStock, MODE_TOPIC_RESTRICT, false);
}

void	handleKeyMode(Server &server, Channel &chann, bool sign, std::vector<std::string> &modeStr) {

	if (sign == true) {
		changeMode(chann._modeStock, MODE_KEY_SET, true);
		chann.setPassword(modeStr[2]);
	}
	else {
		changeMode(chann._modeStock, MODE_KEY_SET, false);
	}
}

void	handleLimitMode(Server &server, Channel &chann, bool sign, std::vector<std::string> &modeStr) {

	if (sign == true)
		chann.setUserLimit(true);
	else
		chann.setUserLimit(false);
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
	// if (chann.)
	// 	Verifier si dans chann operator  this est present !

	for (size_t i = 0; i < str.size(); i++) {

		if (str[i] == '-' || str[i] == '+') {
			if (str[i] == '-')
				sign = false;
			else
				sign = true;
		}
		else {
			e_modes mode = charToMode(str[i]);

			switch (mode) {

				case MODE_INVITE_O :
					handleInviteMode(server, chann, sign, modeStr);
					break;
				case MODE_KEY_SET :
					handleKeyMode(server, chann, sign, modeStr);
					break;
				case MODE_LIMIT_SET :
					handleLimitMode(server, chann, sign, modeStr);
					break;
				case MODE_OPERATOR :
					// handleOperatorMode(server, sign, modeStr);
					break;
				case MODE_TOPIC_RESTRICT :
					handleTopicMode(server, chann, sign, modeStr);
					break;
				case MODE_BAD :
					// send err_badmod
			}
		}

	}

}
