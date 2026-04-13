#ifndef MESSAGE_HPP
# define MESSAGE_HPP

#include <iostream>
#include <array>

class Message{
	public :
	Message(void);
	~Message(void);

	const std::string	&getPrfx(void)const;
	const std::string	&getCmd(void)const;
	std::array<std::string, 15>	getParam(void)const;

	void	setPrfx(std::string prefix);
	void	setCmd(std::string cmd);
	void	setParam(std::string param, int i);

	void	printParams(void);

	bool	fullParams;

	private:
	std::string	_prfx;
	std::string	_cmd;
	std::array<std::string, 15>	_params;
};

#endif
