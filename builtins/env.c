/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:38:43 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/02 14:27:33 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(int argc, char **argv)
{
	char	**env_cpy;
	int		i;
	
	if (argc > 1)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (EXIT_FAILURE);
	}
	env_cpy = g_varvalues.env;
	i = 0;
	while (env_cpy[i])
	{
		printf("%s\n", env_cpy[i++]);
	}
	return (EXIT_SUCCESS);
}
