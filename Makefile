# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/28 11:03:55 by cmaroude          #+#    #+#              #
#    Updated: 2022/08/08 17:10:45 by tmongell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	minishell.c \
		filler_function.c \
		srcs/var_expander.c \
		srcs/expander_utils.c \
		srcs/lexer.c \
		srcs/lexer_cases.c \
		srcs/parser.c \
		srcs/parser_utils.c \
		srcs/parser_chevron.c \
		srcs/heredoc.c \
		srcs/pipe.c \
		srcs/pipe_utils.c \
		srcs/error.c \
		srcs/exec_cmd.c \
		srcs/lst_utils.c \
		builtins/pwd.c \
		builtins/env.c \
		builtins/exit.c \
		builtins/unset.c \


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

sanitize: library
	@${CC} ${SRC} ${LIBFT}/libft.a -lreadline ${GNL}/get_next_line.a -o ${NAME}_sani -g -fsanitize=address

debug: library
	@${CC} ${SRC} ${LIBFT}/libft.a -lreadline ${GNL}/get_next_line.a -o ${NAME}_debug -g

.PHONY: all clean fclean re
