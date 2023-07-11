#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#define CHANNEL_CHARS "&#+|"
#define CHANNEL_MODS "klito"
#include "client.hpp"
#include <deque>

class Server;
class Client;
class Channel{
	std::string name;
	std::string key;
	std::string topic;
	std::string mode;
	public:
		//std::deque<Client *> op;
		//std::deque<Client *> users;
		std::deque<std::string> op;
		std::deque<std::string> users;
		Channel();
		Channel(const std::string&);
		~Channel();
		const std::string&	getName(void) const;
		const std::string&	getTopic(void) const;
		const std::string&	getMode(void) const;
		void				setName(std::string&);
		void				setTopic(std::string&);
		void				setMode(std::string&);
		void				setKey(std::string&);
//		void				topic_cmd(std::string, std::deque<std::string>, std::deque<Channel*>);
//		void				mode_cmd(std::string, std::deque<std::string>, std::deque<Channel*>);
};
#endif
