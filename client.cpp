#include "client.hpp"

Client::Client() {}
Client ::~Client() {}

std::vector<pollfd> Client::connection_multi_client_srv(int serversocket, std::vector<pollfd> &readfds, Client &client)
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
    return (readfds);
}
std::string to_upper(std::string &str)
{
    int i;
    i = 0;
    std::string stri = str;
    while (stri[i])
    {
        stri[i] = toupper(stri[i]);
        i++;
    }
    return (stri);
}

void Client::send_recv_msg(Client &client, std::vector<pollfd> &readfds, char *argv, Server &server,int *index)
{
    char buffer[1024];
    User user;
    int i = 0;
    memset(buffer, 0, sizeof(buffer));
    int valread = read(readfds[*index].fd, buffer, 1024);
    if (valread <= 0)
    {
        getpeername(readfds[*index].fd, (struct sockaddr *)&(client.hint),
                    (socklen_t *)&(client.addrlen));
        printf("Host disconnected , ip %s , port %d \n",
               inet_ntoa(client.hint.sin_addr), ntohs(client.hint.sin_port));
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
        {
            server.pass = true;
            std::cout << server.pass << std::endl;
        }
        if (command == "NICK" && server.pass == true && parametre.length() != 0 && nickname_exist(server, parametre) != 1)
        {
            server.arr_nickname[i] = parametre;
            std::cout << server.arr_nickname[i] << std::endl;
        }
        if (command == "USER" && server.pass == true && parametre.length() != 0)
        {
            std::string us;
            std ::stringstream str(parametre);
            getline(str, us, ' ');
            user.setUser(us);
            getline(str, us, ' ');
            user.setMode(us);
            getline(str, us, ' ');
            user.setUnused(us);
            getline(str, us);
            user.setRealname(us);
            server.arr_name.push_back(&user);
        }
        if (!server.arr_nickname.empty() && !server.arr_name.empty() && server.arr_nickname.size() == size_t(i + 1) && server.arr_name.size() == size_t(i + 1))
            std::cout << "now you are connecte with nickname : " << server.arr_nickname[i] << std::endl;
    }
i++;
}
