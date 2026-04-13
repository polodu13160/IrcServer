#ifndef MESSAGE_HPP
# define MESSAGE_HPP

#include <iostream>
#include <vector>

class Message{
	public :
	Message(void);
	~Message(void);

	const std::string	&getPrfx(void)const;
	const std::string	&getCmd(void)const;
	std::vector<std::string>	getParam(void)const;

	void	setPrfx(std::string prefix);
	void	setCmd(std::string cmd);
	void	pushBackParam(std::string param);

	void	printParams(void);

	bool	fullParams;

	private:
	std::string	_prfx;
	std::string	_cmd;
	std::vector<std::string>	_params;
};

#endif
