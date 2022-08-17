/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:32:34 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/17 15:01:31 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_str_is_valid(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (ft_strchr("+=$#@'%^:,/.{}\"", str[i]))
			if (str[i] == '=' && str[i + 1])
				return (1);
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i ++]))
			return (1);
	}
	return (0);
}

int	ft_find_index(char **env, char *env_srch, int len_srch)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], env_srch, len_srch))
			return (i);
	if (env[i + 1])
	{
		while (env[++i])
			if (!ft_strncmp(env[i], env_srch, len_srch) && !env[i][len_srch])
				return (i);
	}
	return (-1);
}

char	**ft_realloc_char(char **ptr, int len, int hidden, char *str)
{
	char	**temp_ptr;
	int		i;
	int		j;
	int		num;

	temp_ptr = malloc(sizeof(char *) * (len + 1));
	if (!temp_ptr)
		return (NULL);
	i = -1;
	j = 0;
	num = 0;
	while (++i < len)
	{
		if (ptr[i] == NULL)
		{
			if (num++ == hidden)
			{
				j++;
				temp_ptr[i] = ft_strdup(str);
			}
		}
		temp_ptr[i + j] = ptr[i];
	}
	free(ptr);
	return (temp_ptr);
}
