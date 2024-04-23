/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 03:42:49 by aatki             #+#    #+#             */
/*   Updated: 2024/04/21 04:08:14 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channels.hpp"
#include <sstream>
#include <string>
#include <sys/socket.h>

void server::douzi_3andi_a_zine(std::string buffer, Client client)
{
    std::cout<<buffer;
    buffer = buffer.substr(0, buffer.length() - 1);
    try
    {
        if (buffer.substr (0,7) == "/JOIN #")
            ft_join(buffer.substr(7, buffer.length()), client);
        else if (buffer.substr (0,7) == "/KICK #")
            ft_kick(buffer.substr(7, buffer.length()), client);
        else if (buffer.substr (0,9) == "/PRIVMSG ")
            ft_privmsg(buffer.substr(9, buffer.length()), client);
        else if (buffer.substr (0,7)  == "/MODE #")
            ft_mode(buffer.substr(7, buffer.length()), client);
        else if (buffer.substr (0,8) == "/TOPIC #")
            ft_topic(buffer.substr(8, buffer.length()), client);
        else if (buffer.substr (0,8) == "/INVITE ")
            ft_invite(buffer.substr(8, buffer.length()), client);
        else if (buffer.substr (0,7) == "/PART #")
            ft_part(buffer.substr(7, buffer.length()), client);
        else
            for (size_t i = 0; i < channels.size() ; i++)
                for (size_t j = 0; j < channels[i].getClients().size() ; j++)
                    sendMessage(channels[i].getClients()[j].getFd(), channels[i].getClients()[j].getNickName() + "send : " + buffer + "\n");
    }
    catch (std::exception &e)
    {
        std::cout<<e.what()<<std::endl;
    }
}
