/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:46:22 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/09 17:24:08 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_export_err(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier, try harder!", 2);
	return (EXIT_FAILURE);
}

void	ft_print_var_export(char *env)
{
	int		var;

	if (ft_strchr(env, '='))
	{
		var = ft_strchr(env, '=') - env;
		printf("declare -x %.*s=\"%s\"\n", var, env, &env[var + 1]);
	}
	else
	{	
		printf("declare -x %s\n", env);
	}
}

int	ft_print_export(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{	
		ft_print_var_export(env[i]);
		i++;
	}
	if (env[i +1])
	{
		i++;
		while (env[i])
		{	
			ft_print_var_export(env[i]);
			i++;
		}
	}
	if (!i)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_export_add(char *argv, char **var_name, int hidden)
{
	int		len;	
	int		index_ex;
	char	**env;

	env = g_varvalues.env;
	if (!ft_isdigit(argv[0]) && !ft_str_is_valid(var_name[0]))
	{
		len = ft_strlen(var_name[0]);
		index_ex = ft_find_index(env, var_name[0], len);
		if (index_ex == -1)
			ft_add_env(argv, hidden);
		else if (index_ex != -1 && !hidden)
		{
			ft_remove_element(&index_ex);
			ft_add_env(argv, hidden);
		}
	}		
	else
		return (print_export_err(argv));
	return (EXIT_SUCCESS);
}

int	ft_export(int argc, char **argv)
{
	int		i;
	int		hidden;
	char	**var_name;

	if (argc == 1)
		return (ft_print_export(g_varvalues.env));
	i = 0;
	while (argv[++i] && *argv[i])
	{
		if (ft_strchr(argv[i], '='))
		{
			var_name = ft_split(argv[i], '=');
			hidden = 0;
		}
		else
		{
			var_name = ft_split(argv[i], '\0');
			hidden = 1;
		}
		if (ft_export_add(argv[i], var_name, hidden) != 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
