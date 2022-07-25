/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:46:51 by tmongell          #+#    #+#             */
/*   Updated: 2022/07/25 14:04:25 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_script(char *script, char **env)
{
	printf("script execution not yet implemented\n");
	return (1);
}

void	init_fd(t_fd_redirect *fds)
{
	fds->in = 0;
	fds->out = 1;
	fds->base_stdin = dup(0);
	fds->base_stdout = dup(1);
}

void	reset_redirection(t_fd_redirect *fds)
{
	if (fds->in != 0)
		free(fds->in);
	if (fds->out != 1)
		free(fds->out);
	fds->in = fds->base_stdin;
	fds->out = fds->base_stdout;
}

void	use_line(line)
{
	
}

int	main(int ac, char **av, char **env)
{
	t_fd_redirect	fds;
	char			*line;

	if (ac == 2)
		return (exec_script(av[1], env));
	else if (>= 2)
		return (printf("Error, arguments invalid\n"));
	//do initialisation here if needed
	init_fd(&fd);
	while (42)
	{
		reset_redirection(&fds);
		reset_signal();
		line = readline(PS1);
		if (line && line[0])
			add_history(line);
		use_line(line);
		free(line);
	}
}
