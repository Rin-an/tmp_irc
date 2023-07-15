/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:50:12 by ssadiki           #+#    #+#             */
/*   Updated: 2023/07/15 17:00:23 by ssadiki          ###   ########.fr       */
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

void    exec_ch_command(std::string& cmd, std::string& param, Client& cl, Server& serv)
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
            std::cout << "Couldn't find command." << std::endl;
    }
}

/*void    invite_cmd(std::string param, Client& c, Server& s)
{
	(void) param;
	(void) c;
	(void) s;


	std::cout << "INVITE command" << std::endl;
}*/

void    mode_cmd(std::string param, Client& c, Server& s)
{
	(void) param;
	(void) c;
 	(void) s;

	std::cout << "MODE command" << std::endl;
}

/*void    kick_cmd(std::string param, Client& c, Server& s)
{
	(void) param;
	(void) c;
	(void) s;

	std::cout << "KICK command" << std::endl;
}*/
