/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:22:24 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/02 14:44:27 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
		
//recupere argv[1] verifie 	si num ou non
//si num exit(num);
//si argv[1] non num et/ou plusieur argument apres;
//	exit
//	minishell: exit: argv[1]: numeric argument required
//*bash a exit avec reussite* (non afficher);
//si argv[1] num et plusieur argument apres;
//	exit
//	minishell: exit: too many arguments
//*bash continue exit fail* (non afficher);
//si exit seul
//	exit
//*bash exit avec reussite*(non afficher);
int	ft_str_is_num(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(int argc, char **argv)
{
	if (ft_str_is_num(argv[1]) == 0)
	{
		ft_putendl_fd("exit", 2);
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
	if (ft_str_is_num(argv[1]) == 1 && argv[1])
	{
		ft_putendl_fd("exit", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(255);
	}
	if (!argv[1])
		exit(0);
	return (EXIT_SUCCESS);
}
