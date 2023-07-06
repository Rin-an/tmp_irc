#include "server.hpp"
#include "client.hpp"
#include "User.hpp"
#include <poll.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main(int argc, char *argv[])
{
    Client client;
    std::vector<pollfd> readfds(1);
    int new_size;
    Server server;
    // User user;
    int serversocket;
    if (argc > 1)
    {
        serversocket = server.create_socket(server);
        client.addrlen = server.bind_socket_to_port(client, argv[1], serversocket);
        readfds[0].fd = serversocket;
        readfds[0].events = POLLIN;
        while (1)
        {
            int activity;
            activity = poll(readfds.data(), readfds.size(), -1);
            if ((activity < 0))
                std::cout << "select error\n";
            new_size = readfds.size();
            for (int index = 0; index < new_size; index++)
            {
                if (readfds[index].revents == 0)
                    continue;
                if (readfds[index].revents != POLLIN)
                {
                    std::cout << " error" << std::endl;
                    break;
                }
                if (readfds[index].fd == serversocket)
                {
                    std::cout << readfds[index].fd << std::endl;
                    readfds = client.connection_multi_client_srv(serversocket, readfds, client, server);
                    std::cout << readfds[index].fd << std::endl;
                    
                }
                else
                {
                    server.client[readfds[index].fd]->send_recv_msg(readfds, argv[2], &index);
                    
                }
            }
        }
    }
    return 0;
}
