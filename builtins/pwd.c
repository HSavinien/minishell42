/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:41:43 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/02 12:53:17 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(int argc, char **argv)
{
	char	*pwd;

	(void)argv;
	if (argc > 1)
	{
		ft_putendl_fd("pwd: Too many arguments idiot", 2);
		return (EXIT_FAILURE);
	}
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd || pwd == NULL)
	{
		ft_putendl_fd("pwd: PWD_ERROR", 2);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (EXIT_SUCCESS);
}
