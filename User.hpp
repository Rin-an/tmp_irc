#ifndef USER_HPP
#define USER_HPP
#include "client.hpp"
#include "server.hpp"

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