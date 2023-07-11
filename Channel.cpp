#include "Channel.hpp"

Channel::Channel(){}

Channel::Channel(const std::string& n):name(n), topic(""), mode("")
{

}

Channel::~Channel() {}

const std::string&  Channel::getName(void) const
{
    return (this->name);
}

const std::string&  Channel::getTopic(void) const
{
    return (this->topic);
}

const std::string&  Channel::getMode(void) const
{
    return (this->mode);
}

void    Channel::setName(std::string& n)
{
    this->name = n;
}

void    Channel::setTopic(std::string& t)
{
    this->topic = t;
}

void    Channel::setMode(std::string& m)
{
    this->mode = m;
}

void    Channel::setKey(std::string& k)
{
    this->key = k;
}

int Channel::topic_cmd(std:string param)
{
    // (this->mode).find("t") == string::npos ? return (ERR_NOCHANMODES) : continue;
    std::stringstream   str(param);
    std::string         ch_n, t;
    std::getline(str, ch_n, ' ');

    if (param.empty())
    {
        std::cout << name << " topic: " << topic << std::endl;
        return ;
    }
    std::getline(str, t);
}
