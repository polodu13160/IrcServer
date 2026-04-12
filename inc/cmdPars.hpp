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

	void	cmdParser(User &user, std::string cmd, std::string *args);

	std::map<std::string, void (cmdPars::*)(User&, std::string*)>_handlerTab;

	void	handleKick(User &user, std::string *args);
	void	handleMode(User &user, std::string *args);
	void	handleInvite(User &user, std::string *args);
	void	handleTopic(User &user, std::string *args);
	void	handlePart(User &user, std::string *args);
	void	handleNick(User &user, std::string *args);
	void	handleQuit(User &user, std::string *args);
	void	handleJoin(User &user, std::string *args);
	void	handleHelp(User &user, std::string *args);
};
#endif
