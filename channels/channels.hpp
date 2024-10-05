/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channels.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 06:47:46 by aatki             #+#    #+#             */
/*   Updated: 2024/04/21 18:21:58 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELS_HPP
#define CHANNELS_HPP

# include <iostream>
#include <sstream>
# include <vector>
# include <map>
#include "../server/client.hpp"
#include "../server/server.hpp"
#include "../server/header.hpp"

class server;

class Channel
{
    private:
        int limit;
        int cltNumbr;
        std::vector<Client> operatorss;
        std::string name;
        std::string topic;
        std::string key;
        std::vector<Client> chl_cls;
        std::vector<int>   invetation;
        std::map<std::string, int> modes;
    public:
        Channel(std::string name);
        int getLimit();
        int getCltNumbr();
        std::string getName();
        std::string getTopic();
        std::string getKey();
        void setKey(Client client, std::string key);
        void setLimit(Client client, int fd, std::string limit);
        void setOperator(Client client, int fd,std::string op);
        void removeOperator(Client client, int fd, std::string op);
        int findOperator(int fd);
        std::vector<Client> getClients();
        std::vector<Client> getOperator();
        std::map<std::string, int> getModes();
        int findInvite(int fd);
        void join(Client client, std::string strkey);
        void invite(Client client, int fd, std::string message);
        void kick(Client client, std::string nickName, std::string reason);
        void ftopic(Client client, std::string buffer);
        void addMode(Client client, std::string a_mode);
        void removeMode(Client client, std::string mode);
        void part(Client client, int fd, int i, std::string reason);
        ~Channel();
};

long findchannel(std::vector<Channel> channels, std::string name);
long findClient2(std::vector<Client> chl_cls,std::string nickName);
void sendMessage(int fd, std::string message);
std::string intToString(int value);

#endif
