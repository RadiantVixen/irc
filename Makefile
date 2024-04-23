# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aatki <aatki@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/16 16:27:13 by kkouaz            #+#    #+#              #
#    Updated: 2024/04/21 17:00:09 by aatki            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CXX = c++
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror #-fsanitize=address -g3 
RM = rm -rf

SRC1 =  channels.cpp mainFile.cpp join.cpp kick.cpp invite.cpp prvimsg.cpp modes.cpp topic.cpp part.cpp

SRC2 =  utils.cpp client.cpp server.cpp

CHANNELS	= 	$(addprefix channels/,$(SRC1)) 
SERVER	= 	$(addprefix server/,$(SRC2)) main.cpp

OBJ = $(CHANNELS:.cpp=.o) $(SERVER:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CXX) $(CXXFLAGS) $(CHANNELS) $(SERVER) -o $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all
