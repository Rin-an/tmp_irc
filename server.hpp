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
#include "client.hpp"
#include "User.hpp"


class Server;
class User;
class Client;

class Server{

	public :
		static int pass;
		int socket_server;
		std::vector<User *> arr_name;
		std::map<int , std::string>  arr_nickname;


		Server();
		~Server();
		int  create_socket(Server &server);
		int bind_socket_to_port(Client &client, char *argv, int serversocket);
		// std::map<int , std::string> client_info;

};


#endif