/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:36:01 by zel-hach          #+#    #+#             */
/*   Updated: 2023/07/13 16:56:26 by zel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include <deque>
#include <vector>
#include "client.hpp"
#include "User.hpp"
#include "Channel.hpp"

class User;
class Client;
class Channel;
class Server{

	public :
		int socket_server;
		std::map<int,Client > client;
		std::deque<Channel *>  chs;
		Server();
		~Server();
		Server(Server &);
		Server &operator=(Server &);
		int  create_socket(Server &server);
		int bind_socket_to_port(Client &client, char *argv, int serversocket);

};


#endif
