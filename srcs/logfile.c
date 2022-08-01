/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:37:52 by tmongell          #+#    #+#             */
/*   Updated: 2022/07/28 14:48:11 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define LOGFILE "./.cmd_log"

static void	add_logfile(char *line)
{
	int	fd;

	fd = open(LOGFILE, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd > 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	close(fd);
}
