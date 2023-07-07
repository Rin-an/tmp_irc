#include "commands.hpp"

std::deque<Channel*>	g_chs;

int	f_index(std::string cmd)
{
	int	i = -1;
	std::string	cmds[] = {"JOIN", "MODE", "INVITE", "TOPIC", "KICK"};
	while (++i <= 4)
	{
		if (cmd == cmds[i])
			return (i);
	}
	return (-1);
}

void	exec_ch_command(std::string& cmd, std::string& param, std::deque<std::string>::iterator user)
{
	void	(*cmdsf[]) (std::string, std::deque<std::string>::iterator) = {&join_cmd, &mode_cmd, &invite_cmd, &topic_cmd, &kick_cmd};

	switch (f_index(cmd))
	{
		case 0:
			cmdsf[0](param, user);
			break;
		case 1:
			cmdsf[1](param, user);
			break;
		case 2:	
			cmdsf[2](param, user);
			break;
		case 3:
			cmdsf[3](param, user);
			break;
		case 4:
			cmdsf[4](param, user);
			break;
		default:
			std::cout << "how?" << std::endl;
	}
}

std::deque<std::string>::iterator	select_user(std::deque<std::string> &users)
{
	std::string	user;

	std::cout << "Enter your username:";
	std::getline(std::cin, user);
	std::cin.clear();
	return (find(users.begin(), users.end(), user));
}

void    parse_ch_cmd(std::string cmdline, std::deque<std::string> &users)
{
	std::deque<std::string>::iterator	user;
	std ::stringstream str(cmdline);
	std::string cmd;
	std::string param;
	getline(str, cmd, ' ');
	getline(str, param);
	ft_strtrim(param);
	cmd = to_upper(cmd);

	if (cmd == "JOIN" || cmd == "MODE" || cmd == "INVITE" \
			|| cmd == "TOPIC" || cmd == "KICK")
	{
		std::cout << "cmd: " << cmd << " ,parametres " << param << std::endl;
		user = select_user(users);
		if (user == users.end())
		{
			std::cout << "No such username." << std::endl;
			return ;
		}
		exec_ch_command(cmd, param, user);
	}
	else if (cmd == "USER")
	{
		user_cmd(param, users);
		std::cout << "USER LIST" << std::endl << "__________" << std::endl;
		for (std::deque<std::string>::iterator it = users.begin(); it != users.end(); it++)
			std::cout << *it << std::endl;
		std::cout << "__________" << std::endl;
	}
	else
	{
		std::cout << "<" << cmd << ">" << " :Unknown command" << std::endl;
		return;
	}
}

int	main(void)
{
	std::deque<std::string>	users;
	std::string	cmdline;

	while (1)
	{
		std::cout << "Enter command: ";
		std::getline(std::cin, cmdline);
		std::cin.clear();
		std::cout << cmdline << std::endl;
		if (cmdline == "q")
			break;
		parse_ch_cmd(cmdline, users);
	}
	return (0);
}
