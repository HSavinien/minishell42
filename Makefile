# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/10 17:38:52 by cmaroude          #+#    #+#              #
#    Updated: 2022/08/16 17:54:53 by tmongell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	minishell.c \
		init.c \
		additional_functions/script.c \
		additional_functions/log.c \
		srcs/chevron_utils.c \
		srcs/dico_builtins.c \
		srcs/error.c \
		srcs/exec_cmd.c \
		srcs/general_utils.c \
		srcs/heredoc.c \
		srcs/lexer.c \
		srcs/lexer_utils.c \
		srcs/parser.c \
		srcs/parser_chevron.c \
		srcs/pipe.c \
		srcs/pipe_utils.c \
		srcs/sig_handling.c \
		srcs/token_trimer.c \
		srcs/var_expander.c \
		srcs/var_expander_utils.c \
		builtins/cd.c \
		builtins/pwd.c \
		builtins/env.c \
		builtins/exit.c \
		builtins/echo.c \
		builtins/unset.c \
		builtins/export.c \
		builtins/builtins_utils.c \
		builtins/builtins_utils_env.c \

OBJ = ${SRC:.c=.o}

HISTORY_PATH = '"$(HOME)/.minishell_history"'

CONF_PATH = '"$(HOME)/.minishellrc"'

INCLUDE = minishell.h

LIBFT = library/libft

GNL = library/get_next_line

READLINE = library/readline

RM = rm -rf

CC = gcc 

CFLAGS = -Wall -Werror -Wextra -D HISTORY=${HISTORY_PATH} -D CONF_FILE=${CONF_PATH}

COMPILEFLAGS = ${LIBFT}/libft.a ${GNL}/get_next_line.a -L${READLINE}/lib -lreadline


#rules====================================================================rules#

all: library ${NAME}

stuff :
	echo ${HISTORY}

library:	libft	gnl    readline

${READLINE}:
	@sh ./install_readline.sh
	@echo "readline downloaded" 

readline: ${READLINE}

libft: ${LIBFT}/libft.a

${LIBFT}/libft.a:
	@make -sC ${LIBFT}
	@echo "libft compiled"

gnl: ${GNL}/get_next_line.a

${GNL}/get_next_line.a:
	@make -sC ${GNL}
	@echo "gnl compiled"

%.o: %.c ${INCLUDE}
	${CC} ${CFLAGS} -I${READLINE}/include -c $< -o $@

${NAME}: library ${OBJ} ${INCLUDE}
	${CC} ${CFLAGS} ${OBJ} ${COMPILEFLAGS} -o ${NAME}
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
	@${RM} ${NAME}_debug
	@${RM} ${NAME}_sanitize
	@${RM} ${NAME}.dSYM
	@${RM} ${NAME}_debug.dSYM
	@${RM} ${NAME}_sanitize.dSYM
	@echo "executable removed"

re: fclean all

sanitize: library
	${CC} ${SRC} -I${READLINE}/include ${COMPILEFLAGS} -o ${NAME}_sanitize -g -fsanitize=address

debug: library
	${CC} ${SRC} -I${READLINE}/include ${COMPILEFLAGS} -o ${NAME}_debug -g

.PHONY: all clean fclean re
