# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/29 19:36:37 by user              #+#    #+#              #
#    Updated: 2025/07/29 22:54:40 by amsbai           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=address -fsanitize=undefined
SRC = philo.c routine.c parsing.c utils/ft_atoi.c utils/helpers.c utils/valid_nbr.c
OBJ = $(SRC:.c=.o)
HEADER = philo.h

all: $(NAME)
$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

.c.o: $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
