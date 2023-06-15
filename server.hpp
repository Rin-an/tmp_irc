#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <sys/types.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>
#include <map>
#include <vector>
class Server;
class User;
class Client
{
	// std::string _host;
	// std::string _port;
	// std::string _password;
	std::string nickname;
	std::string user;
	int _socket;

public:
	int addrlen;
	struct sockaddr_in hint;
	std::vector<int> client_socket;
	Client();
	~Client();
	void setNickname(std::string const &);
	void setUser(std::string const &);
	std::string const & getNickname(void);
	std::string const & getUser(void);
	int const & getSocket(void);
	int create_socket();
	int bind_socket_to_port(Client &, char *argv, int serversocket);
	fd_set connection_multi_client_srv(int serversocket, fd_set readfds, Client &client);
	void send_recv_msg(Client &client, fd_set readfds, char *argv, Server &server);
	bool ckeck_command(std::string command);
};

class Server{

	public :
		static int pass;
		Server();
		~Server();
		std::vector<User *> arr_name;
		std::vector<std::string> arr_nickname;
		// std::map<std::string , std::string> client_info;

};

class User{
	std::string user;
	std::string  mode; 
	std::string unused;
	std::string realname;
	public:
	User();
	~User();
	void setUser(std::string &);
	void setMode(std::string &);
	void setUnused(std::string &);
	void setRealname(std::string &);
	std::string  & getUser(void);
	std::string & getMode(void);
	std::string & getUnused(void);
	std::string & getRealname(void);
};

#endif