/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:40:28 by tmongell          #+#    #+#             */
/*   Updated: 2022/05/16 18:58:11 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strdup(const char *s1)
{
	char	*cpy;
	size_t	len;

	if (!s1)
		return (gnl_strdup(""));
	len = gnl_strlen(s1) + 1;
	cpy = malloc(len);
	if (cpy == NULL)
		return (NULL);
	gnl_strlcpy(cpy, s1, len);
	return (cpy);
}

size_t	gnl_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i ++;
	return (i);
}

size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	i;

	i = 0;
	while (i < (int)dstsize && src)
	{
		dst[i] = src[i];
		i ++;
	}
	dst[i - 1] = '\0';
	return ((size_t)gnl_strlen(src));
}

void	*gnl_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	if (!b)
		return (NULL);
	i = 0;
	str = b;
	while (i < len)
	{
		str[i] = c;
		i ++;
	}
	return (str);
}
