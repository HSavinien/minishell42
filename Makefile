# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/28 11:03:55 by cmaroude          #+#    #+#              #
#    Updated: 2022/07/20 20:12:46 by tmongell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	main.c \
		srcs/var_expander.c \
		srcs/lexer.c \
		srcs/lexer_cases.c \


OBJ = ${SRC:.c=.o}

INCLUDE = minishell.h

LIBFT = library/libft

GNL = library/get_next_line

RM = rm -rf

CC = gcc 

CFLAGS = -Wall -Werror -Wextra

DIR		:= "\"$(shell pwd)/bin\""

#rules====================================================================rules#

all: ${NAME}

library:	libft	gnl

libft:
	@make -sC ${LIBFT}
	@echo "libft compiled"

gnl:
	@make -sC ${GNL}
	@echo "gnl compiled"

$(NAME): ${OBJ} ${INCLUDE}
	@make library
	@${CC} ${CFLAGS} ${OBJ} -D BIN_DIR=${DIR} ${LIBFT}/libft.a ${GNL}/get_next_line.a -o ${NAME} -lreadline
	@echo "project compiled"

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
