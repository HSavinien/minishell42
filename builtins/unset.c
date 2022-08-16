/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:39:48 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/16 17:39:45 by cmaroude         ###   ########.fr       */
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
			dprintf(2, "index: %d\n", j);
			if (j != -1 && g_varvalues.env[j])
				ft_remove_element(&j);
		}
		else
			ret_exit = print_unset_err(argv[i]);
		i++;
	}
	return (ret_exit);
}
