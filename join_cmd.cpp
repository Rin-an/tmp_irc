#include "commands.hpp"

void	split_param(std::string param, std::vector<std::string> &ch_list, std::vector<std::string> &key_list)
{
	(void) ch_list;
	(void) key_list;
	std::stringstream	ss(param);
	std::string		chs;
	std::string		keys;

	std::cout << ss.str() << std::endl;
	getline(ss, chs, ' ');
	getline(ss, keys);
	std::stringstream	ss_ch(chs);
	std::stringstream	ss_key(keys);

	while(!ss_ch.eof())
	{
		std::string	ch;
		getline(ss_ch, ch, ',');
		ch_list.push_back(ch);
	}
	std::cout << std::endl;
	while (!ss_key.eof())
	{
		std::string	key;
		getline(ss_key, key, ',');
		key_list.push_back(key);
	}
}

int	valid_ch(std::vector<std::string>& ch_list)
{
	for (std::vector<std::string>::iterator it = ch_list.being(); it != ch_list.end(); it++)
	{
		std::string	ch = *it;
		if (!(ch[0] == '&' || ch[0] == '#' || ch[0] == '+' || ch[0] == '|'))
		{
			std::cout << ch << " :No such channel" << std::endl;
			return (-1);
		}
	}
	return (0);
}

void	join_cmd(std::string param, std::deque<std::string>::iterator u)
{
	(void) u;
	std::vector<std::string>	ch_list;
	std::vector<std::string>	key_list;

	std::cout << "JOIN COMMAND" << std::endl;
	split_param(param, ch_list, key_list);
	if (ch_list.empty())
	{
		std::cout << "JOIN :Not enough parameters" << std::endl;
		return ;
	}
	if (valid_ch(ch_list) < 0)
		return ;
}
