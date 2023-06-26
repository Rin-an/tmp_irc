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
        std::deque<Server *> op;
        std::deque<Server *> users;
        Channel();
        Channel(const std::string&);
        ~Channel();
        const std::string&  getName(void) const;
        const std:string&   getTopic(void) const;
        const std::string&  getMode(void) const;
        void                setName(std::string&);
        void                setTopic(std::string&);
        void                setMode(std::string&);
        void                setKey(std::string&);
        int                 topic_cmd(std::string);
};
#endif
