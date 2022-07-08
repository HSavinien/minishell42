/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:54:11 by tmongell          #+#    #+#             */
/*   Updated: 2022/05/02 16:54:22 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// function that give the number of substring in the original string to split
static int	ft_count_word(char const *s)
{
	int	i;
	int	nb_str;

	if (ft_strlen(s) == 0)
		return (0);
	i = 1;
	nb_str = 1;
	while (s[i])
	{
		if (ft_isspace(s[i]) && !ft_isspace(s[i - 1]))
			nb_str ++;
		i ++;
	}
	if (ft_isspace(s[i - 1]))
		nb_str --;
	return (nb_str);
}

// function that give a pointer one the first char of the num^th substr of s.
static char	*ft_find_word(char const *s, int num)
{
	int		i;
	int		curent_str;

	if (num > ft_count_word(s))
		return (NULL);
	i = 0;
	curent_str = 1;
	while (curent_str < num + 1)
	{
		if (ft_isspace(s[i]) && !ft_isspace(s[i - 1]) && i)
			curent_str ++;
		i ++;
	}
	while (ft_isspace(s[i]))
		i ++;
	return ((char *)(s + i));
}

static char	*ft_get_word(char const *s, int num)
{
	char	*str;
	int		i;

	str = ft_find_word(s, num);
	i = 0;
	while (!ft_isspace(str[i]))
		i ++;
	str = ft_strndup(str, i);
	return (str);
}

char	**ft_split_word(char const *s)
{
	char	**str_array;
	int		nb_substr;
	int		i;

	nb_substr = ft_count_word(s);
	str_array = malloc(sizeof (char *) * (nb_substr + 1));
	if (str_array == NULL)
		return (NULL);
	i = 0;
	while (i < nb_substr)
	{
		str_array[i] = ft_get_word(s, i);
		i ++;
	}
	str_array[i] = NULL;
	return (str_array);
}
