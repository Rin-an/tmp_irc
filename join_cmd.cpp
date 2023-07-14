/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:49:29 by ssadiki           #+#    #+#             */
/*   Updated: 2023/07/13 17:28:32 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

void	split_param(std::string param, std::vector<std::string> &ch_list, std::vector<std::string> &key_list)
{
   	std::stringstream	ss(param);
	std::string		chs; std::string		keys;

	getline(ss, chs, ' '); getline(ss, keys); std::stringstream	ss_ch(chs);
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
	for (std::vector<std::string>::iterator it = ch_list.begin(); it != ch_list.end(); it++)
	{
		std::string	ch = *it;
		if ((ch.find_first_of(CHANNEL_CHARS) != 0 || ch.size() > 50) && *it != "0")
		{
			//ERR_NOSUCHCHANNEL 403
			std::cout << ch << " :No such channel" << std::endl;
			return (-1);
		}
	}
	return (0);
}

int	find_ch(std::string ch, Server& s)
{
	for (unsigned long i = 0; i < s.chs.size(); i++)
	{
		if (s.chs[i]->getName() == ch)
		{
			return (i);
		}
	}
	return (-1);
}

int	check_modes(Channel ch, Client& c)
{
	if ((ch.getMode()).find('i') != std::string::npos && find(ch.invite.begin(), ch.invite.end(), &c) == ch.invite.end())
		//ERR_INVITEONLYCHAN 473
		throw (ch.getName() + " :Cannot join channel (+i)");
	if ((ch.getMode()).find('l') != std::string::npos && ch.getUsernum() == ch.getLimit()) 
		//ERR_CHANNELISFULL 471
		throw (ch.getName() + " :Cannot join channel (+l)");
	if ((ch.getMode()).find('k') != std::string::npos)
		return (1);
	return (0);
}

void	add_user(std::string ch, std::vector<std::string>& key_list, int i, Client& c, Server& s)
{
	int	ch_i = find_ch(ch,s);
	(void) s;

	try {
		if (find(s.chs[ch_i]->users.begin(), s.chs[ch_i]->users.end(), &c) != s.chs[ch_i]->users.end())
			return ;
		int k = check_modes(*s.chs[ch_i], c);
		std::deque<Client*>	invite = s.chs[ch_i]->invite;
		if (find(invite.begin(), invite.end(), &c) == invite.end())
			if (k && key_list[i] != s.chs[ch_i]->getKey())
				//ERR_BADCHANNELKEY 475
				throw (ch + " :Cannot join channel (+k)");
		s.chs[ch_i]->users.push_back(&c);
		s.chs[ch_i]->incUsernum();
	}
	catch (const char* str)
	{
		throw(str);
	}
	catch (std::string& str)
	{
		throw (str);
	}
}

void	create_ch(std::string ch, Client& c, Server &s)
{
	Channel	*n_ch = new Channel(ch);

	n_ch->users.push_back(&c);
	n_ch->op.push_back(&c);
	n_ch->incUsernum();
	s.chs.push_back(n_ch);
}

void	quit_all(Client& c, Server &s)
{
	for (std::deque<Channel *>::iterator it = s.chs.begin(); it != s.chs.end(); it++)
	{
		std::deque<Client*>&	users = (*it)->users;
		for (std::deque<Client*>::iterator it2 = users.begin(); it2 != users.end(); it2++)
		{
			if (*it2 == &c)
			{
				users.erase(it2);
				(*it)->decUsernum();
			}
		}
	}
}

int	join_ch(std::vector<std::string>& ch_list, std::vector<std::string>& key_list, Client& c, Server& s)
{
	for (unsigned long i = 0; i < ch_list.size(); i++)
	{
		try{
			if (ch_list[i] == "0")
				quit_all(c,s);
			else if (!s.chs.empty() && find_ch(ch_list[i],s) >= 0)
				add_user(ch_list[i], key_list, i, c, s);
			else
			{
				create_ch(ch_list[i], c, s);
				std::cout << s.chs[0]->getName() << std::endl;
			}
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		catch (const char* str)
		{
			std::cout << str << std::endl;
		}
		catch (std::string& str)
		{
			std::cout << str << std::endl;
		}
	}
	return (0);
}

void	join_cmd(std::string param, Client& c, Server& s)
{
	std::vector<std::string>	ch_list;
	std::vector<std::string>	key_list;

	//std::cout << "JOIN COMMAND" << std::endl;
	split_param(param, ch_list, key_list);
	if (ch_list[0].empty())
	{
		//ERR_NEEDMOREPARAMS 461
		std::cout << "JOIN :Not enough parameters" << std::endl;
		return ;
	}
	if (valid_ch(ch_list) < 0)
		return ;
	if (join_ch(ch_list, key_list, c, s) < 0)
		return ;
}
