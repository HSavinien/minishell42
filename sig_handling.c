/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:50:38 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/10 17:40:10 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		if (rl_done)
			return ;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_signal(struct termios *read_prompt, struct termios *exec)
{
	tcgetattr(STDIN_FILENO, read_prompt);
	read_prompt->c_lflag &= ~(ECHOCTL);
	exec = read_prompt;
	exec->c_lflag |= (ECHOCTL);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}
