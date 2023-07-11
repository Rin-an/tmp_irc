#include "commands.hpp"

extern   std::deque<Channel>	g_chs;

void    split_param(std::string param, std::vector<std::string> &ch_list, std::vector<std::string> &user_list, std::string& cmt)
{
	std::stringstream   ss(param);
    std::string     chs;
    std::string     users;

    getline(ss, chs, ' ');
    getline(ss, users, ' ');
	getline(ss, cmt);
    std::stringstream   ss_ch(chs);
    std::stringstream   ss_user(users);
    while(!ss_ch.eof())
    {
        std::string ch;
        getline(ss_ch, ch, ',');
        ch_list.push_back(ch);
    }
    while (!ss_user.eof())
    {
        std::string user;
        getline(ss_user, user, ',');
        user_list.push_back(user);
    }
}

void	kick_user(std::vector<std::string> ch_list, std::vector<std::string> users, std::deque<std::string>::iterator u)
{
	for (size_t i = 0; i < ch_list.size(); i++)
	{
		int	ch_i = find_ch(ch_list[i]);
		if (ch_i < 0)
		{
			//ERR_NOSUCHCHANNEL 403
			std::cout << ch_list[i] << " :No such channel" << std::endl;
			return ;
		}
		Channel	*ch = &g_chs[ch_i];
		if (find(ch->users.begin(), ch->users.end(), *u) == ch->users.end())
		{
			//ERR_NOTONCHANNEL 442
			std::cout << ch_list[i] << " :You're not on that channel" << std::endl;
			return ;
		}
		if (find(ch->op.begin(), ch->op.end(), *u) == ch->op.end())
		{
			//ERR_CHANOPRIVSNEEDED 482
			std::cout << ch_list[i] << " :You're not channel operator" << std::endl;
			return ;
		}
		if (find(ch->users.begin(), ch->users.end(), users[i]) == ch->users.end())
		{
			//ERR_USERNOTINCHANNEL 441
			std::cout << users[i] << " " << ch_list[i] << " :They aren't on that channel" << std::endl;
			return ;
		}
		ch->users.erase(find(ch->users.begin(), ch->users.end(), users[i]));
	}
}

void	kick_cmd(std::string param, std::deque<std::string>::iterator u)
{
	std::vector<std::string>	ch_list;
	std::vector<std::string>	user_list;
	std::string					cmt;

	split_param(param, ch_list, user_list, cmt);
	if (ch_list[0].empty() || user_list[0].empty() || ch_list.size() != user_list.size())
	{
		//ERR_NEEDMOREPARAMS 461
		std::cout << "KICK :Not enough parameters" << std::endl;
		return ;
	}
	if (valid_ch(ch_list) < 0)
		return ;
	kick_user(ch_list, user_list, u);
}
