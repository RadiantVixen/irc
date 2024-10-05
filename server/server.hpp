/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 02:24:39 by kkouaz            #+#    #+#             */
/*   Updated: 2024/04/24 15:27:15 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include <poll.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../channels/channels.hpp"
#include <fstream>

class Channel;
using namespace std;


class server
{
    private:
        int serverSocket;
        int _port;
        std ::string _password;
        std :: vector <Client> clients;
        std :: vector <Channel> channels;
        std :: vector <struct pollfd> fds;
        static bool  signal;
    public: 
        static void recieveSignal(int signum);
        server(int port, std :: string &password);
        void setup();
        void start();
        void clearClients(int fd);
        void acceptAclient();
        void recieveData(int fd);
        void checkData(std :: string data, int fd);
        long findClients(std::vector<Client> client, int fd);
        void PassCommand(std :: string data, int fd);
        void UserCommand(std :: string data, int fd);
        void NickCommand(std :: string data, int fd);
        void creating_channels(std::string buffer, Client client);
        void ft_join(std::string name, Client client);
        void ft_kick(std::string buffer, Client client);
        void ft_privmsg(std::string buffer, Client client);
        void ft_mode(std::string buffer, Client client);
        void ft_topic(std::string buffer, Client client);
        void ft_invite(std::string buffer, Client client);
        void ft_part(std::string buffer, Client client);
        int checkNick(std :: string str);
        void userCheck(std :: string str, int i);
        int checkdupUser(std :: string str);
        unsigned long findClient(int fd);
        void CapCommand(std :: string data, int fd);
        void closeFds();
        ~server();
};

#   endif