# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/28 11:03:55 by cmaroude          #+#    #+#              #
#    Updated: 2022/07/28 15:00:33 by tmongell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	minishell.c \
		srcs/var_expander.c \
		srcs/expander_utils.c \
		srcs/lexer.c \
		srcs/lexer_cases.c \
		srcs/parser.c \
		srcs/parser_utils.c \
		srcs/parser_chevron.c \
		filler_function.c \
		srcs/error.c \
		srcs/exec_cmd.c \
		srcs/lst_utils.c \
#		srcs/logfile.c \


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
