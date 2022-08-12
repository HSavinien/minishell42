/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:50:38 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/12 15:27:02 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		if (rl_done)
			return ;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_varvalues.ret = 1;
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		g_varvalues.ret = g_varvalues.ret + SIGQUIT;
	}
}

void	init_signal(struct termios *read_prompt, struct termios *exec)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	tcgetattr(STDIN_FILENO, exec);
	exec->c_lflag |= ECHOCTL;
	*read_prompt = *exec;
	read_prompt->c_lflag &= ~ECHOCTL;
}
