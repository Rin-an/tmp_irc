#include "client.hpp"

Client::Client() {}
Client ::~Client() {}

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

std::vector<pollfd> Client::connection_multi_client_srv(int serversocket, std::vector<pollfd> &readfds, Client &client, Server &server)
{
    int new_socket;
    char message[21] = "welcome to client \r\n";
    if ((new_socket = accept(serversocket,
                             (struct sockaddr *)&client.hint, (socklen_t *)&(client.addrlen))) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    std::cout << "New connection , socket fd is  " << new_socket << ", ip is : " << inet_ntoa(client.hint.sin_addr) << ", port : " << ntohs(client.hint.sin_port) << "\n";
    size_t k;
    if ((k = send(new_socket, message, strlen(message), 0)) != strlen(message))
        perror("send");
    std::cout << "Welcome message sent successfully\n";
    pollfd p;
    p.fd = new_socket;
    p.events = POLLIN;
    readfds.push_back(p);
    server.client[p.fd] = &client;
    server.client[p.fd]->setPass(0);
    server.client[p.fd]->setNickName("");
    server.client[p.fd]->setUserName("");
    return (readfds);
}

void Client::send_recv_msg(std::vector<pollfd> &readfds, char *argv, int *index)
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
        std::cout << this->getPass() << std::endl;
        if ((command == "PASS" && parametre == argv))
        {
            std::cout << buffer << std::endl;
            this->setPass(1);
            std::cout << this->pass << std::endl;
        }
        if (command == "NICK" && this->getPass() == 1 && parametre.length() != 0)
        {
            this->nickname = parametre;
            std::cout << nickname << std::endl;
        }
        if (command == "USER" && this->getPass() == 1 && parametre.length() != 0)
        {
            this->user_name = parametre;
            std::cout << user_name << std::endl;
            // std::string us;
            // std ::stringstream str(parametre);
            // getline(str, us, ' ');
            // user.setUser(us);
            // getline(str, us, ' ');
            // user.setMode(us);
            // getline(str, us, ' ');
            // user.setUnused(us);
            // getline(str, us);
            // user.setRealname(us);
            // server.arr_name.push_back(&user);
        }
        if(!this->user_name.empty() && !this->nickname.empty())
        {
            std::cout << this->user_name << " " << this->nickname << std::endl;
            std::cout << "now you are connecte with nickname : " << this->nickname << std::endl;
        }
    }
}
