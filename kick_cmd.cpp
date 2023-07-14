/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:49:50 by ssadiki           #+#    #+#             */
/*   Updated: 2023/07/14 13:47:00 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

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

Client*	getClient(std::string	user, Server& s)
{
	for (std::map<int, Client>::iterator it = s.client.begin(); it != s.client.end(); it++)
	{
		if (it->second.getNickName() == user)
			return &(it->second);
	}
	return (NULL);
}

void	kick_user(std::vector<std::string> ch_list, std::vector<std::string> users, Client& c, Server& s)
{
	for (size_t i = 0; i < ch_list.size(); i++)
	{
		int	ch_i = find_ch(ch_list[i], s);
		Client*	dest = getClient(users[i], s);

		if (ch_i < 0)
		{
			//ERR_NOSUCHCHANNEL 403
			std::cout << ch_list[i] << " :No such channel" << std::endl;
			return ;
		}
		Channel	*ch = s.chs[ch_i];
		if (find(ch->users.begin(), ch->users.end(), &c) == ch->users.end())
		{
			//ERR_NOTONCHANNEL 442
			std::cout << ch_list[i] << " :You're not on that channel" << std::endl;
			return ;
		}
		if (find(ch->op.begin(), ch->op.end(), &c) == ch->op.end())
		{
			//ERR_CHANOPRIVSNEEDED 482
			std::cout << ch_list[i] << " :You're not channel operator" << std::endl;
			return ;
		}
		if (find(ch->users.begin(), ch->users.end(), dest) == ch->users.end())
		{
			//ERR_USERNOTINCHANNEL 441
			std::cout << users[i] << " " << ch_list[i] << " :They aren't on that channel" << std::endl;
			return ;
		}
		ch->users.erase(find(ch->users.begin(), ch->users.end(), dest));
	}
}

void	kick_cmd(std::string param, Client& c, Server& s)
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
	kick_user(ch_list, user_list, c, s);
}
