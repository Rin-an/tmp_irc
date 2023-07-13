/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:49:57 by ssadiki           #+#    #+#             */
/*   Updated: 2023/07/13 16:25:13 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel()
{
	usernum = 0;
}

Channel::Channel(const std::string& n):name(n), usernum(0), topic(""), mode("")
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

const std::string&  Channel::getKey(void) const
{
    return (this->key);
}

int  Channel::getLimit(void) const
{
    return (this->limit);
}

int  Channel::getUsernum(void) const
{
    return (this->usernum);
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

void    Channel::setLimit(int l)
{
    this->limit = l;
}

void    Channel::incUsernum(void)
{
    (this->usernum)++;
}

void    Channel::decUsernum(void)
{
    (this->usernum)--;
}

/*int Channel::topic_cmd(std:string param)
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
}*/
