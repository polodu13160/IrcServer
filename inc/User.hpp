#ifndef USER_HPP
# define USER_HPP

#include <iostream>
#include <sstream>
#include <vector>

#include "Channel.hpp"
#include "Server.hpp"
#include "Define.hpp"

class Server;
class Channel;

#define BOTNAME "bot"

struct s_parseMode {
	mode_t mode;
	std::string arg;
	bool sign;
};

class User {
	public :
	User();
	User(int userfd, std::string nickname, std::string username);
	~User(void);

	const std::string	&getNickname(void)const;
	const std::string	&getUsername(void)const;
	const std::string	&getRealname(void)const;
	const int			&getUserFd(void)const;
	std::string			getMessage(void);

	const int	&getnbChannelRegistered(void);
	void	setNbChannelRegistered(int nb);

	void	setNickname(std::string nickname);
	void	setUsername(std::string username);
	void	setRealname(std::string realname);
	void	setUserFd(int userFd);
	void	setMessage(std::string realname);


	// CMD

	void nickCmd(Server& server, const std::vector<std::string> &nickName);
	void userCmd(Server& server, const std::vector<std::string> &userName);


	void modeCmd(Server& server, const std::vector<std::string> &modeStr);
	void joinCmd(Server &server, const std::vector<std::string>& arg);
	void quitCmd(Server &server, const std::vector<std::string> &arg);
	void listCmd(Server &server, std::vector<std::string> channels_string);
	void topicCmd(Server& server, std::vector<std::string> channels_string);
	void pongCmd(Server &server, const std::vector<std::string> &arg) const;
	void partCmd(Server &server, std::vector<std::string> &arg);
	void privMsgCmd(Server &server, std::vector<std::string> arg);
	void whoCmd(Server &server, std::vector<std::string> arg);
	void noticeCmd(Server &server, std::vector<std::string> arg);
	void passCmd(Server &server, std::vector<std::string> &arg);
	void inviteCmd(Server &server, std::vector<std::string> &arg);
	void kickCmd(Server &server, std::vector<std::string> &arg);
	std::string &getIp();


	protected :
	int			_userFd;
	std::string	_nickname;
	std::string	_username;
	std::string	_realname;
	std::string _ip;
	std::string	message;

	int	nbChannelRegistered;

	bool	hasANickName;
	bool	hasAUserName;
	bool	registered;
	bool	passMatch;
	bool _isBot;

	__uint32_t		_userMode;

	friend class Server;

};

void	getMsg(Server &server, std::string msg, int userFd);
void	changeMode(unsigned int &checkedMode, const e_modes MODE, bool sign);
bool	checkMode(const unsigned int &checkedMode, const e_modes MODE);
void	handleInviteMode(Channel &channel, const s_parseMode &mode);
void	handleTopicMode(Channel &channel, const s_parseMode &mode);
void	handleKeyMode(Channel &channel, const s_parseMode &mode, User &userSend, Server &server);
void	handleLimitMode(Channel &channel, const s_parseMode &mode);
void	handleOperatorMode(Channel &channel, const s_parseMode &mode, User &userSend, Server &server);


#endif
