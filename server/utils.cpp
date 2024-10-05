/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkouaz <kkouaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 01:37:49 by kkouaz            #+#    #+#             */
/*   Updated: 2024/04/22 16:33:14 by kkouaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"header.hpp"

int checkPort(std :: string av)
{
    int port;
    for(unsigned long i = 0; i< av.size(); i++)
    {
        if(!isdigit(av[i]))
            throw std::runtime_error("Invalid port number");
            
    }
    port = atoi(av.c_str());
    if(port <= 0 || port > 65535)
        throw std::runtime_error("Invalid port number");
    return(port);
}


std :: string rm(std :: string str)
{
    std :: string result;

    for (unsigned long  i = 0; i < str.size(); i++)
    {
        if(str[i] != '\r' && str[i] != '\n')
            result.push_back(str[i]);
    }
    return(result);
}

std :: string rn(std :: string str)
{
    std :: string result;

    for (unsigned long  i = 0; i < str.size(); i++)
    {
        if( str[i] != '\n')
            result.push_back(str[i]);
    }
    return(result);
}