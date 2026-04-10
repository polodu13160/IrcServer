#ifndef CMDPARS_HPP
# define CMDPARS_HPP
#include <iostream>
#include <map>

class cmdPars{
	public :
	cmdPars(void);
	~cmdPars(void);

	void	cmdParser(std::string cmd);

	std::map<std::string, void (cmdPars::*)(std::string*)>_handlerTab;

	void	handleKick(std::string *args);
	void	handleMode(std::string *args);
	void	handleInvite(std::string *args);
	void	handleTopic(std::string *args);
};
#endif
