/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 14:06:18 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/10 14:08:41 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(int argc, char **argv)
{
	int i;

	i = 1;
	while (!ft_strcmp(argv[i], "-n"))
			i++;
	while (argv[i])
	{
		printf("%s", argv[i ++]);
		if (i <= argc - 1)
			printf(" ");
	}	
	if (ft_strcmp(argv[1], "-n"))
		printf("\n");
	return (0);
}
