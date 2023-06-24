#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include "client.hpp"
#include <deque>

class Server;
class User;
class Client;
class Channel{
	std::string	name;
	std::string	mode;
	public:
		Channel();
		~Channel();
		std::deque<Server *> op;
		std::deque<Server *> users;
		//std::deque<Server *> 
};
#endif
