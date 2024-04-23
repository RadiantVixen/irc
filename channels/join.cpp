/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 03:43:20 by aatki             #+#    #+#             */
/*   Updated: 2024/04/20 22:42:16 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channels.hpp"


void Channel::join(Client client, std::string strkey)
{
    std::string message;

    if (!findInvite(client.getFd()))
    {
        sendMessage(client.getFd(),"Cannot join channel (+i)");
        return ;
    }
    if (modes["l"] && cltNumbr >= limit)
    {
        sendMessage(client.getFd(),"Cannot join channel (+l)");
        return ;
    }
    if(modes["k"] && strkey != key)
    {
        sendMessage(client.getFd(),"Cannot join channel (+k)");
        return ;
    }
    chl_cls.push_back(client);
    cltNumbr ++;
    message += client.getNickName() + " has joined " +name + "\n";
    message += "Welcome to " +name + " " + client.getNickName() + "\n";
    message += "Topic for " +name + " is " + topic + "\n";
    message += "There are " +  intToString(cltNumbr) + " users on this channel\n";
    for (size_t i = 0; i < chl_cls.size() ; i++)
        sendMessage(chl_cls[i].getFd(), message);
}

void server::ft_join(std::string buffer, Client client)
{
    if (buffer.empty())
        return sendMessage(client.getFd(), "there is no arguments\n");
    std::size_t found=buffer.find(' ');
    std::string strKey;
    if (found != std::string::npos)
    {
        strKey = buffer.substr(found + 1, buffer.length() - found);
        buffer = buffer.substr(0, found);
        std::size_t f2 = buffer.find(' ');
        if (f2 != std::string::npos)
            return sendMessage (client.getFd(), "too much argument\n");
    }
    int i = findchannel(channels,buffer);
    if (i >= 0)
        channels[i].join(client,strKey);
    else
    {
        // std::cout<<">>"<<buffer<<"<<>>"<<buffer<<"<<"<<std::endl;
        Channel newc(buffer);
        newc.join(client,strKey);
        channels.push_back(newc);
    }
}
