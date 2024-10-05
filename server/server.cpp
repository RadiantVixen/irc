/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:07:54 by kkouaz            #+#    #+#             */
/*   Updated: 2024/04/24 18:34:43 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"
#include"header.hpp"

bool server :: signal = 0;

server :: server(int port, std :: string &password)
{
    _port = port;
    _password = password;
    serverSocket = -1;
}

void server:: recieveSignal(int signum)
{
    (void)signum;
    server :: signal = 1;
}


long server :: findClients(std::vector<Client> client, int fd)
{
    
    for(unsigned long i = 0; i < client.size();  i++)
    {
        if(client[i].getFd() == fd)
            return(i);
    }
    return(-1);
}

unsigned long server :: findClient(int fd)
{
    for(unsigned long i = 0; i < clients.size();  i++)
    {
        if(clients[i].getFd() == fd)
            return(i);
    }
    return(0);
}

void server :: setup()
{
    struct pollfd pollfds;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket < 0)
        throw std::runtime_error("unable to create a socket !!");
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(_port);
    address.sin_addr.s_addr = INADDR_ANY;
    int n = 1;
    if(setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &n, sizeof(n)) == -1) 
        throw(std::runtime_error("unable to set option (SO_REUSEADDR) on socket"));
    if(fcntl(serverSocket, F_SETFL, O_NONBLOCK) == -1)
         throw std::runtime_error("non_blocking mode errror !!");
    if(bind(serverSocket, (struct sockaddr *)&address,sizeof(address)) < 0)
        throw std::runtime_error("unable to bind the socket !!");
    if (listen(serverSocket, SOMAXCONN) == -1) 
        throw(std::runtime_error("listen() failed"));
    
    pollfds.fd = serverSocket;
    pollfds.events = POLLIN;
    pollfds.revents = 0;
    fds.push_back(pollfds);
}

void server::clearClients(int fd)
{ 
    for(size_t i = 0; i < fds.size(); i++)
    {
        if (fds[i].fd == fd)
        {
            fds.erase(fds.begin() + i);
            break;
        }
    }
    for(size_t i = 0; i < clients.size(); i++)
    { 
        if (clients[i].getFd() == fd)
        {
            clients.erase(clients.begin() + i);
            break;
        }
    }

}

void server :: recieveData(int fd)
{
    char buffer[1024];
    ssize_t recieved;

    recieved = recv(fd, buffer, sizeof(buffer) - 1, 0);
    if(recieved < 0)
    {
        std :: cout << " disconnected client \n";
        clearClients(fd);
        close(fd);
    }
    else
    {
        if(recieved == 0)
        {
            std :: cout << "client " << fd << "  disconnected \n";
            clearClients(fd);
            close(fd);
        }
        buffer[recieved ] = 0;
        checkData(buffer, fd);
        unsigned long i = findClient(fd);
        std :: string buf = buffer;
        if(clients[i].isRegistred() && clients[i].hasNick() && clients[i].hasUser())
        {
            creating_channels(buffer,clients[findClients(clients, fd)]);
        }
           
    }
}

void server :: CapCommand(std :: string data, int fd)
{
    if (data.substr(0, 3) == "CAP")
    {
        std :: vector<std :: string > names;
        std :: string s;
        for (unsigned long i = 0; i <=  data.length() ; i++)
        {
            if(data[i] != '\n' )
                s.push_back(data[i]);
            else
            {
                s.push_back(0);
                names.push_back(s);
                s.clear();
            }
        }
        for (unsigned long i = 1; i <  names.size() ; i++)
        {
            if(names[i].substr(0,4) == "PASS")
                PassCommand(names[i], fd);
            if(names[i].substr(0,4)== "NICK")
                NickCommand(names[i], fd);
            if(names[i].substr(0,4) == "USER")
                UserCommand(names[i], fd);
        }
    }
}

void server :: PassCommand(std :: string data, int fd)
{
    if (data.substr(0, 5) == "PASS ")
    {
        std :: string str = data.substr(5, data.size());
        unsigned long i = findClient(fd);
        if(clients[i].isRegistred())
        {
            std::string msg = "client already registred\n";
            int msgSize = msg.size();
            if (send(fd, msg.c_str(), msgSize, 0) == -1)
            {
                std::cout << "send failed!" << std::endl;
            }
        }
           
        else
        {
            if( str.compare(_password + "\r\n") && str.compare(_password + "\n"))
            {
                std::string msg = ":localhost 464 * :Password incorrect, Try again please\n";
                int msgSize = msg.size();
                if (send(fd, msg.c_str(), msgSize, 0) == -1)
                {
                    std::cout << "send failed!" << std::endl;
                }
            }
            else
            {

                std::string msg = ":localhost 001 " + clients[i].getNickName() + " :Welcome to the IRC Network, " + clients[i].getNickName() + "!\n";
                if (send(fd, msg.c_str(), msg.size(), 0) == -1)
                {
                    std::cout << "send failed!" << std::endl;
                }
                clients[i].beRegistred();
            }
        }
    }
}

void server :: userCheck(std :: string str, int i )
{
    std :: vector<std :: string > names;
    std :: string s;

    for (unsigned long i = 0; i <= str.length() ; i++)
    {
        if(str[i] != ' ' && str[i] != 0)
            s.push_back(str[i]);
        else
        {
            s.push_back(0);
            names.push_back(s);
            s.clear();
        }
    }
    if(names.size() != 4)
        std :: cout << " error:)\n";
    else
    {
        if(checkdupUser(names[0]))
            return;
        else
        {  
            clients[i].setUser(names[0]);
            clients[i].setHostname(names[1]);
            clients[i].setServername(names[2]);
            clients[i].setRealname(names[3]);
        }
    }

}

int server :: checkdupUser(std :: string str)
{

    for(unsigned long i = 0 ; i < clients.size(); i++)
    {
        if(clients[i].getUser()  == str )
        {
            std :: cout << "Username already used , try a new one\n";
            return(1);
        }

    }
    return(0);
}

void server :: UserCommand(std :: string data, int fd)
{
    if (data.substr(0, 5) == "USER ")
    {
        std :: string str = data.substr(5);
        unsigned long i = findClient(fd);
        if(clients[i].isRegistred() && clients[i].hasNick())
        {
            userCheck(str, i);
        }
        else
        {
            std::string msg = "enter password and nickname  first !!\n";
            int msgSize = msg.size();
            if (send(fd, msg.c_str(), msgSize, 0) == -1)
            {
                std::cout << "send failed!" << std::endl;
            }
        }
    }
}

int server :: checkNick(std :: string str)
{
    std :: string rmStr;
    std :: string cmp;

    rmStr = rm(str);
    for(unsigned long i = 0 ; i < clients.size(); i++)
    {
        if(rm(clients[i].getNickName() ) == rmStr )
        {
            return(1);
        }

    }
    return(0);
}

void server :: NickCommand(std :: string data, int fd)
{
    if (data.substr(0, 5) == "NICK ")
    {
        send(fd, "....\n", 5, 0);
        std :: string str = data.substr(5);
        unsigned long i = findClient(fd);
        if(clients[i].isRegistred())
        {
            if(!checkNick(str))
            {
                clients[i].setNickName(str);
                std::string msg = "Nickname set to: " + clients[i].getNickName() + "\n";
                int msgSize = msg.size();
                if (send(fd, msg.c_str(), msgSize, 0) == -1)
                {
                    std::cout << "send failed!" << std::endl;
                }
            }
            else
            {
                std :: string msg = "Nickname already used , try a new one\n";
                int msgSize = msg.size();
                if (send(fd, msg.c_str(), msgSize, 0) == -1)
                {
                    std::cout << "send failed!" << std::endl;
                }
            }
        }
        else
        {
            std::string msg = "Enter password first\n";
            int msgSize = msg.size();
            if (send(fd, msg.c_str(), msgSize, 0) == -1)
            {
                std::cout << "send failed!" << std::endl;
            }
        }
    }
}

void server :: checkData(std :: string data, int fd)
{
    CapCommand(data,fd);
    PassCommand(data, fd);
    UserCommand(data, fd);
    NickCommand(data, fd);
    
}

void server :: acceptAclient()
{
    Client newClient;
    struct sockaddr_in clientAddr;
    struct pollfd clientfds;
    socklen_t size = sizeof(clientAddr);

    int fdc = accept(serverSocket, (sockaddr *) &clientAddr, &size);
    if(fdc == -1)
        throw(std::runtime_error("accept() faild"));
    if(fcntl(fdc, F_SETFL, O_NONBLOCK) == -1)
         throw std::runtime_error("non_blocking mode errror !!");
    clientfds.fd = fdc;
    clientfds.events = POLLIN;
    clientfds.revents = 0;
    newClient.setFd(fdc);
    newClient.setIpAdress((inet_ntoa((clientAddr.sin_addr))));
    clients.push_back(newClient);
    fds.push_back(clientfds);

    std :: cout << "client : " << fdc << "   is connected\n";
    
}

void server :: start()
{
    while(server :: signal == 0)
    {
        if(poll(&fds[0],fds.size(), -1) == -1 && server :: signal == 0)
            throw(std::runtime_error("poll() failed"));
        for(size_t i = 0 ; i < fds.size(); i++)
        {
            if ((fds[i].revents & POLLIN ))
            {
                if(fds[i].fd == serverSocket  && server :: signal == 0)
                    acceptAclient();
                else
                    recieveData(fds[i].fd);
            }
        }
    }
}

void server::closeFds()
{
    for(size_t i = 0; i < clients.size(); i++)
    { 
        std::cout << "Client " << clients[i].getFd() << " Disconnected"  << std::endl;
        close(clients[i].getFd());
    }
    if (serverSocket != -1)
    { 
    std::cout <<  "Server " << serverSocket<< "> Disconnected" <<  std::endl;
    close(serverSocket);
    }
}

server :: ~server()
{
    // closeFds();
}