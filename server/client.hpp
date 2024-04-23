/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkouaz <kkouaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:27:15 by kkouaz            #+#    #+#             */
/*   Updated: 2024/04/22 04:11:49 by kkouaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#   include <iostream>
#   include <netinet/in.h>
#   include <sys/socket.h>

class Client
{
    private:
        int _fd;
        std :: string ipAddress;
        std :: string _nickname;
        std :: string _user;
        std :: string _hostname;
        std :: string _servername;
        std :: string _realname;

        bool registred;
        bool hasNickName;
        bool hasUserName;
    public:
        Client();

        //getters
        int getFd();
        std :: string getIpAddress();
        std :: string getNickName();
        std :: string getUser();
        std :: string getHostname();
        std :: string getServername();
        std :: string getRealname();

        bool isRegistred();
        bool hasNick();
        bool hasUser();

        //setters
        void setNickName(std :: string nickname);
        void setUser(std :: string user);
        void setFd(int fd);
        void setIpAdress(std :: string addr);
        void beRegistred();
        void setHostname(std :: string hostname);
        void setServername(std :: string servername);
        void setRealname(std :: string realname);


        ~Client();
} ;



#   endif