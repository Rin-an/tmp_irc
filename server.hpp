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
#include "Channel.hpp"

class Server;
class User;
class Client;
class Channel;
class Server{

	public :
		int socket_server;
		std::map<int,Client > client;
		Server();
		~Server();
		Server(Server &);
		Server &operator=(Server &);
		int  create_socket(Server &server);
		int bind_socket_to_port(Client &client, char *argv, int serversocket);

};


#endif
