/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 14:06:18 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/17 14:48:46 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//test if an argument is of the form -nnnnnnn... with at least one n.
//return 1 if arg is of this form, 0 else
int	is_option_no_nl(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i ++] != 'n')
			return (0);
	}
	return (1);
}

int	ft_echo(int argc, char **argv)
{
	int	i;

	if (argc == 1)
		return (printf("\n"));
	i = 1;
	while (argv[i] && is_option_no_nl(argv[i]))
			i++;
	while (argv[i])
	{
		printf("%s", argv[i ++]);
		if (i <= argc - 1)
			printf(" ");
	}	
	if (!is_option_no_nl(argv[1]))
		printf("\n");
	return (0);
}
