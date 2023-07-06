#include "client.hpp"

Client:: Client(): flag(0) {}

Client :: ~Client(){}

bool Client :: ckeck_command(std::string command)
{
	if (command == "PASS" || command == "NICK"|| command == "USER")
		return 1;
	return 0;        
}

int	Client::getFlag()
{
	return (this->flag);
}

int Client::getPass()
{
    return (this->pass);
}

std::string Client::getUserName(void)
{
    return (this->user_name);
}

std::string Client::getNickName(void)
{
    return (this->nickname);
}

void Client::setPass(int pass)
{
    this->pass = pass;
}

void Client::setUserName(std::string user_name)
{
    this->user_name = user_name;
}

void Client::setNickName(std::string nick_name)
{
    this->nickname = nick_name;
}

std::vector<pollfd> Client::connection_multi_client_srv(int serversocket, std::vector<pollfd> &readfds, Client &client, Server &server)
{
    int new_socket;
    char message[21] = "welcome to client \r\n";
    if ((new_socket = accept(serversocket,
                             (struct sockaddr *)&client.hint, (socklen_t *)&(client.addrlen))) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    std::cout << "New connection , socket fd is  " << new_socket << ", ip is : " << inet_ntoa(client.hint.sin_addr) << ", port : " << ntohs(client.hint.sin_port) << "\n";
    size_t k;
    if ((k = send(new_socket, message, strlen(message), 0)) != strlen(message))
        perror("send");
    std::cout << "Welcome message sent successfully\n";
    pollfd p;
    p.fd = new_socket;
    p.events = POLLIN;
    readfds.push_back(p);
    server.client[p.fd] = &client;
    server.client[p.fd]->setPass(0);
    server.client[p.fd]->setNickName("");
    server.client[p.fd]->setUserName("");
    return (readfds);
}

std::string to_upper(std::string &str)
{
	int i;
	i = 0;
	std::string stri = str;
	while (stri[i])
	{
		stri[i] = toupper(stri[i]);
		i++;
	}
	return(stri);
}

int nickname_exist(Server server,std::string parametre)
{
	for (std::map<int , std::string>::iterator it = server.arr_nickname.begin(); it != server.arr_nickname.end() ; it++)
	{
		if (it->second == parametre)
		{
			std::cout << "Nickname '" << parametre << "' is already taken." << std::endl;
			return (1);
		}
	}
	return (0);
}

void ft_strtrim(std::string& str)
{
	str.erase(0, str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
}

void Client:: send_recv_msg(Client &client, fd_set readfds, char *argv, Server &server)
{
	char	buffer[1025];
	int		sd, valread;
	User user;
	int i = 0;

	for (std::vector<int>::iterator it  = client.client_socket.begin(); it < client.client_socket.end(); it++)  
	{  
		sd = *it ;
		if (FD_ISSET(sd , &readfds))  
		{
			if ((valread = read( sd , buffer, 1024)) == 0)  
			{
				getpeername(sd , (struct sockaddr*)&(client.hint) , \
						(socklen_t*)&(client.addrlen));  
				printf("Host disconnected , ip %s , port %d \n" , 
						inet_ntoa(client.hint.sin_addr) , ntohs(client.hint.sin_port));  
				close(sd);
				*it = 0;
			}  
			else 
			{
				buffer[valread] = '\0';
				std ::stringstream str(buffer);
				std::string command;
				std::string parametre;
				getline(str, command,' ');
				command = to_upper(command);
				getline(str, parametre);
				ft_strtrim(parametre);
				std::cout << "COMMAND: " << command << "$" << std::endl;
				if (!this->flag)
				{
					if((command=="PASS" && parametre == argv))
						server.pass = true;
					if (command == "NICK" && server.pass == true && parametre.length() != 0 && nickname_exist(server,parametre) != 1)
						server.arr_nickname[i] = parametre;
					if (command == "USER" && server.pass == true && parametre.length() != 0)
					{
						std::string us;
						std ::stringstream str(parametre);
						getline(str,us,' ');
						user.setUser(us);
						getline(str,us,' ');
						user.setMode(us);
						getline(str,us,' ');
						user.setUnused(us);
						getline(str,us);
						user.setRealname(us);
						server.arr_name.push_back(&user);
					}
					if (!server.arr_nickname.empty() && !server.arr_name.empty() && server.arr_nickname.size() == size_t(i + 1) && server.arr_name.size() == size_t(i + 1))
					{
						this->flag = 1;
						std::cout << "now you are connecte with nickname : " << server.arr_nickname[i] << std::endl;
					}
				} //end if flag
			/*	else 
					client.parse_ch_cmd(client, server, command, parametre);*/
			} //end parent else
		} //end parent if
		i++;
	} //end loop
}

void	Client::parse_ch_cmd(Client &c, Server& s, std::string command, std::string parametre)//, fd_set readfds)
{
/*	std ::stringstream str(buffer);
	std::string command;
	std::string parametre;
	getline(str, command,' ');
	command = to_upper(command);*/
	(void)c;
	(void)s;
	std::cout << "COMMAND: " << command << "$" << std::endl;
	if (command == "JOIN" || command == "MODE" || command == "INVITE" \
			|| command == "TOPIC" || command == "USER" || command == "NICK")
		//	exec_ch_command(command, str, s);
		std::cout << "cmd: " << command << " ,parametres " << parametre << std::endl;
	else
	{
		std::cout << "No such command" << std::endl;
		return;
	}
}
