# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/28 11:03:55 by cmaroude          #+#    #+#              #
#    Updated: 2022/07/08 13:40:54 by cmaroude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	ft_main.c

OBJ = $(SRC:.c=.o)

INCLUDE = ft_minishell.h

LIBFT = libft
RM = rm -rf
AR = ar rc
GCC = gcc -Wall -Werror -Wextra

all: $(NAME)

%.o : %.c
	$(GCC) -c $(SRC)

$(NAME): $(OBJ) $(INCLUDE)
	make -C $(LIBFT) bonus
	$(GCC) $(OBJ) $(LIBFT)/libft.a -o $(NAME)

clean:
	make -C libft clean
	$(RM) $(OBJ)

fclean: clean
	$(RM) libft/libft.a
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
