

#include "server.hpp"

int main(int argc, char *argv[])
{

    Client client;
    fd_set readfds;
    Server server;
    int serversocket = socket(AF_INET, SOCK_STREAM, 0);

    if (argc > 1)
    {
        serversocket = client.create_socket();
        client.addrlen = client.bind_socket_to_port(client, argv[1], serversocket);
        while (1)
        {
            readfds = client.connection_multi_client_srv(serversocket, readfds, client);
            client.send_recv_msg(client, readfds, argv[2],server);
            // puts ("------");
            // for (std::vector<std::string>::iterator it = server.arr_name.begin(); it != server.arr_name.end(); it++)
            //     std::cout <<"user : " << *it << std::endl;
            // puts ("------");
        }
    }

    return 0;
}