#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "User.hpp"
#include "server.hpp"
#include <poll.h>

class Server;
class User;
class Client
{
	int pass;
	std::string user_name;
	std::string nickname;
public:
	int addrlen;
	struct sockaddr_in hint;
	int getPass();
	std::string getUserName(void);
	std::string getNickName(void);
	void setPass(int);
	void setUserName(std::string);
	void setNickName(std::string);
	// std::vector<int> client_socket;
	Client();
	~Client();
	std::vector<pollfd> connection_multi_client_srv(int serversocket, std::vector<pollfd> &readfds, Client &client,Server &server);
	void send_recv_msg(std::vector<pollfd> &readfds, char *argv, int *index);
	bool ckeck_command(std::string command);
};
std::string to_upper(std::string &str);
int nickname_exist(Server server, std::string parametre);
void ft_strtrim(std::string &str);
#endif