#include "client.hpp"

Client:: Client(){}
Client :: ~Client(){}

bool Client :: ckeck_command(std::string command)
{
    if (command == "PASS" || command == "NICK"|| command == "USER")
        return 1;
    return 0;        
}
fd_set Client:: connection_multi_client_srv(int serversocket,fd_set readfds, Client &client)
{
        int new_socket;
        int max_sd,sd;
        int  activity;
        char message[21] = "welcome to client \r\n";  
        FD_ZERO(&readfds);  
        FD_SET(serversocket, &readfds);  
        max_sd = serversocket;
        for (std::vector<int>::iterator it  = client.client_socket.begin(); it < client.client_socket.end(); it++)  
        {  
            sd = *it;
            if(sd > 0)  
                FD_SET( sd , &readfds);  
            if(sd > max_sd)  
                max_sd = sd;  
        }
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
        if ((activity < 0) && (errno!=EINTR))   
            std::cout << "select error\n";
        if (FD_ISSET(serversocket, &readfds))  
        {  
            if (( new_socket = accept(serversocket, 
                    (struct sockaddr *)&client.hint, (socklen_t*)&(client.addrlen)))<0)  
            {  
                perror("accept");  
                exit(EXIT_FAILURE);  
            }
            std::cout << "New connection , socket fd is  "<< new_socket <<", ip is : " << inet_ntoa(client.hint.sin_addr) << ", port : " <<  ntohs(hint.sin_port) << "\n";
            size_t j;
            if( (j = send(new_socket, message, strlen(message), 0)) != strlen(message) )
                perror("send");
            std::cout << "Welcome message sent successfully\n";
            client.client_socket.push_back(new_socket);  
        }
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
    char buffer[1025];
    int  sd, valread;
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
                    getline(str, parametre);
                    ft_strtrim(parametre);
					command = to_upper(command);
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
                        std::cout << "now you are connecte with nickname : " << server.arr_nickname[i] << std::endl;
                }
            }
            i++;
        }
}
