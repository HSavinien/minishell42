/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:31:57 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/04 16:30:06 by tmongell         ###   ########.fr       */
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
# include <limits.h>

# include "library/libft/libft.h"
# include "library/get_next_line/get_next_line.h"

//macros==================================================================macros

# define PS1 "minishell :> "
# define PS2 ">"

//struct==================================================================struct

//typedef
typedef int (*builtins_func) (int argc, char **argv);
typedef int	t_pipe_array[(OPEN_MAX + 1) /2][2];

//struct
typedef struct s_lst_token {
	char				*content;
	int					index;
	struct	s_lst_token	*next;
}	t_lst_token;

typedef struct s_fd_redir {
	int	in;
	int	out;
	int	base_stdin;
	int	base_stdout;
}	t_fd_redir;

typedef struct s_global_var {
	char			**env;
	int				ret;
}	t_global_var;


typedef struct s_dico {
	char			*key;
	builtins_func	fct;
}	t_dico;

//globales==============================================================globales

t_global_var	g_varvalues;

//prototypes==========================================================prototypes

//reading and history
//static void	add_logfile(char *line);


//lexer-parser
int			parser_chevron(t_lst_token *token, t_fd_redir *fds);
char		*expand_vars(char *src);
t_lst_token	*lexing(char *line);
int			lexer_checkcase(char *line);
char		*trim_token(char *src);
int			parser_entry(t_lst_token *tokens, t_fd_redir *fds);
void		ft_heredoc(char *limit);
void		do_pipe (t_lst_token *cmd, int nb_pipe, t_fd_redir *fds);
void		dup_pipe(int num_cmd, int nb_pipe, t_pipe_array pipes);
void		close_unused_pipe(int num_cmd, int nb_pipe, t_pipe_array pipes);
void		close_all_except(t_pipe_array pipes, int except1, int except2);

//execution
int	exec_cmd(char	*cmd, char **args, char **env);

//signals


//utils
char	**ft_construct(t_lst_token *token);
void	ft_break(t_lst_token *start, t_lst_token **actual);
void	ft_skip(t_lst_token **tmp, int skip);//not used anymore
void	do_redirect_chevron(char *chevron, char *file, t_fd_redir *fds);
void	check_forbidden_ends(t_lst_token *token);
int		is_chevron(char *str);

//error management
void	open_error(char *file);
void	tech_error(char *msg);
int		max_var_len(char **env);


//debug
void	 error(char	*msg);
int		execcmd(char **args);
void	destroy_lst(t_lst_token *lst);
void	display_lst(t_lst_token	*lst);



//builtins
int		ft_pwd(int argc, char **argv);
int		ft_env(int argc, char **argv);
int		ft_exit(int argc, char **argv);


#endif
