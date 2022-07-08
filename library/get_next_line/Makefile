SRCS	=	get_next_line_utils.c \
			get_next_line.c \

B_SRCS	=	get_next_line_bonus.c \
			get_next_line_utils.c \

OBJS	= ${SRCS:.c=.o}

B_OBJS	= ${B_SRCS:.c=.o}

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

NAME	= get_next_line.a

#rules    -------------------------------------------------------------    rules

all:	${NAME}

${NAME}:	${OBJS}
		ar -rcs ${NAME} ${OBJS}
		ranlib ${NAME}

bonus:	${B_OBJS}
		ar -rcs ${NAME} ${B_OBJS}
		ranlib ${NAME}

clean:
		rm -f ${OBJS}
		rm -f ${B_OBJS}

fclean:	clean
		rm -f ${NAME}

re:		fclean all

.PHONY:	all clean fclean re
