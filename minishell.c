/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:46:51 by tmongell          #+#    #+#             */
/*   Updated: 2022/08/13 20:20:55 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd_redir	*init_fd(void)
{
	t_fd_redir	*fds;

	fds = malloc(sizeof(t_fd_redir));
	fds->in = 0;
	fds->out = 1;
	fds->base_stdin = dup(0);
	fds->base_stdout = dup(1);
	return (fds);
}

void	reset_redirection(t_fd_redir *fds)
{
	if (fds->in != 0)
		close(fds->in);
	if (fds->out != 1)
		close(fds->out);
//	fds->base_stdin = dup(0);
//	fds->base_stdout = dup(1);
	dup2(fds->base_stdin, 0);
	dup2(fds->base_stdout, 1);
}

void	use_line(char *line, t_fd_redir *fds)
{
	t_lst_token	*cmd_list;

	if (!line || !ft_strlen(line))
		return ;
	//add_logfile(line);
	line = expand_vars(line);
	cmd_list = lexing(line);
	if (!cmd_list)
		return ;
	parser_entry(cmd_list, fds);
}

void	init_global(char **env)
{
	int	len;

	len = 0;
	while (env[len])
		len++;
	g_varvalues.env = malloc(sizeof(char *) * (len + 2));
	len = -1;
	while (env[++len])
		g_varvalues.env[len] = ft_strdup(env[len]);
	g_varvalues.env[len] = NULL;
	g_varvalues.env[len + 1] = NULL;
	g_varvalues.ret = 0;
}

int	main(int ac, char **av, char **env)
{
	t_fd_redir		*fds;
	struct termios	read_prompt;
	struct termios	exec;
	char			*line;

	init_signal(&read_prompt, &exec);
	fds = init_fd();
	init_global(env);
	if (ac == 2)
		return (exec_script(av[1], exec, fds));
	else if (ac >= 2)
		return (printf("Error, arguments invalid\n") + 102);
	load_conf(".minishellrc", exec, fds);
	while (42)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &read_prompt);
		reset_redirection(fds);
		line = readline(PS1);
		if (!line && printf("\033[1A%sexit\n", rl_prompt))
			return (g_varvalues.ret);
		if (line[0])
			add_history(line);
		tcsetattr(STDIN_FILENO, TCSANOW, &exec);
		use_line(line, fds);
	}
}
