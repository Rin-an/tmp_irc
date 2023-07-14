/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:14:52 by zel-hach          #+#    #+#             */
/*   Updated: 2023/07/14 13:25:03 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "server.hpp"
#include "Channel.hpp"

int pars_mode_param(std::string mode_param)
{
	const char *s;
	s = mode_param.c_str();
	for (int i = 0 ; i < mode_param.size();i++)
	{
		if (s[i] < '0' && s[i] < '9')
			return(0);
		else
			i++;
	}
	return(1);
}
void set_mode(std::string &str,std::string mode_param, std::deque<Channel *>::iterator it)
{
	const char *s;
	s = str.c_str();
	for (int i = 0; i < str.size(); i++)
	{
		if ( (s[0] == '-' || s[0] == '+'))
		{
			if (s[i] == 'i')
			{
				//Set/remove Invite-only channel
			}
			if (s[i] == 'l')
			{
				//Set/remove the user limit to channel
				if (pars_mode_param(mode_param) == 1)
				{
					(*it)->setLimit(atoi(mode_param.c_str()));
					(*it)->setMode(str[i]);
					
				}
				else
					std::cout << "replay(696) \n";
			}
			if (s[i] == 'o')
			{
				// Give/take channel operator privilege
			}
			if (s[i] == 'k')
			{
				//Set/remove the channel key (password)
			}
			if (s[i] == 't')
			{
				// Set/remove the restrictions of the TOPIC command to channel operators
			}
			else
				std::cout << "ERR_UNKNOWNMODE" << std::endl;
		}
	}
}
void mode_cmd(std::string param, Client &c, Server &s)
{
	std::stringstream str(param);
	std::string mode;
	std::string channel;
	std::string modeparam;
	getline(str, channel, ' ');
	getline(str, mode, ' ');
	getline(str, modeparam);

	if (channel.empty())
		std::cout << "ERR_NEEDMOREPARAMS\n";
	for (std::deque<Channel *>::iterator it = s.chs.begin(); it != s.chs.end(); it++)
	{
		if ((*it)->getName() == channel)
		{
			std::deque<Client *>::iterator it_user = std::find((*it)->users.begin(), (*it)->users.end(), &c);
			if (it_user == (*it)->users.end())
				std::cout << "user not in channel\n";
			else
			{

				(*it)->setMode(mode);
				// if ((*it)->getTopic().empty())
				// 	std::cout << "RPL_NOTOPIC\n";
				// else
				// 	std::cout << "RPL_TOPIC" << std::endl;
			}
		}
		else
			std::cout << "ERR_NOTONCHANNEL" << std::endl;
	}
}