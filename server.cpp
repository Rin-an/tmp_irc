
#include "server.hpp"





Server:: Server()
{

}

Server:: ~Server()
{

}
int Server::  create_socket(Server &server)
{
	int opt = 1; 
	int serversocket = socket(AF_INET, SOCK_STREAM, 0);
	server.socket_server = serversocket;
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

int  Server::bind_socket_to_port(Client &client,char *argv,int serversocket)
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
