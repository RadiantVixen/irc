/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 04:01:57 by aatki             #+#    #+#             */
/*   Updated: 2024/04/24 19:24:00 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channels.hpp"

void Channel::part(Client client, int fd,int i, std::string reason)
{
    (void) client;
    if (i >= 0)
    {
        ///
        sendMessage(client.getFd(), rm(client.getNickName())+"!"+client.getFirst()+"@localhost PART " + name + "\r\n");
        sendMessage(fd, "client is out because of " + reason);
        sendMessage(i, "you are out cuz " + reason);
        chl_cls.erase (chl_cls.begin() + i);
    }
    else
        sendMessage(fd, "client does not exist\n");
}

void server::ft_part(std::string buffer, Client client)
{
    if (buffer.empty())
        return sendMessage(client.getFd(), "there is no arguments\n");
    std::size_t f1 = buffer.find(' ');
    if (f1 == std::string::npos)
        return sendMessage(client.getFd(), "the channel name incorrect\n");
    std::string channelName = buffer.substr(0,f1);
    std::string reason = buffer.substr(f1 + 1, buffer.length());
    int i = findchannel(channels, channelName);
    if (i >= 0)
    {
        int j = findClients(channels[i].getClients(), client.getFd());
        channels[i].part(client, client.getFd(),j, reason); 
    }
    else
        return sendMessage(client.getFd(), "the channel again\n");
}
