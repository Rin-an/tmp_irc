#include "server.hpp"
int Server:: pass = false;
Client:: Client(){}
Client :: ~Client(){}
int Client::  create_socket()
{
	int opt = 1; 
	int serversocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serversocket == -1)
    {
        std::cout << "socket creation failed" << std::endl;
        return 1;
    }
    if( setsockopt(serversocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
          sizeof(opt)) < 0 )  
    {  
        perror("setsockopt");  
        exit(EXIT_FAILURE);  
    } 
	return (serversocket);
}

int  Client::bind_socket_to_port(Client &client,char *argv,int serversocket)
{
	int  addrlen;
	client.hint.sin_family = AF_INET;
    client.hint.sin_port = htons(atoi(argv));
    inet_pton(AF_INET, "0.0.0.0", &(client.hint.sin_addr));
    if (bind(serversocket, (sockaddr*)&(client.hint), sizeof(client.hint)) == -1)
    {
        std::cout << "bind failed" << std::endl;
        return 2;
    }
    if(listen(serversocket, SOMAXCONN) == -1)
    {
        std::cout << "listen failed" << std::endl;
        return 3;
    }
    addrlen = sizeof(client.hint);  
    std::cout  << "enter your password[PASS]"<< std::endl;
    std::cout  << "enter your nickname[NICK]"<< std::endl;
    std::cout  << "enter your username[USER]"<< std::endl;
    std:: cout << "Waiting for connections ..." << std::endl;
	return (addrlen);
}
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
            printf("select error");
        if (FD_ISSET(serversocket, &readfds))  
        {  
            if (( new_socket = accept(serversocket, 
                    (struct sockaddr *)&client.hint, (socklen_t*)&(client.addrlen)))<0)  
            {  
                perror("accept");  
                exit(EXIT_FAILURE);  
            }
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(client.hint.sin_addr) , ntohs
                  (hint.sin_port)); 
            size_t j;
            if( (j = send(new_socket, message, strlen(message), 0)) != strlen(message) )
                perror("send");
            puts("Welcome message sent successfully");
            client.client_socket.push_back(new_socket);  
        }
        return (readfds);
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
                    if((command=="PASS" && parametre == argv))
                        server.pass = true;
                    if (command == "NICK" && server.pass == true)
                    {
                         std::vector<std::string >::iterator fnd = find(server.arr_nickname.begin(),server.arr_nickname.end(),parametre);
                        if(!server.arr_nickname.empty() && fnd == server.arr_nickname.begin())
                        {
                            std::cout << "Nickname '" << parametre << "' is already taken." << std::endl;
                            break ;
                        }
                        server.arr_nickname.push_back(parametre);
                    }
                    if (command == "USER" && server.pass == true)
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
                    if (!server.arr_nickname.empty() && !server.arr_name.empty())
                        std::cout << "now you are connecte with nickname : " << server.arr_nickname[i] << std::endl;
                }
            }
            i++;
        }
}


void Client :: setNickname(std::string const &nick)
{
    this->nickname = nick;
}
void Client :: setUser(std::string const &user)
{
    this->user = user;
}
std::string const & Client :: getNickname(void)
{
    return(this->nickname);
}
std::string const & Client :: getUser(void)
{
    return(this->user);
}
int const & Client :: getSocket(void)
{
    return(this->_socket);
}



Server:: Server()
{

}
Server:: ~Server()
{

}


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