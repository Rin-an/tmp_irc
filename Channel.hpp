/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:50:01 by ssadiki           #+#    #+#             */
/*   Updated: 2023/07/13 11:17:05 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#define CHANNEL_CHARS "&#+|"
#define CHANNEL_MODS "klito"
#include "client.hpp"
#include <deque>
#include <algorithm>

class Server;
class Client;
class Channel{
	std::string name;
	std::string key;
	int			limit;
	int			usernum;
	std::string topic;
	std::string mode;
	public:
		std::deque<Client *> op;
		std::deque<Client *> invite;
		std::deque<Client *> users;
		Channel();
		Channel(const std::string&);
		~Channel();
		const std::string&	getName(void) const;
		const std::string&	getTopic(void) const;
		const std::string&	getMode(void) const;
		const std::string&	getKey(void) const;
		int			getLimit(void) const;
		int			getUsernum(void) const;
		void				setName(std::string&);
		void				setTopic(std::string&);
		void				setMode(std::string&);
		void				setKey(std::string&);
		void				setLimit(int);
		void				incUsernum(void);
		void				decUsernum(void);
//		void				topic_cmd(std::string, std::deque<std::string>, std::deque<Channel*>);
//		void				mode_cmd(std::string, std::deque<std::string>, std::deque<Channel*>);
};

#endif
