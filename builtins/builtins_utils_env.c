/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:22:04 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/15 19:24:27 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_remove_element(int *index)
{
	int	i;
	int	len_env;

	i = 0;
	while (g_varvalues.env[i])
		i++;
	if (g_varvalues.env[i + 1])
	{
		i++;
		while (g_varvalues.env[i])
			i++;
	}
	len_env = i;
	if (!g_varvalues.env[*index])
		return ;
	free(g_varvalues.env[*index]);
	while (*index < len_env)
	{
		g_varvalues.env[*index] = g_varvalues.env[(*index) + 1];
		(*index)++;
	}
}

void	ft_add_env(char *str, int hidden)
{
	int		i;
	int		j;
	char	**env;

	i = -1;
	j = 0;
	env = g_varvalues.env;
	while (env[++i])
		if (env[i + 1] == '\0')
			j = i + 1;
	while (env[++i])
		if (env[i + 1] == '\0')
			j = i + 1;
	g_varvalues.env = ft_realloc_char(env, i + 1, hidden, str);
}

void	ft_exchange_env(int index, char *argv)
{
	free(g_varvalues.env[index]);
	g_varvalues.env[index] = argv;
}
