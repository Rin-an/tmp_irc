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
    return (this->mode;
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
    (this->mode).find("t") == string::npos ? return (ERR_NOCHANMODES) : continue;
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

void    Client::parse_ch_cmd(Client &c, Server& s, std::string command, std::string parametre)//, fd_set readfds)
{
/*  std ::stringstream str(buffer);
    std::string command;
    std::string parametre;
    getline(str, command,' ');
    command = to_upper(command);*/
    (void)c;
    (void)s;
    std::cout << "COMMAND: " << command << "$" << std::endl;
    if (command == "JOIN" || command == "MODE" || command == "INVITE" \
            || command == "TOPIC" || command == "USER" || command == "NICK")
        //  exec_ch_command(command, str, s);
        std::cout << "cmd: " << command << " ,parametres " << parametre << std::endl;
    else
    {
        std::cout << "No such command" << std::endl;
        return;
    }
}
