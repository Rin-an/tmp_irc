/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:11:52 by zel-hach          #+#    #+#             */
/*   Updated: 2023/07/12 19:21:49 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

Client::Client()
{
    this->i = 0;
    this->len = 0;
}
Client ::~Client() {}
// Client:: Client(Client &copy)
// {
//     *this = copy;
// }
// Client &Client:: operator=(Client &cpy)
// {
//     this->pass = cpy.pass;
//     this->user_name = cpy.user_name;
//     this->nickname = cpy.nickname;
//     return(*this);
// }
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
        std::string command;
        std::string parametre;
        getline(str, command, ' ');
        getline(str, parametre);
        ft_strtrim(parametre);
        command = to_upper(command);

        if (command == "PASS")
        {
            if (parametre.empty())
                std::cout << "ERR_NEEDMOREPARAMS\n";
            else if (this->getPass() == 1)
                std::cout << "ERR_ALREADYREGISTRED\n";
            else if (parametre == argv)
                this->setPass(1);
        }
        if (command == "NICK" && this->getPass() == 1 && nickname_exist(server, parametre) == 0)
        {
            if (parametre.length() == 0)
                std::cout << "ERR_NONICKNAMEGIVEN\n";
            if (valide_nickname(parametre) == 1)
                std::cout << "ERR_ERRONEUSNICKNAME\n";
            else
            {
                this->nickname = parametre;
                this->i++;
            }
        }
        if (command == "USER" && this->getPass() == 1 && parametre.length() != 0)
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
        if (this->i == 1 && this->len == 1)
            std::cout << "now you are connecte with nickname : " << this->nickname << std::endl;
        if (this->i > 1 && this->len == 1)
            std::cout << "now you are change nickname with : " << this->nickname << std::endl;
    }
}
// void 	Client::invite_user(std::string nickname,Server &server,std::string channel)
// {
// std::deque<Channel *>::iterator it = find(server.chs.begin(),server.chs.end(),channel);
// std::deque<Client *>::iterator it_user = find(server.chs.users.begin(),server.chs.users.end(),this->getNickName());
// std::deque<Client *>::iterator it_user_chs = find(server.chs.users.begin(),server.chs.users.end(),nickname);

// if (it != server.chs->end() && nickname_add_to_chs(server, nickname) == 1)
// RPL_INVITING;
// if (nickname_add_to_chs(server, nickname) == 0)
// error_ERR_NOSUCHNICK;
// if (it_user == server.chs.users->end())
//   ERR_NOTONCHANNEL  ;
// if (it_user_chs != server.chs.users->end())
//   ERR_USERONCHANNEL ;

// }
