#include "commands.hpp"

void	topic_cmd(std::string param, std::deque<std::string>::iterator u)
{
	/*(this->mode).find("t") == string::npos ? return (ERR_NOCHANMODES) : continue;
	std::stringstream   str(param);
	std::string         ch_n, t;
	std::getline(str, ch_n, ' ');

	if (param.empty())
	{
		std::cout << name << " topic: " << topic << std::endl;
		return ;
	}
	std::getline(str, t);*/
	(void) param;
	(void) u;

	std::cout << "TOPIC command" << std::endl;
}

/*void    join_cmd(std::string param, std::deque<std::string>::iterator u)
{
	(void) param;
	std::stringstream	ss(param);
	std::cout << "User: " << *u << std::endl;
	std::cout << "JOIN command" << std::endl;
}*/

void    invite_cmd(std::string param, std::deque<std::string>::iterator u)
{
	(void) param;
	(void) u;

	std::cout << "INVITE command" << std::endl;
}

void    user_cmd(std::string param, std::deque<std::string>& u)
{
	(void) param;
	(void) u;

	if (param.empty())
	{
		std::cout << "USER :Not enough parameters" << std::endl;
		return ;
	}
	u.push_back(param);
	std::cout << "USER command" << std::endl;
}

void    mode_cmd(std::string param, std::deque<std::string>::iterator u)
{
	(void) param;
	(void) u;

	std::cout << "MODE command" << std::endl;
}

/*void    kick_cmd(std::string param, std::deque<std::string>::iterator u)
{
	(void) param;
	(void) u;

	std::cout << "KICK command" << std::endl;
}*/
