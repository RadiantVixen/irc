/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkouaz <kkouaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 01:05:50 by kkouaz            #+#    #+#             */
/*   Updated: 2024/03/30 03:37:47 by kkouaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"header.hpp"



int main(int ac, char **av)
{
    
    if(ac != 3)
    {
        std :: cout << "invalid args\n";
        return(1);
    }
    try
    {
        int port = checkPort(av[1]);
        std :: string password = av[2];
        server server(port, password);
        signal(SIGINT, server :: recieveSignal);
        signal(SIGQUIT, server :: recieveSignal);
        server.setup();
        server.start();
    }
    catch(std :: exception &e)
    {
        std :: cerr << e.what();
    }
   
}