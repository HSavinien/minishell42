/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:39:48 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/09 16:25:05 by cmaroude         ###   ########.fr       */
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
		if (!ft_isdigit(argv[i][0]) && !ft_str_is_valid(argv[i]))
		{
			env_srch = argv[i];
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
