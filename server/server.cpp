/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkouaz <kkouaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:07:54 by kkouaz            #+#    #+#             */
/*   Updated: 2024/04/22 18:23:50 by kkouaz           ###   ########.fr       */
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


void server :: recieveData(int fd)
{
    char buffer[1024];
    ssize_t recieved;

    recieved = recv(fd, buffer, sizeof(buffer) - 1, 0);
    if(recieved < 0)
    {
        std :: cout << " disconnected client \n";
        exit(0);
    }
    else
    {
        if(recieved == 0)
        {
            std :: cout << "client " << fd << "  disconnected \n";
            close(fd);
        }
        buffer[recieved ] = 0;
        checkData(buffer, fd);
        unsigned long i = findClient(fd);
        std :: string buf = buffer;
        if(clients[i].isRegistred() && clients[i].hasNick() && clients[i].hasUser())
        {
            if(buf.substr(0,4) == "PING :")
            {
                std :: string pong = "PONG :";
                if(buf.size() > 5)
                    pong +=buf.substr(5);
                pong+="\r\n";
                send(fd,pong.c_str(),pong.size(),0);
            }

            // std :: string msg1 = clients[i].getServername()+ "001 "+ clients[i].getNickName()+" :Welcome to the Internet Relay Network\r\n";

            // send(fd, msg4.c_str(), msg4.length(), 0);
            // send(fd, ":<ServerName> 002 <Nickname> :Your host is <ServerName> <ServerVersion>\r\n", strlen(":<ServerName> 002 <Nickname> :Your host is <ServerName> <ServerVersion>\r\n"), 0);
            // send(fd, ":<ServerName> 003 <Nickname> :This server was created <CreationDate>\r\n", strlen(":<ServerName> 003 <Nickname> :This server was created <CreationDate>\r\n"), 0);
            // send(fd, ":<ServerName> 004 <Nickname> :<ServerName> <ServerVersion> More info\r\n", strlen(":<ServerName> 004 <Nickname> :<ServerName> <ServerVersion> More info\r\n"), 0);

            douzi_3andi_a_zine(buffer,clients[findClients(clients, fd)]);
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
            std :: cout  << "client already registred\n";
        else
        {
            if(str.compare(_password + "\r\n") && str.compare(_password + "\n"))
            {
                std :: cout << "invalid password try again please\n";
            }
            else
            {
                std :: cout << "welcome !!\n";
                clients[i].beRegistred();
            }
        }
    }
}

void server :: userCheck(std :: string str, int i )
{
    std :: vector<std :: string > names;
    std :: string s;

    for (unsigned long i = 0; i <=  str.length() ; i++)
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
        std :: cout << " error u must enter all the four :)\n";
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
////













            // :A 001 KAOUTHAR :Welcome to the Relay Network, :KAOUTHAR!A@localhost 
            // :A 002 KAOUTHAR :Your host is A, running version ft_irc
            // :A 003 KAOUTHAR :This server was created Mon Apr 22 15:18:03 2024
            // :A 004 KAOUTHAR A ft_irc More info
            std::string msg1 = ":" + clients[i].getServername()+" 001 " +(rn(clients[i].getNickName()))+ " :Welcome to the Relay Network, " + rn(clients[i].getNickName())+"!"+rn(clients[i].getUser())+"@localhost" + "\r\n"; 
		    std::string msg2 = ":" + clients[i].getServername()+" 002 " + (rn(clients[i].getNickName())) + " :Your host is " + clients[i].getServername()+", running version ft_irc\r\n";
		    std::string msg3 = ":" + clients[i].getServername()+" 003 " + (rn(clients[i].getNickName())) + " :This server was created " + "0" +"\r\n"; 
		    std::string msg4 = ":" + clients[i].getServername()+" 004 " + (rn(clients[i].getNickName())) + " " + clients[i].getServername()+ " ft_irc More info\r\n"; 

            // std :: string msg4 = clients[i].getServername()+ "004 "+ clients[i].getNickName()+" :Welcome to the Internet Relay Network\r\n";


           int fd = clients[i].getFd();

            send(fd, msg1.c_str(), msg1.size(), 0);
             send(fd, msg2.c_str(), msg2.size(), 0);
            send(fd, msg3.c_str(), msg3.size(), 0);
            send(fd, msg4.c_str(), msg4.size(), 0);
        }
    }

}



int server :: checkdupUser(std :: string str)
{
    // std :: string rmStr;
    // std :: string cmp;


    // rmStr = rm(str);
   
    
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
            // clients[i].setUser(str);
            // std :: cout << "user =  " << clients[i].getUser();
        }
        else
            std :: cout << "enter password and nickname  first !!\n";
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
            std :: cout << "Nickname already used , try a new one\n";
            return(1);
        }

    }
    return(0);
}

void server :: NickCommand(std :: string data, int fd)
{
    if (data.substr(0, 5) == "NICK ")
    {
        std :: string str = data.substr(5);
        unsigned long i = findClient(fd);
        if(clients[i].isRegistred())
        {
            if(!checkNick(str))
                clients[i].setNickName(str);
            std :: cout << "nickname  =  " << clients[i].getNickName();
        }
        else
            std :: cout << "enter password first\n";
    }
}
void server :: checkData(std :: string data, int fd)
{
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


server ::  ~server()
{
}
