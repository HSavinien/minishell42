/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:18:19 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/10 19:18:03 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	send_to_pipe(char *line, char *stop, int fd)
{
		if (line && ft_strcmp(line, stop))
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
}

//idea : we have to read stdin with readline until the stop str is found.
//whe then have to send everything to stdin, so the next cmd can read it.
void	ft_heredoc(char	*stop, t_fd_redir *fds)
{
	char	*line;
	int		pipe_fd[2];

	close(fds->in);
	dup2(fds->base_stdin, 0);
	if (pipe(pipe_fd))
		tech_error("could not creat pipe for heredoc");
	line = readline(PS2);
	send_to_pipe(line, stop, pipe_fd[1]);
	while (line && ft_strcmp(line, stop))
	{
		free(line);
		line = readline(PS2);
		send_to_pipe(line, stop, pipe_fd[1]);
	}
	free(line);
	close(pipe_fd[1]);
	fds->in = pipe_fd[0];
	dup2(fds->in, 0);
}
