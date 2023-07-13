/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:11:52 by zel-hach          #+#    #+#             */
/*   Updated: 2023/07/13 13:13:23 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

Client::Client()
{
	this->i = 0;
	this->len = 0;
	flag = 0;
}

Client::~Client() {}

Client::Client(const Client& cp)
{
	*this = cp;
}

Client& Client::operator=(const Client &cpy)
{
	if (this != &cpy)
	{
		this->pass = cpy.pass;
		this->user_name = cpy.user_name;
		this->nickname = cpy.nickname;
		this->flag = cpy.flag;
	}
	return(*this);
}

int Client::getPass()
{
	return (this->pass);
}

const std::string Client::getUserName(void)
{
	return (this->user_name);
}

const std::string Client::getNickName(void)
{
	return (this->nickname);
}

void Client::setPass(int pass)
{
	this->pass = pass;
}

void Client::setUserName(std::string user_name)
{
	this->user_name = user_name;
}

void Client::setNickName(std::string nick_name)
{
	this->nickname = nick_name;
}

std::vector<pollfd> Client::connection_multi_client_srv(int serversocket, std::vector<pollfd> &readfds, Server &server)
{
	int new_socket;
	char message[21] = "welcome to client \r\n";
	if ((new_socket = accept(serversocket,
					(struct sockaddr *)&this->hint, (socklen_t *)&(this->addrlen))) < 0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	std::cout << "New connection , socket fd is  " << new_socket << ", ip is : " << inet_ntoa(this->hint.sin_addr) << ", port : " << ntohs(this->hint.sin_port) << "\n";
	size_t k;
	if ((k = send(new_socket, message, strlen(message), 0)) != strlen(message))
		perror("send");
	std::cout << "Welcome message sent successfully\n";
	pollfd p;
	p.fd = new_socket;
	p.events = POLLIN;
	readfds.push_back(p);
	server.client[p.fd] = *this;
	return (readfds);
}

int valide_nickname(std::string nickname)
{
	int i;
	const char *str;

	str = nickname.c_str();
	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'A' && str[i] <= '[') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '-' || str[i] == '_' || str[i] == ']')
		{
			if (i == 0 && (str[i] >= '0' && str[i] <= '9'))
				return (1);
			i++;
		}
		else
			return (1);
	}
	return (0);
}

void Client::send_recv_msg(std::vector<pollfd> &readfds, char *argv, int *index, Server &server)
{
	char buffer[1024];
	User user;
	memset(buffer, 0, sizeof(buffer));
	int valread = read(readfds[*index].fd, buffer, 1024);
	if (valread <= 0)
	{
		getpeername(readfds[*index].fd, (struct sockaddr *)&(this->hint),
				(socklen_t *)&(this->addrlen));
		std::cout << "Host disconnected , ip" << inet_ntoa(this->hint.sin_addr) << ", port " << ntohs(this->hint.sin_port) << ".\n";
		close(readfds[*index].fd);
	}
	else
	{
		buffer[valread] = '\0';
		std ::stringstream str(buffer);
		std::string	tmp;
		getline(str, tmp, '\n');
		std::string command;
		std::string parametre;
		str.str(tmp);
		getline(str, command, ' ');
		getline(str, parametre);
		ft_strtrim(parametre);
		command = to_upper(command);

		if (command == "PASS")
		{
			if (parametre == "\0")
				std::cout << "ERR_NEEDMOREPARAMS\n";
			else if (this->getPass() == 1)
				std::cout << "ERR_ALREADYREGISTRED\n";
			else if (parametre == argv)
				this->setPass(1);
		}
	//	std::cout << this->i << std::endl;
		if (command == "NICK" && this->getPass() == 1 && nickname_exist(server, parametre) == 0)
		{
			if (parametre.length() == 0)
				std::cout << "ERR_NONICKNAMEGIVEN\n";
			else if (valide_nickname(parametre) == 1)
				std::cout << "ERR_ERRONEUSNICKNAME\n";
			else
			{
				this->nickname = parametre;
		//		std::cout << "nickname: " << this->nickname << std::endl;
				this->i++;
			}
		}
		if (command == "USER" && this->getPass() == 1 )//&& parametre.length() != 0)
		{
			this->user_name = parametre;
			std::string us;
			std ::stringstream str(parametre);
			getline(str, us, ' ');
			user.setUser(us);
			us = "";
			getline(str, us, ' ');
			user.setMode(us);
			us = "";
			getline(str, us, ' ');
			user.setUnused(us);
			us = "";
			getline(str, us);
			user.setRealname(us);
			us = "";
			if (user.getRealname().empty() || user.getMode().empty() || user.getUnused().empty() || user.getUser().empty())
				std::cout << "ERR_NEEDMOREPARAMS" << std::endl;
			else if (this->len == 1)
				std::cout << "ERR_ALREADYREGISTRED" << std::endl;
			else
			{
				this->users.push_back(user);
				this->len++;
			}
		}
		if (!this->flag && this->i == 1 && this->len == 1)
		{
			std::cout << "now you are connecte with nickname : " << this->nickname << std::endl;
			this->flag = 1;
		}
		else if (command == "NICK" && this->i > 1 && this->len == 1)
			std::cout << "You changed your nickname to : " << this->nickname << std::endl;
		else if (command != "NICK" && this->flag)
			parse_ch_cmd(command, parametre, server);
	}
}

void	Client::parse_ch_cmd(std::string cmd, std::string param, Server& server)
{
	if (cmd == "JOIN" || cmd == "MODE" || cmd == "INVITE" \
			|| cmd == "TOPIC" || cmd == "KICK")
	{
		exec_ch_command(cmd, param, *this, server);
	}
	else
	{
		std::cout << cmd << " :Unknown command" << std::endl;
		return;
	}
}
