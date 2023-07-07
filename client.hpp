/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:12:02 by zel-hach          #+#    #+#             */
/*   Updated: 2023/07/07 15:12:02 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "User.hpp"
#include "server.hpp"
#include <poll.h>

class Server;
class User;
class Client
{
	int pass;
	std::string user_name;
	std::string nickname;
public:
	int addrlen;
	int i;
	int len;
	struct sockaddr_in hint;

	Client();
	~Client();
	Client(Client &);
	Client &operator=(Client &);

	int getPass();
	std::string getUserName(void);
	std::string getNickName(void);



	void setPass(int);
	void setUserName(std::string);
	void setNickName(std::string);


	std::vector<pollfd> connection_multi_client_srv(int serversocket, std::vector<pollfd> &readfds, Server &server);
	void send_recv_msg(std::vector<pollfd> &readfds, char *argv, int *index, Server &server);
	bool ckeck_command(std::string command);
};
std::string to_upper(std::string &str);
int nickname_exist(Server server, std::string parametre);
void ft_strtrim(std::string &str);
#endif