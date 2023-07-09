#include "commands.hpp"

extern std::deque<Channel> g_chs;

void	split_param(std::string param, std::vector<std::string> &ch_list, std::vector<std::string> &key_list)
{
	std::stringstream	ss(param);
	std::string		chs;
	std::string		keys;

//	std::cout << ss.str() << std::endl;
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

int	find_ch(std::string ch)
{
	for(unsigned long i = 0; i < g_chs.size(); i++)
	{
		if (g_chs[i].getName() == ch)
			return (i);
	}
	return (-1);
}

int	check_modes(int i, std::deque<std::string>::iterator u)
{
	Channel ch = g_chs[i];

	if ((ch.getMode()).find('i') != std::string::npos && find(ch.invite.begin(), ch.invite.end(), *u) == ch.invite.end())
		//ERR_INVITEONLYCHAN 473
		throw (ch.getName() + " :Cannot join channel (+i)");
	if ((ch.getMode()).find('l') != std::string::npos && ch.getUsernum() == ch.getLimit()) 
		//ERR_CHANNELISFULL 471
		throw (ch.getName() + " :Cannot join channel (+l)");
	if ((ch.getMode()).find('k') != std::string::npos)
		return (1);
	return (0);
}

void	add_user(std::string ch, std::vector<std::string>& key_list, int i, std::deque<std::string>::iterator u)
{
	int	ch_i = find_ch(ch);

	try{
		if (find(g_chs[ch_i].users.begin(), g_chs[ch_i].users.end(), *u) != g_chs[ch_i].users.end())
			return ;
		int k = check_modes(ch_i, u);
		std::deque<std::string>	invite = g_chs[ch_i].invite;
		if (find(invite.begin(), invite.end(), *u) == invite.end())
			if (k && key_list[i] != g_chs[ch_i].getKey())
				//ERR_BADCHANNELKEY 475
				throw (ch + " :Cannot join channel (+k)");
		g_chs[ch_i].users.push_back(*u);
		g_chs[ch_i].incUsernum();
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

void	create_ch(std::string ch, std::deque<std::string>::iterator u)
{
	Channel	n_ch(ch);

	n_ch.users.push_back(*u);
	n_ch.op.push_back(*u);
	n_ch.incUsernum();
	g_chs.push_back(n_ch);
}

void	quit_all(std::deque<std::string>::iterator u)
{
	for (std::deque<Channel>::iterator it = g_chs.begin(); it != g_chs.end(); it++)
	{
		std::deque<std::string>&	users = (*it).users;
		for (std::deque<std::string>::iterator it2 = users.begin(); it2 != users.end(); it2++)
		{
			if (*it2 == *u)
			{
				std::cout << "Did it get here?" << std::endl;
				users.erase(it2);
				(*it).decUsernum();
			}
		}
		std::cout << "Channel " << (*it).getName() << " has " << (*it).getUsernum() << "users." << std::endl;
	}
}

int	join_ch(std::vector<std::string>& ch_list, std::vector<std::string>& key_list, std::deque<std::string>::iterator u)
{
	for (unsigned long i = 0; i < ch_list.size(); i++)
	{
		try{
			if (ch_list[i] == "0")
				quit_all(u);
			else if (!g_chs.empty() && find_ch(ch_list[i]) >= 0)
				add_user(ch_list[i], key_list, i, u);
			else
				create_ch(ch_list[i], u);
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

void	join_cmd(std::string param, std::deque<std::string>::iterator u)
{
	std::vector<std::string>	ch_list;
	std::vector<std::string>	key_list;

	//std::cout << "JOIN COMMAND" << std::endl;
	split_param(param, ch_list, key_list);
	if (ch_list.empty() || (ch_list.size() == 1 && ch_list[0].empty()))
	{
		//ERR_NEEDMOREPARAMS 461
		std::cout << "JOIN :Not enough parameters" << std::endl;
		return ;
	}
	if (valid_ch(ch_list) < 0)
		return ;
	if (join_ch(ch_list, key_list, u) < 0)
		return ;
}
