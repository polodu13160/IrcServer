#ifndef CMD_HPP
# define CMD_HPP
#include <iostream>
#include <map>
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
	void	join(void);
	void	part(void);
	void	msg(void);
	void	nick(void);
	void	quit(void);
	void	help(void);
};
#endif
