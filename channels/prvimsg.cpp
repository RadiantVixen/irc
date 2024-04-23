/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prvimsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkouaz <kkouaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 02:23:54 by aatki             #+#    #+#             */
/*   Updated: 2024/04/21 22:39:23 by kkouaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channels.hpp"

void server::ft_privmsg(std::string buffer, Client client)
{
    if (buffer.empty())
        return sendMessage(client.getFd(), "there is no arguments\n");
    std::size_t f1 = buffer.find(' ');
    std::string message = buffer.substr(f1 + 1,buffer.length());
    if (f1 == std::string::npos)
        return sendMessage(client.getFd(), "where is the message\n");
    if (buffer[0] == '#')
    {
        int k = findchannel(channels, buffer.substr(1, f1 - 1));
        if (k >= 0)
        {
            if (findClients(channels[k].getClients(), client.getFd()) >= 0)
            {
                for (size_t i = 0; i < channels[k].getClients().size() ; i++)
                    send(channels[k].getClients()[i].getFd(),message.c_str(), message.length() - 1, 0);
            }
            else
                return sendMessage(client.getFd(), "the client does not exist in the channel");
        }
        else
            return sendMessage(client.getFd(), "the channel name is incorrect");
    }
    else
    {
        int k = findClient2(clients, buffer.substr(0, f1));
        if (k >= 0)
            send(clients[k].getFd(), message.c_str(), message.length(), 0);
        else
            return sendMessage(client.getFd(), "the nick name of the client you provide that's not exist");
    }
}
