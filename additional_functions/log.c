/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 19:26:28 by tmongell          #+#    #+#             */
/*   Updated: 2022/08/15 12:40:40 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//function that read a logfile, and add each line (without the \n) to the
//readline history.
int	load_logfile(char *logfile)
{
	int		fd;
	char	*line;

	fd = open(logfile, O_RDONLY);
	if (!fd)
		return (1);
	while (42)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line[ft_strlen(line) - 1] = '\0';
		add_history(line);
		free(line);
	}
	close (fd);
	return (0);
}

void	add_logfile(char *line)
{
	int	fd;

	fd = open(".minishell_history", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return ;
	ft_putstr_fd(line, fd);
	write(fd, "\n", 1);
	close (fd);
}
