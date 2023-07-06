#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "User.hpp"
#include "server.hpp"
#include <poll.h>

class Server;
class User;
class Client
{
	int	flag;
	int pass;
	std::string user_name;
	std::string nickname;

	public:
		int addrlen;
		struct sockaddr_in hint;
	//	std::vector<int> client_socket;
		Client();
		~Client();
		int getPass();
		std::string getUserName(void);
		std::string getNickName(void);
		void setPass(int);
		void setUserName(std::string);
		void setNickName(std::string);
		int	getFlag();
		std::vector<pollfd> connection_multi_client_srv(int serversocket, std::vector<pollfd> &readfds, Client &client,Server &server);
		void send_recv_msg(std::vector<pollfd> &readfds, char *argv, int *index);
		bool	ckeck_command(std::string command);
		void 	parse_ch_cmd(Client&, Server&, std::string, std::string);//), fd_set);
		int		channel_command(std::string&);
		void	exec_ch_command(std::string&, std::stringstream&, Server&);
		void	join_cmd(Server&);
};
std::string to_upper(std::string &str);
int nickname_exist(Server server, std::string parametre);
void ft_strtrim(std::string &str);

#endif
