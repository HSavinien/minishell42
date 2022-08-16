/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:46:51 by tmongell          #+#    #+#             */
/*   Updated: 2022/08/16 17:54:16 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_redirection(t_fd_redir *fds)
{
	if (fds->in != 0)
		close(fds->in);
	if (fds->out != 1)
		close(fds->out);
	dup2(fds->base_stdin, 0);
	dup2(fds->base_stdout, 1);
}

void	use_line(char *line, t_fd_redir *fds)
{
	t_lst_token	*cmd_list;

	if (!line || !ft_strlen(line))
	{
		free(line);
		return ;
	}
	add_logfile(line);
	line = expand_vars(line);
	cmd_list = lexing(line);
	if (!cmd_list)
		return ;
	parser_entry(cmd_list, fds);
}

void	load_files(struct termios exec, t_fd_redir *fds)
{
	load_conf(CONF_FILE, exec, fds);
	load_logfile(HISTORY);
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
	load_files(exec, fds);
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
