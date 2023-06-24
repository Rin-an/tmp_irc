#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "User.hpp"
#include "server.hpp"

class Server;
class User;
class Client
{
	int	flag;
	public:
		int addrlen;
		struct sockaddr_in hint;
		std::vector<int> client_socket;
		
		Client();
		~Client();
		int	getFlag();
		fd_set connection_multi_client_srv(int serversocket, fd_set readfds, Client &client);
		void send_recv_msg(Client &client, fd_set readfds, char *argv, Server &server);
		bool	ckeck_command(std::string command);
		void 	parse_ch_cmd(Client&, Server&, std::string, std::string);//), fd_set);
		int		channel_command(std::string&);
		void	exec_ch_command(std::string&, std::stringstream&, Server&);
		void	join_cmd(Server&);
};

#endif
