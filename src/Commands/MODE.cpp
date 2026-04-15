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

e_modes	charToMode(char c) {
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


void	handleInviteMode(bool sign, Server &server, std::vector<std::string> &modeStr) {


}



void User::modeCmd(Server& server, const std::vector<std::string> &modeStr) {

	bool	sign = true;
	const std::string	str = modeStr[0];

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
					// handleInviteMode(sign);
				case MODE_KEY_SET :
					// handleKeyMode(sign, modeStr);
				case MODE_LIMIT_SET :
					// handleLimitMode(sign, modeStr);
				case MODE_OPERATOR :
					// handleOperatorMode(sign)
				case MODE_TOPIC_RESTRICT :
					// handleTopicRestrict(sign)
				case MODE_BAD :
					// send err_badmod
			}
		}

	}

}
