#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "User.hpp"
#include "server.hpp"
#include <poll.h>

class Server;
class User;
class Client
{
public:
	int addrlen;
	struct sockaddr_in hint;
	std::vector<int> client_socket;
	Client();
	~Client();
	std::vector<pollfd> connection_multi_client_srv(int serversocket,std::vector<pollfd> &readfds, Client &client);
	void send_recv_msg(Client &client, std::vector<pollfd> &readfds, char *argv, Server &server,int *index);
	bool ckeck_command(std::string command);
};

std::string to_upper(std::string &str);
int nickname_exist(Server server,std::string parametre);
void ft_strtrim(std::string& str);
#endif