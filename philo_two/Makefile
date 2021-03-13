# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/06 10:47:13 by esnowbal          #+#    #+#              #
#    Updated: 2021/03/13 14:58:07 by esnowbal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo_two

SRC= notlibft.c activity.c init.c get_time.c main.c

HEADERS= philo.h

all: $(NAME)

$(NAME): $(SRC) $(HEADERS)
		clang -Wall -Wextra -Werror -pthread $(SRC) -o $(NAME)

clean:
		rm -rf $(NAME)

fclean: clean

re: fclean all

norm:
		norminette *.c *.h
