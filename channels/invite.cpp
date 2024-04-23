/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 07:11:33 by aatki             #+#    #+#             */
/*   Updated: 2024/04/20 20:41:21 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channels.hpp"

void Channel::invite(int fd, std::string message)
{
    // std::cout<<"the client "<<fd<<" have recieved an invetation from the channel"<<name<<std::endl;
    // std::cout<<message<<std::endl;
    send(fd, message.c_str(), message.length(),0);
    invetation.push_back(fd);
}

void server::ft_invite(std::string buffer, Client client)
{
    if (buffer.empty())
        return sendMessage(client.getFd(), "there is no arguments");
    std::size_t f1 = buffer.find(' ');
    if (f1 != std::string::npos)
    {
        std::string clientName = buffer.substr(0, f1);
        std::string chan = buffer.substr(f1 + 2, buffer.length());
        int i = findchannel(channels,chan);
        int j = findClient2 (clients, clientName);
        std::cout<<clientName<<chan<<i<<j<<std::endl;
        if (i >= 0 && j >= 0)
        {
            std::string message = "you just recived an invetation to join this channel " + chan;
            channels[i].invite(clients[j].getFd(),message);
        }
        return sendMessage(client.getFd(), "the channel/client name that's not exist\n");
    }
    else
        return sendMessage(client.getFd(), "not enough arguments\n");
}
