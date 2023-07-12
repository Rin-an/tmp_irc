/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:12:09 by zel-hach          #+#    #+#             */
/*   Updated: 2023/07/12 15:33:27 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "client.hpp"
#include "User.hpp"
#include <poll.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/ioctl.h>

std::deque<Channel> g_chs;

int main(int argc, char *argv[])
{
    Client client;
    std::vector<pollfd> readfds(1);
    int new_size;
    Server server;
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
                    readfds = client.connection_multi_client_srv(serversocket, readfds,server);
                else
                    server.client[readfds[index].fd].send_recv_msg(readfds, argv[2], &index,server);
            }
        }
    }
    return 0;
}
