/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:08:26 by aatki             #+#    #+#             */
/*   Updated: 2024/04/24 15:19:10 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channels.hpp"

void Channel::addMode(Client client, std::string mode)
{
    (void) client;
    for (size_t i = 0; i < chl_cls.size() ; i++)
        sendMessage(chl_cls[i].getFd(), "the mode now is + " + mode +"\n");
    modes[mode] = 1;
}

void Channel::removeMode(Client client, std::string mode)
{
    (void) client;
    ///
    // sendMessage(client.getFd(), "KICK " + name + " " + client.getNickName() + " :" + reason + "\r\n");
    for (size_t i = 0; i < chl_cls.size() ; i++)
        sendMessage(chl_cls[i].getFd(), "the mode now is - " + mode +"\n");
    modes[mode] = 0;
}

void server::ft_mode(std::string buffer, Client client)
{
    if (buffer.empty())
        return sendMessage(client.getFd(), "there is no arguments\n");
    std::size_t f1 = buffer.find(' ');
    std::size_t f2 = buffer.substr(f1 + 1,buffer.length()).find(' ');
    // std::size_t f3 = buffer.substr(f2,buffer.length()).find(' ');
    int i = -1;
    std::string mode;
    if (f1 != std::string::npos)
    {
        std::string name = buffer.substr(0, f1);
        i = findchannel(channels,name);
        if (f2 != std::string::npos)
            mode = buffer.substr(f1 + 1, f2);
        else
            mode = buffer.substr(f1 + 1, buffer.length() - f1);
    }
    if (i < 0 ||  mode.length() != 2 || (mode[0] != '+' && mode[0] != '-'))
        return sendMessage(client.getFd(), "the channel/mode name incorrect\n");
    if (client.getFd() != channels[i].getClients()[0].getFd() && !channels[i].findOperator(client.getFd()))
        return sendMessage(client.getFd(), "the client most be an operator or the founder\n");
    if (f2 == std::string::npos && (mode == "+i" || mode == "-i" || mode == "+t" || mode == "-t" || mode == "-l" || mode == "-k"))
    {
        if(mode[0] == '+')
            channels[i].addMode(client, mode.substr(1,1));
        if(mode[0] == '-')
            channels[i].removeMode(client, mode.substr(1,1));
    }
    else if (f2 != std::string::npos && (mode == "+k"  || mode == "+o" || mode == "-o" || mode == "+l"))
    {
        std::string rest = buffer.substr(f1 + f2 + 2, buffer.length());
        if(mode[0] == '+')
            channels[i].addMode(client, mode.substr(1,1));
        if(mode[0] == '-')
            channels[i].removeMode(client, mode.substr(1,1));
        if (mode == "+k")
            channels[i].setKey(client, rest);
        if (mode == "+l")
            channels[i].setLimit(client, client.getFd(), rest);
        if (mode == "+o")
            channels[i].setOperator(client, client.getFd(), rest);
        if (mode == "-o")
            channels[i].removeOperator(client, client.getFd(), rest);
    }
    else
        return sendMessage(client.getFd(), "there are some errors\n");
}
