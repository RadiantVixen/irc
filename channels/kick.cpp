/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 03:45:24 by aatki             #+#    #+#             */
/*   Updated: 2024/04/24 19:25:43 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channels.hpp"

void Channel::kick(Client client, std::string nickName, std::string reason)
{
    int i = findClient2(chl_cls,nickName);
    if (i >= 0)
    {
        cltNumbr --;
        
        sendMessage(client.getFd(), "KICK " + name + " " + rm(client.getNickName()) + " :" + reason + "\r\n");
        sendMessage(chl_cls[i].getFd(), "client has been kicked because of " + reason );
        chl_cls.erase (chl_cls.begin() + i);
    }
    else
        sendMessage(chl_cls[i].getFd(), "client does not exist\n");
}

void server::ft_kick(std::string buffer, Client client)
{
    std::string reason;
    std::string channelName;
    std::string nickName;

    (void) client;
    if (buffer.empty())
        return sendMessage(client.getFd(), "there is no arguments\n");
    std::size_t f1=buffer.find(' ');
    std::size_t f2=buffer.substr(f1 + 1, buffer.length()).find(' ');
    if (f1 == std::string::npos)
        return sendMessage(client.getFd(), "enter more argument\n");
    channelName = buffer.substr(0,f1);
    if (f2 != std::string::npos)
    {
        nickName = buffer.substr(f1 + 1, f2);
        reason = buffer.substr(f2 + 1, buffer.length());
    }
    else
    {
        nickName = buffer.substr(f1 + 1, buffer.length());
        reason = "nothing";
    }
    int i = findchannel(channels, channelName);
    if (i >= 0)
    {
        if (client.getFd() != channels[i].getClients()[0].getFd() && !channels[i].findOperator(client.getFd()))
            return sendMessage(client.getFd(), "the client most be an operator or the founder\n");
        channels[i].kick(client , nickName, reason);
    }
    else
        return sendMessage(client.getFd(), "the channel again\n");
}
