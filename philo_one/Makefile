# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/06 10:47:13 by esnowbal          #+#    #+#              #
#    Updated: 2021/01/29 14:48:35 by esnowbal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo_one

SRC= notlibft.c main.c

HEADERS= philo.h

all: $(NAME)

$(NAME): $(SRC) $(HEADERS)
		gcc -Wall -Wextra -Werror $(SRC) -o $(NAME)

clean:
		rm -rf $(NAME)

fclean: clean

re: fclean all

norm:
		norminette *.c *.h