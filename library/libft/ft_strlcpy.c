/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:31:10 by tmongell          #+#    #+#             */
/*   Updated: 2021/11/23 18:21:23 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	i;

	if (!dst)
		return (ft_strlen(src));
	i = 0;
	while (i < (int)dstsize && src)
	{
		dst[i] = src[i];
		i ++;
	}
	dst[i - 1] = '\0';
	return ((size_t)ft_strlen(src));
}
