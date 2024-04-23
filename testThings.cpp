/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testThings.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 03:56:47 by aatki             #+#    #+#             */
/*   Updated: 2024/04/04 05:29:43 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

void function()
{   
    std::cout<<name<<std::endl;
}

class test 
{
    private :
        std::string name ;
    public :
        test(std::string name)
        {
            this-> name = name;
        }
        void    member();
        // {
        //         function();
        // };
};

void test::member()
{
} 

int main()
{
    test j("jj");
    j.member();
}