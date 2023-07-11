#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "Channel.hpp"

void	topic_cmd(std::string, std::deque<std::string>::iterator);
void	invite_cmd(std::string, std::deque<std::string>::iterator);
void	mode_cmd(std::string, std::deque<std::string>::iterator);
void	join_cmd(std::string, std::deque<std::string>::iterator);
void	kick_cmd(std::string, std::deque<std::string>::iterator);
void	user_cmd(std::string, std::deque<std::string>&);
void    split_param(std::string, std::vector<std::string>&, std::vector<std::string>&);
int		valid_ch(std::vector<std::string>&);
#endif
