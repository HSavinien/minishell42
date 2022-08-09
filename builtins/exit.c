/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:22:24 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/09 15:52:42 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_exit_err(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

int	ft_str_is_num(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (!str[0])
		return (0);
	if ((str[0] == '-' || str[0] == '+') && str[1])
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(int argc, char **argv)
{
	ft_putendl_fd("exit", 2);
	if (ft_str_is_num(argv[1]))
	{
		if (argc > 2 && argv[2])
		{	
			ft_putendl_fd("minishell: exit: Too many arguments dunderhead", 2);
			return (EXIT_FAILURE);
		}
		else if (!argv[1])
			exit(0);
		else
			exit(ft_atoi(argv[1]));
	}
	if (!ft_str_is_num(argv[1]) && argv[1])
	{
		print_exit_err(argv[1]);
		exit(255);
	}
	if (!argv[1])
		exit(0);
	return (EXIT_SUCCESS);
}
