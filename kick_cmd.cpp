#include "commands.hpp"

extern   std::deque<Channel>	g_chs;

 void    split_param(std::string param, std::vector<std::string> &ch_list, std::vector<std::string> &user_list)
{
    std::stringstream   ss(param);
    std::string     chs;
    std::string     keys;

    getline(ss, chs, ' ');
    getline(ss, keys);
    std::stringstream   ss_ch(chs);
    std::stringstream   ss_key(keys);

    while(!ss_ch.eof())
    {
        std::string ch;
        getline(ss_ch, ch, ',');
        ch_list.push_back(ch);
    }
    std::cout << std::endl;
    while (!ss_key.eof())
    {
        std::string key;
        getline(ss_key, key, ',');
        key_list.push_back(key);
    }
}

void	kick_user(std::vector<std::string> ch_list, std::vector<std::string> users, std::deque<std::string>::iterator u)
{
	for (int
}

void	kick_cmd(std::string param, std::deque<std::string>::iterator u)
{
	(void) u;
	std::vector<std::string>	ch_list;
	std::vector<std::string>	user_list;

	split_param(param, ch_list, user_list);
	if (ch_list[0].empty() || user_list[0].empty() || ch_list.size() != user_list.size())
	{
		//ERR_NEEDMOREPARAMS 461
		std::cout << "KICK :Not enough parameters" << std::endl;
		return ;
	}
	if (valid_ch(ch_list) < 0)
		return ;
	
	for (size_t i = 0; i < ch_list.size(); i++)
	{
		std::cout << "Channel: " << ch_list[i] << ", User " << user_list[i] << std::endl;
	}
}
