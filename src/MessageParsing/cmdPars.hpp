#ifndef CMDPARS_HPP
# define CMDPARS_HPP
#include <iostream>
#include "User.hpp"
#include <map>

class cmdPars{
	public :
	cmdPars(void);
	~cmdPars(void);

	void	cmdParser(User &user, std::string cmd, const std::string *args);

	std::map<std::string, void (cmdPars::*)(User&, const std::string*)>_handlerTab;

	void	handleKick(User &user, const std::string *args);
	void	handleMode(User &user, const std::string *args);
	void	handleInvite(User &user, const std::string *args);
	void	handleTopic(User &user, const std::string *args);
	void	handlePart(User &user, const std::string *args);
	void	handleNick(User &user, const std::string *args);
	void	handleQuit(User &user, const std::string *args);
	void	handleJoin(User &user, const std::string *args);
	void	handleHelp(User &user, const std::string *args);
};
#endif
