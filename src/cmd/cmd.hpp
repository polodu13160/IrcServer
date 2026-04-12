#ifndef CMD_HPP
# define CMD_HPP

#include <iostream>
#include <map>
#include "../MessageParsing/User.hpp"
using namespace	std;

class cmd{
	public:
	cmd(void);
	void			(cmd::*_cmdFunction[10])();
	std::string		_cmd[10];
	map<string, void (cmd::*)()> _cmdMap;

	void	kick(void);
	void	invite(void);
	void	topic(void);
	void	mode(void);
	void	join(Server server, User &user, std::string channel, std::string pass);
	void	part(void);
	void	msg(void);
	void	nick(User &user, std::string name);
	void	quit(void);
	void	help(void);
};
#endif
