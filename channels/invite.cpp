/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 07:11:33 by aatki             #+#    #+#             */
/*   Updated: 2024/04/24 19:23:34 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channels.hpp"

void Channel::invite(Client client, int fd, std::string message)
{
    (void) client;
    // std::cout<<"the client "<<fd<<" have recieved an invetation from the channel"<<name<<std::endl;
    // std::cout<<message<<std::endl;
    ///
    sendMessage(client.getFd(), "INVITE " + rm (client.getNickName())+ " " + name + "\r\n");
    send(fd, message.c_str(), message.length(),0);
    invetation.push_back(fd);
}

void server::ft_invite(std::string buffer, Client client)
{
    if (buffer.empty())
        return sendMessage(client.getFd(), "there is no arguments \n");
    std::size_t f1 = buffer.find(' ');
    if (f1 != std::string::npos)
    {
        std::string clientName = buffer.substr(0, f1);
        std::string chan = buffer.substr(f1 + 2, buffer.length());
        int i = findchannel(channels,chan);
        int j = findClient2 (clients, clientName);
        if (i >= 0 && j >= 0)
        {
            if (client.getFd() != channels[i].getClients()[0].getFd() && !channels[i].findOperator(client.getFd()))
                return sendMessage(client.getFd(), "the client most be an operator or the founder\n");
            std::string message = "you just recived an invetation to join this channel " + chan;
            channels[i].invite(client, clients[j].getFd(),message);
        }
        else
            return sendMessage(client.getFd(), "the channel/client name that's not exist\n");
    }
    else
        return sendMessage(client.getFd(), "not enough arguments\n");
}
