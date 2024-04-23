/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkouaz <kkouaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:20:23 by kkouaz            #+#    #+#             */
/*   Updated: 2024/04/22 04:13:33 by kkouaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"client.hpp"

Client :: Client()
{
    _fd = -1;
    registred = false;
    hasNickName = false;
    hasUserName = false;

}

//getters

std :: string  Client :: getHostname()
{
    return(_hostname);
}
std :: string  Client :: getServername()
{
    return(_servername);
}
std :: string  Client :: getRealname()
{
    return(_realname);
}

int Client :: getFd()
{
    return(_fd);
}

std :: string Client :: getIpAddress()
{
    return(ipAddress);
}

std :: string Client :: getNickName()
{
    return(_nickname);
}

std :: string Client :: getUser()
{
    return(_user);
}

bool Client :: isRegistred()
{
    return(registred);
}

bool Client :: hasNick()
{
    return(hasNickName);
}

bool Client :: hasUser()
{
    return(hasUserName);
}
// setters


void Client :: setNickName(std :: string nickname)
{
    _nickname = nickname;
    hasNickName = true;
}

void Client :: setUser(std :: string user)
{
    _user = user;
    hasUserName = true;
}
void Client :: setFd(int fd)
{
    _fd = fd;
}

void Client :: setIpAdress(std :: string addr)
{
    ipAddress = addr;
}

void Client :: beRegistred()
{
    registred = true;
}

void Client :: setHostname(std :: string hostname)
{
    _hostname= hostname;
}

void Client :: setServername(std :: string servername)
{
    _servername = servername;
}

void Client :: setRealname(std :: string realname)
{
    _realname = realname;
}

Client :: ~Client()
{
}