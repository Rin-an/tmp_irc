/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_topic.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:26:05 by zel-hach          #+#    #+#             */
/*   Updated: 2023/07/14 09:16:29 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "server.hpp"
#include "Channel.hpp"
#include "commands.hpp"

void topic_cmd(std::string param, Client &c, Server &server)
{
	std::stringstream str(param);
	std::string topic;
	std::string channel;
	getline(str, channel, ' ');
	getline(str, topic);
	if (channel.empty())
		std::cout << "ERR_NEEDMOREPARAMS\n";
	for (std::deque<Channel *>::iterator it = server.chs.begin(); it != server.chs.end(); it++)
	{
		if ((*it)->getName() == channel)
		{
			std::deque<Client *>::iterator it_user = std::find((*it)->users.begin(), (*it)->users.end(), &c);
			if (it_user == (*it)->users.end())
				std::cout << "user not in channel\n";
			else
			{
				(*it)->setTopic(topic);
				if ((*it)->getTopic().empty())
					std::cout << "RPL_NOTOPIC\n";
				else
					std::cout << "RPL_TOPIC" << std::endl;
			}
		}
		else
			std::cout << "ERR_NOTONCHANNEL" << std::endl;
	}
}
