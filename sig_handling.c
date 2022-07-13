/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:50:38 by cmaroude          #+#    #+#             */
/*   Updated: 2022/07/13 11:33:42 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "minishell.h" */

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		// redisplay prompt
	}
	else if (sig == SIGQUIT && /*interactive mode*/)
		return;
	else if (sig == SIGQUIT && /* non-interactive mode*/)
	{
		/*change satus minishell to stop running actual cmd*/
		write(1, "Quit: 3\n", 8);
	   //display new prompt	
	}
}

void	init_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}

/*int main(int argc, char **argv)
{
	init_signal():
}*/
