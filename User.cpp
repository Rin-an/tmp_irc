#include "User.hpp"

User:: User()
{

}
User:: ~User()
{

}
void User:: setUser(std::string& user)
{
    this->user = user;
}
void User:: setMode(std::string & mode)
{
    this->mode = mode;
}
void User:: setUnused(std::string & unused)
{
    this->unused = unused;
}
void User:: setRealname(std::string &realname)
{
    this->realname = realname;
}

std::string  & User :: getUser(void)
{
    return (this->user);
}
std::string & User :: getMode(void)
{
    return (this->mode);
}
std::string & User :: getUnused(void)
{
    return (this->unused);
}
std::string & User :: getRealname(void)
{
    return (this->realname);
}