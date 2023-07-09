#include "commands.hpp"

extern   std::deque<Channel>	g_chs;

void	kick_cmd(std::string param, std::deque<std::string>::iterator u)
{
	std::vector<std::string>	ch_list;
	std::vector<std::string>	user_list;

	split_param(param, ch_list, user_list);
}
