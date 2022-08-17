/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 14:06:18 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/17 14:16:05 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(int argc, char **argv)
{
	int	i;

	if (argc == 1)
		return (printf("\n"));
	i = 1;
	while (argv[i] && !ft_strncmp(argv[i], "-n", 2))
			i++;
	while (argv[i])
	{
		printf("%s", argv[i ++]);
		if (i <= argc - 1)
			printf(" ");
	}	
	if (ft_strncmp(argv[1], "-n", 2))
		printf("\n");
	return (0);
}
