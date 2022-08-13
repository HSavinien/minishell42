/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 19:35:01 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/13 20:19:51 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_script(char *script, struct termios exec, t_fd_redir *fds)
{
	int		fd;
	char	*line;

	fd = open(script, O_RDONLY);
	if (fd < 0)
		return (open_error(script, 1));
	tcsetattr(STDIN_FILENO, TCSANOW, &exec);
	while (42)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[0] != '#')
		{
			if (line[ft_strlen(line)] == '\n')
				line[ft_strlen(line)] = '\0';
			use_line(line, fds);
		}
	}
	close(fd);
	return (0);
}

void	load_conf(char *conf_file, struct termios exec, t_fd_redir *fds)
{
	if (access(conf_file, R_OK | F_OK) < 0)
		return ;
	exec_script(conf_file, exec, fds);
}
