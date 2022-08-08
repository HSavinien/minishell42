/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:18:19 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/08 17:53:00 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//idea : we have to read stdin with readline until the stop str is found.
//whe then have to send everything to stdin, so the next cmd can read it.
void	ft_heredoc(char	*stop, t_fd_redir *fds)
{
	dprintf(2, "entering %s (%s:%d)\n", __FUNCTION__, __FILE__,__LINE__);//debug
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd))
		tech_error("could not creat pipe for heredoc");
	line = NULL;
	while (!line || ft_strcmp(line, stop))
	{
		free(line);
		line = readline(PS2);
		if (line && ft_strcmp(line, stop))
			write(pipe_fd[1], line, ft_strlen(line));
	}
	free(line);
	close(fds->in);
	close(pipe_fd[1]);
	fds->in = pipe_fd[0];
	dup2(fds->in, 0);
	dprintf(2, "exiting %s (%s:%d)\n", __FUNCTION__, __FILE__,__LINE__);//debug
}
