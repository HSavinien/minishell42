/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:31:57 by cmaroude          #+#    #+#             */
/*   Updated: 2022/07/20 15:10:51 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# ifndef BIN_DIR
#  define BIN_DIR "./minishell/bin"
# endif

//includes==============================================================includes

# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "library/libft/libft.h"
# include "library/get_next_line/get_next_line.h"


//struct==================================================================struct

typedef struct s_lst_token {
	char				*content;
	int					index;
	struct	s_lst_token	*next;
}	t_lst_token;

//prototypes==========================================================prototypes

//reading and history


//lexer-parser
void	ft_parser(t_lst_token **token);
char	*expand_vars(char *src, char **env);

//execution


//signals


//utils

#endif
