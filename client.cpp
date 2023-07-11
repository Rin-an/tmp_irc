/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:11:52 by zel-hach          #+#    #+#             */
/*   Updated: 2023/07/09 16:00:38 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"


Client::Client() {}
Client ::~Client() {}
Client:: Client(Client &copy)
{
    *this = copy;
}
Client &Client:: operator=(Client &cpy)
{
    this->pass = cpy.pass;
    this->user_name = cpy.user_name;
    this->nickname = cpy.nickname;
    return(*this);
}

int Client::getPass()
{
	return (this->pass);
}

std::string Client::getUserName(void)
{
	return (this->user_name);
}

std::string Client::getNickName(void)
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
        printf("Host disconnected , ip %s , port %d \n",
               inet_ntoa(this->hint.sin_addr), ntohs(this->hint.sin_port));
        close(readfds[*index].fd);
    }
    else
    {
        buffer[valread] = '\0';
        std ::stringstream str(buffer);
        std::string command;
        std::string parametre;
        getline(str, command, ' ');
        getline(str, parametre);
        ft_strtrim(parametre);
        command = to_upper(command);

        if ((command == "PASS" && parametre == argv))
            this->setPass(1);
        if (command == "NICK" && this->getPass() == 1 && parametre.length() != 0 && nickname_exist(server, parametre) == 0)
        {
            this->nickname = parametre;
            this->i++;
        }
        if (command == "USER" && this->getPass() == 1 && parametre.length() != 0)
        {
            this->user_name = parametre;
            this->len++;
        }
        if (!this->user_name.empty() && !this->nickname.empty() && server.client.size() == (size_t)this->i && server.client.size() == (size_t)this->len)
            std::cout << "now you are connecte with nickname : " << this->nickname << std::endl;
        for (std::map<int, Client>::iterator it = server.client.begin(); it != server.client.end(); it++)
            std::cout << it->first << " nickname: " << it->second.getNickName() << std::endl;
    }

}
