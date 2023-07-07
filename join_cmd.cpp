#include "commands.hpp"

void	parse_param(std::string param, std::vector<std::string> &ch_list, std::vector<std::string> &key_list)
{
	(void) ch_list;
	(void) key_list;
	std::stringstream	ss(param);
	std::string		chs;
	std::string		keys;

	getline(ss, chs, ' ');
	getline(ss, keys);

	std::cout << "Channels list: " << chs << ", Keys list: " << keys << std::endl;
}

void	join_cmd(std::string param, std::deque<std::string>::iterator u)
{
	(void) u;
	std::vector<std::string>	ch_list;
	std::vector<std::string>	key_list;

	parse_param(param, ch_list, key_list);
	std::cout << "JOIN COMMAND" << std::endl;
}
