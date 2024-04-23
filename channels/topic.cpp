/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkouaz <kkouaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:21:23 by aatki             #+#    #+#             */
/*   Updated: 2024/04/22 00:29:55 by kkouaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channels.hpp"

void Channel::ftopic(std::string topic)
{
    std::cout<<"topic has been changed"<<std::endl;
    this->topic = topic;
    std::string message = "the new topic is " + topic + "\n";
    for (size_t i = 0; i < chl_cls.size(); i++)
        send (chl_cls[i].getFd() , message.c_str(), message.length(), 0);
}

void server::ft_topic(std::string buffer, Client client)
{
    if (buffer.empty())
        return sendMessage(client.getFd(), "there is no arguments");
    std::size_t f1=buffer.find(' ');
    std::string chan;
    if (f1 != std::string::npos)
        chan = buffer.substr(0, f1);
    else
        chan = buffer;
    int i = findchannel(channels,chan);
    if (i >= 0)
    {
        if (f1 == std::string::npos)
            std::cout<<channels[i].getTopic()<<std::endl;
        else
        {
            if (client.getFd() == channels[i].getClients()[0].getFd() || !channels[i].getModes()["t"] || (channels[i].getModes()["t"] && channels[i].findOperator(client.getFd())))
            {
                std::string strTopic = buffer.substr(f1, buffer.length() - f1);
                channels[i].ftopic(strTopic);
            }
            else
                return sendMessage(client.getFd(), "the client most be an operator\n");
        }
    }
    else
        return sendMessage(client.getFd(), "the channel name that's not exist\n");
}
