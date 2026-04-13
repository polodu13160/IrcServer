#ifndef CMDPARS_HPP
# define CMDPARS_HPP
#include <iostream>
#include "User.hpp"
#include <map>

class User;

class cmdPars{
	public :
	cmdPars(void);
	~cmdPars(void);

	void	cmdPars::cmdParser(User &user, std::string cmd, std::array<std::string, 15> args);

	std::map<std::string, void (cmdPars::*)(User&, std::array<std::string, 15>)>_handlerTab;

	void	handleKick(User &user, std::array<std::string, 15> args);
	void	handleMode(User &user, std::array<std::string, 15> args);
	void	handleInvite(User &user, std::array<std::string, 15> args);
	void	handleTopic(User &user, std::array<std::string, 15> args);
	void	handlePart(User &user, std::array<std::string, 15> args);
	void	handleNick(User &user, std::array<std::string, 15> args);
	void	handleQuit(User &user, std::array<std::string, 15> args);
	void	handleJoin(User &user, std::array<std::string, 15> args);
	void	handleHelp(User &user, std::array<std::string, 15> args);
};
#endif
