/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 04:07:17 by tmongell          #+#    #+#             */
/*   Updated: 2022/05/16 18:57:25 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line_light(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	char		*line;
	static char	*leftover;
	int			read_ret;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = gnl_strdup(leftover);
	if (got_end_of_line(leftover))
	{
		leftover = save_leftover(line, leftover);
		return (line);
	}
	gnl_memset(buf, 0, BUFFER_SIZE + 1);
	read_ret = read(fd, buf, BUFFER_SIZE);
	if (read_ret <= 0 && !gnl_strlen(leftover))
		return (do_free(line));
	while (!got_end_of_line(buf) && read_ret == BUFFER_SIZE)
	{
		line = save_buf(line, buf, read_ret);
		gnl_memset(buf, '\0', BUFFER_SIZE);
		read_ret = read(fd, buf, BUFFER_SIZE);
	}
	leftover = save_leftover(buf, leftover);
	return (save_buf(line, buf, read_ret));
}

void	*do_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

int	got_end_of_line(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i ++;
	}
	return (0);
}

char	*save_buf(char *base_str, char *buf, int read_ret)
{
	char	*new_str;
	int		base_size;
	int		buf_size;

	base_size = gnl_strlen(base_str);
	buf_size = 0;
	while (buf[buf_size] && buf[buf_size] != '\n' && read_ret--)
		buf_size ++;
	if (buf[buf_size] == '\n')
		buf_size ++;
	new_str = malloc(base_size + buf_size + 1);
	if (!new_str)
		return (NULL);
	gnl_strlcpy(new_str, base_str, base_size + 1);
	gnl_strlcpy(new_str + base_size, buf, buf_size + 1);
	free(base_str);
	return (new_str);
}

char	*save_leftover(char *str, char *old_leftover)
{
	char	*leftover;
	int		i;

	if (old_leftover)
		free(old_leftover);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (!str[i])
		return (NULL);
	leftover = gnl_strdup(str + i + 1);
	str[i + 1] = '\0';
	if (!*leftover)
	{
		free(leftover);
		leftover = NULL;
	}
	return (leftover);
}
