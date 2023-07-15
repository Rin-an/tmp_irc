/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:50:23 by ssadiki           #+#    #+#             */
/*   Updated: 2023/07/15 16:34:56 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "Channel.hpp"

void	exec_ch_command(std::string&, std::string&, Client&, Server&);

void	join_cmd(std::string, Client&, Server&);
void	topic_cmd(std::string, Client&, Server&);
void	invite_cmd(std::string, Client&, Server&);
void	mode_cmd(std::string, Client&, Server&);
void	kick_cmd(std::string, Client&, Server&);
void	user_cmd(std::string, Client&, Server&);

int		valid_ch(std::vector<std::string>&);
int		find_ch(std::string ch, Server& s);
Client*	getClient(std::string, Server&);
#endif
