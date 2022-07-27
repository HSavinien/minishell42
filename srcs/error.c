/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:52:57 by tmongell          #+#    #+#             */
/*   Updated: 2022/07/27 15:03:57 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_error(char *file_name)
{
	int save;
	save = dup(1);
	dup2(2, 1);
	printf("Error : cannot open file  %s\n", file_name);
	dup2(save, 1);
//	exit(1);
}

void	tech_error(char *msg)
{	
	int save;
	save = dup(1);
	dup2(2, 1);
	printf("technical error : %s\n", msg);
	dup2(save, 1);
	exit(1);
}
