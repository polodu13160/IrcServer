#ifndef CMDPARS_HPP
# define CMDPARS_HPP
#include <iostream>
#include <map>

class cmdPars{
	public :
	cmdPars(void);
	~cmdPars(void);

	void	cmdParser(std::string cmd, const std::string *args);

	std::map<std::string, void (cmdPars::*)(const std::string*)>_handlerTab;

	void	handleKick(const std::string *args);
	void	handleMode(const std::string *args);
	void	handleInvite(const std::string *args);
	void	handleTopic(const std::string *args);
	void	handlePart(const std::string *args);
	void	handleNick(const std::string *args);
	void	handleQuit(const std::string *args);
	void	handleJoin(const std::string *args);
	void	handleHelp(const std::string *args);
};
#endif
