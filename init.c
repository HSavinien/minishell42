/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:51:27 by tmongell          #+#    #+#             */
/*   Updated: 2022/08/15 19:52:55 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_global(char **env)
{
	int	len;

	len = 0;
	while (env[len])
		len++;
	g_varvalues.env = malloc(sizeof(char *) * (len + 2));
	len = -1;
	while (env[++len])
		g_varvalues.env[len] = ft_strdup(env[len]);
	g_varvalues.env[len] = NULL;
	g_varvalues.env[len + 1] = NULL;
	g_varvalues.ret = 0;
}

t_fd_redir	*init_fd(void)
{
	t_fd_redir	*fds;

	fds = malloc(sizeof(t_fd_redir));
	fds->in = 0;
	fds->out = 1;
	fds->base_stdin = dup(0);
	fds->base_stdout = dup(1);
	return (fds);
}
