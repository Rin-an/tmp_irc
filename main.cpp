#include "server.hpp"
#include "client.hpp"
#include "User.hpp"


int main(int argc, char *argv[])
{

	Client client;
	fd_set readfds;
	Server server;
	int serversocket = socket(AF_INET, SOCK_STREAM, 0);

	if (argc > 1)
	{
		serversocket = server.create_socket(server);
		client.addrlen = server.bind_socket_to_port(client, argv[1], serversocket);
		while (1)
		{
			readfds = client.connection_multi_client_srv(serversocket, readfds, client);
			client.send_recv_msg(client, readfds, argv[2],server);
			puts ("------");
			for (std::map<int, std::string>::iterator it = server.arr_nickname.begin(); it != server.arr_nickname.end(); it++)
				std::cout <<"nickname : " << it->second << std::endl;
			puts ("------");
		//	client.parse_ch_cmd(client, server, readfds);
		}
	}

	return 0;
}
