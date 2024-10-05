/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channels.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkouaz <kkouaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 00:11:24 by aatki             #+#    #+#             */
/*   Updated: 2024/04/22 00:51:04 by kkouaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channels.hpp"

Channel::Channel(std::string name)
{
    modes["i"] = 0;
    modes["t"] = 0;
    modes["k"] = 0;
    modes["o"] = 0;
    modes["l"] = 0;
    cltNumbr = 0;
    topic = "defaut";
    this->name = name;
}

std::string Channel::getName()
{
    return name;
}

std::string Channel::getTopic()
{
    return topic;
}

std::string Channel::getKey()
{
    return key;
}

int Channel::getLimit()
{
    return limit;
}

int Channel::getCltNumbr()
{
    return cltNumbr;
}

std::vector<Client> Channel::getOperator()
{
    return operatorss;
}

std::vector<Client> Channel::getClients()
{
    return chl_cls;
}

void Channel::setKey(Client client, std::string key)
{
    (void) client;
    this->key = key;
}

void Channel::setLimit(Client client, int fd, std::string str)
{
    (void) client;
    std::istringstream iss(str);
    int num;
    if (iss >> num)
        this->limit = num;
    else
        sendMessage(fd, "the limit must be a positive number\n");
}

void Channel::setOperator(Client client, int fd,std::string op)
{
    (void) client;
    int i = findClient2(chl_cls, op);
    if (i >= 0)
    {
        operatorss.push_back(chl_cls[i]);
        sendMessage(fd, "the channel " + name + " has an operator now who is " + op);
    }
    else
        sendMessage(fd, "the client is not a number of the channel\n");
}

void Channel::removeOperator(Client client, int fd, std::string op)
{
    (void) client;
    int i = findClient2(operatorss, op);
    if (i >= 0)
    {
        sendMessage(fd, "client just lost his  privilege\n");
        operatorss.erase (operatorss.begin() + i);
    }
    else
        sendMessage(fd, "client does not exist\n");
}

int Channel::findOperator(int fd)
{
    for(unsigned long i = 0; i < operatorss.size();  i++)
    {
        if(operatorss[i].getFd() == fd)
            return (1);
    }
    return (0);
}

std::map<std::string, int> Channel::getModes()
{
    return modes;
}

int Channel::findInvite(int fd)
{
    if (modes["i"])
    {  
        for(unsigned long i = 0; i < invetation.size();  i++)
        {
            if(invetation[i] == fd)
                return(1); 
        }
        return(0);
    }
    else
        return (1);
}

Channel::~Channel()
{
    
}

long findchannel(std::vector<Channel> channels, std::string name)
{
    for(unsigned long i = 0; i < channels.size();  i++)
    {
        if(channels[i].getName() == name)
            return(i);
    }
    return(-1);
}

long findClient2(std::vector<Client> chl_cls,std::string nickName)
{
    for(unsigned long i = 0; i < chl_cls.size();  i++)
    {
        if(chl_cls[i].getNickName().substr(0, chl_cls[i].getNickName().length() - 1) == nickName)
            return(i);
    }
    return(-1);
}

void sendMessage(int fd, std::string message)
{
    message = message + "\n";
    send(fd,message.c_str(),message.length(),0);
}


std::string intToString(int value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}
