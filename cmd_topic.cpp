/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_topic.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:26:05 by zel-hach          #+#    #+#             */
/*   Updated: 2023/07/13 11:25:49 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "server.hpp"
#include "Channel.hpp"

void Client::cmd_topic(std::string channel, std::string topic, Server &server)
{
	std::deque<Channel>::iterator it = std::find(server.chs.begin(), server.chs.end(), channel);
	std::deque<Client *>::iterator it_user = std::find((*it).user.begin(), (*it).user.end(), this);

	if (it != server.chs.end())
		std::cout << "ERR_NOTONCHANNEL" << std::endl;
	if (it_user != (*it).user.end())
		std::cout << "user not in channel\n";
	if (channel.empty() && topic.empty())
		std::cout << "ERR_NEEDMOREPARAMS\n";
	else
	{
		(*it).setTopic(topic);
		if ((*it).getTopic().empty())
			std::cout << "RPL_NOTOPIC\n";
		else
			std::cout << "RPL_TOPIC" << std::endl;
	}
}
