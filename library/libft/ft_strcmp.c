/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 12:18:23 by cmaroude          #+#    #+#             */
/*   Updated: 2022/07/13 14:35:33 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_min(const char x, const char y)
{
	if (x > y)
		return (y);
	else
		return (x);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	return (ft_strncmp(s1, s2, ft_min(ft_strlen(s1), ft_strlen(s2)) + 1));
}
