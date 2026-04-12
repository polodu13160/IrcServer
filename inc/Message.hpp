#ifndef MESSAGE_HPP
# define MESSAGE_HPP
#include <iostream>

class Message{
	public :
	Message(void);
	~Message(void);

	const std::string	&getPrfx(void)const;
	const std::string	&getCmd(void)const;
	const std::string	*getParam(void)const;

	void	setPrfx(std::string prefix);
	void	setCmd(std::string cmd);
	void	setParam(std::string param, int i);

	void	printParams(void);

	private:
	std::string	_prfx;
	std::string	_cmd;
	std::string	_param[15];
};

#endif
