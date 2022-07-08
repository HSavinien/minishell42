# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/28 11:03:55 by cmaroude          #+#    #+#              #
#    Updated: 2022/07/08 15:40:20 by tmongell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	main.c

OBJ = ${SRC:.c=.o}

INCLUDE = minishell.h

LIBFT = library/libft

GNL = library/get_next_line

RM = rm -rf

GCC = gcc -Wall -Werror -Wextra

#rules====================================================================rules#

all: ${NAME}

%.o : %.c
	${GCC} -c ${SRC}

library:	libft	gnl

libft:
	@make -sC ${LIBFT}
	@echo "libft compiled"

gnl:
	@make -sC ${GNL}
	@echo "gnl compiled"

$(NAME): ${OBJ} ${INCLUDE}
	@make library
	@${GCC} ${OBJ} ${LIBFT}/libft.a ${GNL}/get_next_line.a -o ${NAME}
	@echo "\e[1,32mproject compiled\e[0m"

clean:
	@make -sC ${LIBFT} clean
	@make -sC ${GNL} clean
	@${RM} ${OBJ}
	@echo "project cleaned"

fclean: clean
	@make -sC ${LIBFT} fclean
	@make -sC ${GNL} fclean
	@${RM} ${NAME}
	@${RM} ${NAME}.dSYM
	@echo "executable removed"

re: fclean all

debug: library
	@${GCC} ${OBJ} ${LIBFT}/libft.a ${GNL}/get_next_line.a -o ${NAME} -g -fsanitize=address

.PHONY: all clean fclean re
