/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dico_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 18:37:21 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/02 19:16:56 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtins(char **std_args)
{
	int		argc;
	int		i;
	t_dico	dico[8];

	argc = 0;
	while (std_args[argc])
		argc++;
	dico[0] = (t_dico){"env", &ft_env};
	dico[1] = (t_dico){"pwd", &ft_pwd};
	dico[2] = (t_dico){"exit", &ft_exit};
	dico[3] = (t_dico){"cd", &ft_cd};
	dico[4] = (t_dico){"export", &ft_export};
	dico[5] = (t_dico){"unset", &ft_unset};
	dico[6] = (t_dico){"echo", &ft_echo};
	dico[7] = (t_dico){0, 0};
	i = 0;
	while (dico[i].key && ft_strcmp(dico[i].key, std_args[0]))
		i++;
	if (!dico[i].key || ft_strcmp(dico[i].key, std_args[0]))
		return (1);
	dico[i].fct(argc, std_args);
	return (0);
}
