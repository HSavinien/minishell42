/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:52:57 by tmongell          #+#    #+#             */
/*   Updated: 2022/08/17 17:33:51 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_error(char *file_name, int err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	g_varvalues.ret = err;
	return (1);
}

int	tech_error(char *msg, int err, t_lst_token *token)
{	
	ft_putstr_fd("technical error: ", 2);
	ft_putendl_fd(msg, 2);
	g_varvalues.ret = err;
	destroy_lst(token);
	return (err);
}

int	error(char *msg, int err, t_lst_token *freeable_lst)
{
	printf("Error : %s\n", msg);
	g_varvalues.ret = err;
	destroy_lst(freeable_lst);
	return (err);
}
