/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:50:12 by ssadiki           #+#    #+#             */
/*   Updated: 2023/07/12 20:03:23 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

int f_index(std::string cmd)
{
    int i = -1;
    std::string cmds[] = {"JOIN", "MODE", "INVITE", "TOPIC", "KICK"};
    while (++i <= 4)
    {
        if (cmd == cmds[i])
            return (i);
    }
    return (-1);
}

void    exec_ch_command(std::string& cmd, std::string& param, Client& cl, Server& server)
{
    void    (*cmdsf[]) (std::string, Client&, Server&) = {&join_cmd, &mode_cmd, &invite_cmd, &topic_cmd, &kick_cmd};

    switch (f_index(cmd))
    {
        case 0:
            cmdsf[0](param, cl, serv);
            break;
        case 1:
            cmdsf[1](param, cl, serv);
            break;
        case 2:
            cmdsf[2](param, cl, serv);
            break;
        case 3:
            cmdsf[3](param, cl, serv);
            break;
        case 4:
            cmdsf[4](param, cl, serv);
            break;
        default:
            std::cout << "how?" << std::endl;
    }
}
void	topic_cmd(std::string param, std::deque<std::string>::iterator u)
{
	/*(this->mode).find("t") == string::npos ? return (ERR_NOCHANMODES) : continue;
	std::stringstream   str(param);
	std::string         ch_n, t;
	std::getline(str, ch_n, ' ');

	if (param.empty())
	{
		std::cout << name << " topic: " << topic << std::endl;
		return ;
	}
	std::getline(str, t);*/
	(void) param;
	(void) u;

	std::cout << "TOPIC command" << std::endl;
}

/*void    join_cmd(std::string param, std::deque<std::string>::iterator u)
{
	(void) param;
	std::stringstream	ss(param);
	std::cout << "User: " << *u << std::endl;
	std::cout << "JOIN command" << std::endl;
}*/

void    invite_cmd(std::string param, std::deque<std::string>::iterator u)
{
	(void) param;
	(void) u;

	std::cout << "INVITE command" << std::endl;
}

void    user_cmd(std::string param, std::deque<std::string>& u)
{
	(void) param;
	(void) u;

	if (param.empty())
	{
		std::cout << "USER :Not enough parameters" << std::endl;
		return ;
	}
	u.push_back(param);
	std::cout << "USER command" << std::endl;
}

void    mode_cmd(std::string param, std::deque<std::string>::iterator u)
{
	(void) param;
	(void) u;

	std::cout << "MODE command" << std::endl;
}

/*void    kick_cmd(std::string param, std::deque<std::string>::iterator u)
{
	(void) param;
	(void) u;

	std::cout << "KICK command" << std::endl;
}*/
