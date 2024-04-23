/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 03:45:24 by aatki             #+#    #+#             */
/*   Updated: 2024/04/21 18:25:58 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channels.hpp"

void Channel::kick(std::string nickName, std::string reason)
{
    int i = findClient2(chl_cls,nickName);
    if (i >= 0)
    {
        sendMessage(chl_cls[i].getFd(), "client has been kicked because of " + reason);
        chl_cls.erase (chl_cls.begin() + i);
    }
    else
        sendMessage(chl_cls[i].getFd(), "client does not exist\n");
}

void server::ft_kick(std::string buffer, Client client)
{
    (void) client;
    if (buffer.empty())
        return sendMessage(client.getFd(), "there is no arguments\n");
    std::size_t f1=buffer.find(' ');
    std::size_t f2=buffer.substr(f1 + 1, buffer.length()).find(' ');
    if (f1 == std::string::npos || f2 == std::string::npos)
        return sendMessage(client.getFd(), "the channel/client name incorrect\n");
    std::string channelName = buffer.substr(0,f1);
    std::string nickName = buffer.substr(f1 + 1, f2);
    std::string reason = buffer.substr(f2 + 1, buffer.length());
    int i = findchannel(channels, channelName);
    if (i >= 0)
        channels[i].kick(nickName, reason);
    else
        return sendMessage(client.getFd(), "the channel again\n");
}
