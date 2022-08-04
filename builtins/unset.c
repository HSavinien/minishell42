/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:39:48 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/03 19:09:59 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_unset_err(char *str)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier, try harder!", 2);
	return (1);
}

int	ft_strisvalid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr("+=$#@'%^:,/.{}\"", str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_remove_element(int *index)
{
	int	i;
	int	len_env;

	i = 0;
	while (g_varvalues.env[i])
		i++;
	len_env = i;
	if (!g_varvalues.env[*index])
		return ;
	//free(g_varvalues.env[i]);
	while (*index < len_env)
	{
		g_varvalues.env[*index] = g_varvalues.env[(*index) + 1];
		(*index)++;
	}
}

int	ft_find_index(char **env, char *env_srch, int len_srch)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], env_srch, len_srch))
			i++;
	if (!env[i])
		return (-1);
	else
		return (i);
}

int	ft_unset(int argc, char **argv)
{
	int		i;
	int		j;
	char	*env_srch;
	int		ret_exit;

	ret_exit = 0;
	if (argc == 1)
		return (EXIT_SUCCESS);
	i = 1;
	while (argv[i])
	{
		if (!ft_isdigit(argv[i][0]) && !ft_strisvalid(argv[i]))
		{
			env_srch = ft_strjoin(argv[i], "=");
			j = ft_find_index(g_varvalues.env, env_srch, ft_strlen(env_srch));
			if (j != -1 || g_varvalues.env[j])
				ft_remove_element(&j);
		}
		else
			ret_exit = print_unset_err(argv[i]);
		i++;
	}
	return (ret_exit);
}
