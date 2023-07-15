/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite_cmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:28:33 by ssadiki           #+#    #+#             */
/*   Updated: 2023/07/15 17:10:39 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

void	invite_user(std::string nick, std::string ch, Client& c, Server& s)
{
	int	ch_i = find_ch(ch, s);

	if (ch_i < 0)
	{
		//ERR_NOSUCHCHANNEL 403
		std::cout << ch << " :No such channel" << std::endl;
		return ;
	}
	Channel*	ch2 = s.chs[ch_i];
	if (find(ch2->users.begin(), ch2->users.end(), &c) == ch2->users.end())
	{
		//ERR_NOTONCHANNEL 442
		std::cout << ch << " :You're not on that channel" << std::endl;
		return ;
	}
	Client	*dest = getClient(nick, s);
	if (dest == NULL)
	{
		//ERR_NOSUCHNICK 401
		std::cout << nick << " :No such nick/channel" << std::endl;
		return ;
	}
	if (find(ch2->users.begin(), ch2->users.end(), dest) != ch2->users.end())
	{
		//ERR_USERONCHANNEL 443
		std::cout << nick << " " << ch << " :is already on channel" << std::endl;
		return ;
	}
	if (ch2->getMode().find('i') != std::string::npos && find(ch2->op.begin(), ch2->op.end(), &c) == ch2->op.end())
	{
		//ERR_CHANOPRIVSNEEDED 482
		std::cout << ch << " :You're not channel operator" << std::endl;
		return ;
	}
	//send reply to destination user
	ch2->invite.push_back(dest);
}

void	invite_cmd(std::string param, Client& c, Server& s)
{
	std::stringstream	ss(param);
	std::string			nick;
	std::string			ch;

	getline(ss, nick, ' ');
	getline(ss, ch);

	if (nick.empty() || ch.empty())
	{
		//ERR_NEEDMOREPARAMS 461
		std::cout << "INVITE :Not enough parameters" << std::endl;
		return ;
	}
	/*if (valid_ch(ch) < 0)
		return ;*/
	invite_user(nick, ch, c, s);
}
