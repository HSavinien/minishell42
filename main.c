/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:35:09 by tmongell          #+#    #+#             */
/*   Updated: 2022/07/28 14:50:38 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	segfault(int sig)
{
	if (sig)
	printf("segfault caught\n");
}


/* test expander
int	main(int ac, char **av, char **env)
{
	char *line;
	(void) av[ac];
	char	*end_line;
	while (42)
	{
		line = readline("input : ");
		if (line[0])
			add_history(line);
		end_line = expand_vars(line, env);
		printf("result : %s\n", end_line);
		free(end_line);
	}
}
*/
/*
// test lexer + expander
int	main(int ac, char **av, char **env)
{
	char *line;
	(void) av[ac];
	t_lst_token	*end_line;
	while (42)
	{
		line = readline("input : ");
		if (line[0])
			add_history(line);
		end_line = lexing(line, env);
		display_lst(end_line);
		destroy_lst(end_line);
	}
}
*/

t_fd_redir	*init_fds(void)
{
	t_fd_redir *new;

	new = malloc(sizeof (t_fd_redir));

	new->in = -1;
	new->out = -1;

	new->base_stdin = dup(0);
	new->base_stdout = dup(1);
	return (new);
}

void	reset_redirect(t_fd_redir *fds)
{
	dup2(fds->base_stdout, 1);
	dup2(fds->base_stdin, 0);
	close(fds->in);
	close(fds->out);
	fds->in = -1;
	fds->out = -1;
}

void	init_global(char **env)
{
	g_varvalues.env = env;
	g_varvalues.ret = 0;
}
/*
int	main(int ac, char **av, char **env)
{
	char *line;
	(void) av[ac];
	t_lst_token	*end_line;
	t_fd_redir	*fds;

	fds = init_fds();
	init_global(env);
	while (42)
	{
		reset_redirect(fds);
		line = readline("\033[1;33minput : \033[0m");
		if (line[0])
			add_history(line);
		end_line = lexing(line, env);
		display_lst(end_line);
		ft_parser(end_line, fds);
		destroy_lst(end_line);
	}
}
*/

int	main(int ac, char **av, char **env)
{
	if (ac <= 1)
		return(printf("error args\n"));
	exec_cmd(av[1], av + 1, env);
	printf("comande exited with status %d\n", g_varvalues.ret);
}
