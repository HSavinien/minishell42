/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:31:57 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/15 19:53:26 by tmongell         ###   ########.fr       */
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
# include <sys/errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <limits.h>
# include <termios.h>

# include "library/libft/libft.h"
# include "library/get_next_line/get_next_line.h"

//macros==================================================================macros

# define PS1 "[2;4;32mminishell[0;2;5;32m>> [0m"
# define PS2 "[2;32m> [2;4;32m"

//struct==================================================================struct

//typedef
typedef int		(*t_builtins_func) (int argc, char **argv);
typedef int		t_pipe_array[(OPEN_MAX + 1) / 2][2];//pas a la norme

//struct
typedef struct s_lst_token {
	char				*content;
	int					index;
	struct s_lst_token	*next;
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
	t_builtins_func	fct;
}	t_dico;

//globales==============================================================globales

t_global_var	g_varvalues;

//prototypes==========================================================prototypes

//initialisation
t_fd_redir	*init_fd(void);
void		init_global(char **env);

//expander
char		*expand_vars(char *src);
int			expand_ret_value(char *dst);
int			max_var_len(char **env);

//lexer
t_lst_token	*lexing(char *line);
int			lexer_checkcase(char *line);
void		*lexer_error(char *line, t_lst_token *lst);

//parser
int			parser_entry(t_lst_token *tokens, t_fd_redir *fds);
char		*trim_token(char *src);
int			check_forbidden_ends(t_lst_token *token);
char		**ft_construct(t_lst_token *token);

//chevrons
int			parser_chevron(t_lst_token *token, t_fd_redir *fds);
int			do_redirect_chevron(char *chevron, char *file, t_fd_redir *fds);
void		ft_heredoc(char *stop, t_fd_redir *fds);
int			is_chevron(char *str);

//pipes
void		do_pipe(t_lst_token *cmd, int nb_pipe, t_fd_redir *fds);
void		dup_pipe(int num_cmd, int nb_pipe, t_pipe_array pipes);
void		close_unused_pipe(int num_cmd, int nb_pipe, t_pipe_array pipes);
void		close_all_except(t_pipe_array pipes, int except1, int except2);
void		wait_all_pipes(int *pid, int num_cmd);
void		close_two(int fd1, int fd2);

//execution
int			exec_cmd(char	*cmd, char **args, char **env);
int			try_builtins(char **std_args);

//signals
void		init_signal(struct termios *read_prompt, struct termios *exec);

//utils
void		*destroy_lst(t_lst_token *lst);
void		display_lst(t_lst_token	*lst);
int			destroy_array(char **array);

//error management
int			open_error(char *file, int err);
int			tech_error(char *msg, int err);
int			error(char *msg, int err, t_lst_token *freeable_lst);

//builtins
int			ft_pwd(int argc, char **argv);
int			ft_env(int argc, char **argv);
int			ft_exit(int argc, char **argv);
int			ft_unset(int argc, char **argv);
int			ft_cd(int argc, char **argv);
int			ft_export(int argc, char **argv);
int			ft_echo(int argc, char **argv);

//builtins utils
int			ft_find_index(char **env, char *env_srch, int len);
int			ft_str_is_valid(char *str);
char		**ft_realloc_char(char **ptr, int len, int hidden, char *str);
void		ft_add_env(char *str, int hidden);
void		ft_exchange_env(int index, char *argv);
void		ft_remove_element(int *index);

//aditional functionality===============================additional functionality

//history
int			load_logfile(char *logfile);
void		add_logfile(char *line);

//script
int			exec_script(char *script, struct termios exec, t_fd_redir *fds);
void		use_line(char *line, t_fd_redir *fds);
void		load_conf(char *conf_file, struct termios exec, t_fd_redir *fds);
#endif
